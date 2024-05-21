#!/usr/bin/env python

import rospy
from mavros_msgs.msg import PositionTarget
from mavros_msgs.srv import SetMode
from geometry_msgs.msg import PoseStamped
import casadi as ca

class MPCController:
    def __init__(self):
        rospy.init_node('mpc_controller', anonymous=True)

        self.pos_pub = rospy.Publisher('/mavros/setpoint_raw/local', PositionTarget, queue_size=10)
        self.pose_sub = rospy.Subscriber('/mavros/local_position/pose', PoseStamped, self.pose_callback)

        self.set_mode_service = rospy.ServiceProxy('/mavros/set_mode', SetMode)

        self.current_pose = PoseStamped()

        self.init_mpc()

    def pose_callback(self, msg):
        self.current_pose = msg

    def init_mpc(self):
        # MPC parameters
        self.T = 10.0  # Time horizon
        self.N = 20  # Number of control intervals
        self.dt = self.T / self.N

        # Model variables
        x = ca.SX.sym('x')
        y = ca.SX.sym('y')
        z = ca.SX.sym('z')
        vx = ca.SX.sym('vx')
        vy = ca.SX.sym('vy')
        vz = ca.SX.sym('vz')
        states = ca.vertcat(x, y, z, vx, vy, vz)
        self.n_states = states.size()[0]

        ax = ca.SX.sym('ax')
        ay = ca.SX.sym('ay')
        az = ca.SX.sym('az')
        controls = ca.vertcat(ax, ay, az)
        self.n_controls = controls.size()[0]

        rhs = ca.vertcat(vx, vy, vz, ax, ay, az)
        self.f = ca.Function('f', [states, controls], [rhs])

        # Initialize decision variables, parameters, and constraints
        self.U = ca.SX.sym('U', self.n_controls, self.N)
        self.P = ca.SX.sym('P', self.n_states + self.n_states)
        self.X = ca.SX.sym('X', self.n_states, self.N+1)

        # Initial state constraint
        g = [self.X[:, 0] - self.P[0:self.n_states]]

        # Dynamics constraints
        for k in range(self.N):
            st = self.X[:, k]
            con = self.U[:, k]
            f_value = self.f(st, con)
            st_next = st + (self.dt * f_value)
            g.append(st_next - self.X[:, k+1])

        Q = ca.diagcat(1, 1, 1, 0.1, 0.1, 0.1)
        R = ca.diagcat(0.1, 0.1, 0.1)

        obj = 0
        for k in range(self.N):
            st = self.X[:, k]
            con = self.U[:, k]
            obj += ca.mtimes([st.T - self.P[self.n_states:].T, Q, st - self.P[self.n_states:]]) + ca.mtimes([con.T, R, con])

        # Flatten the list of constraints
        g_flat = ca.vertcat(*g)

        opt_variables = ca.reshape(self.U, -1, 1)
        nlp_prob = {'f': obj, 'x': opt_variables, 'g': g_flat, 'p': self.P}
        opts = {'ipopt.max_iter': 100, 'ipopt.print_level': 0, 'print_time': 0}
        self.solver = ca.nlpsol('solver', 'ipopt', nlp_prob, opts)

        self.lbg = ca.DM.zeros((self.n_states * (self.N+1), 1))  # Match the number of constraints
        self.ubg = ca.DM.zeros((self.n_states * (self.N+1), 1))  # Match the number of constraints

    def mpc_control(self, ref):
        init_state = ca.DM([self.current_pose.pose.position.x, self.current_pose.pose.position.y, self.current_pose.pose.position.z, 0, 0, 0])
        p = ca.vertcat(init_state, ref)

        u0 = ca.DM.zeros((self.n_controls, self.N))
        x0 = ca.repmat(init_state, 1, self.N+1)

        sol = self.solver(x0=ca.reshape(u0, -1, 1), p=p, lbg=self.lbg, ubg=self.ubg)
        u = ca.reshape(sol['x'], self.n_controls, self.N)

        return u[:, 0].full().flatten()

    def run(self):
        rate = rospy.Rate(20)
        self.set_mode_service(custom_mode="OFFBOARD")

        while not rospy.is_shutdown():
            ref = ca.DM([1, 1, 1, 0, 0, 0])  # Desired position
            control = self.mpc_control(ref)

            target = PositionTarget()
            target.type_mask = PositionTarget.IGNORE_PX + PositionTarget.IGNORE_PY + PositionTarget.IGNORE_PZ
            target.coordinate_frame = PositionTarget.FRAME_LOCAL_NED
            target.position.x = self.current_pose.pose.position.x
            target.position.y = self.current_pose.pose.position.y
            target.position.z = self.current_pose.pose.position.z
            target.velocity.x = control[0]
            target.velocity.y = control[1]
            target.velocity.z = control[2]

            self.pos_pub.publish(target)

            rate.sleep()

if __name__ == '__main__':
    mpc_controller = MPCController()
    mpc_controller.run()
