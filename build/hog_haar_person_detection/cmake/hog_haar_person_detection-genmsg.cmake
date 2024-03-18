# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "hog_haar_person_detection: 3 messages, 0 services")

set(MSG_I_FLAGS "-Ihog_haar_person_detection:/home/orange/orange_ws/src/hog_haar_person_detection/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(hog_haar_person_detection_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg" NAME_WE)
add_custom_target(_hog_haar_person_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hog_haar_person_detection" "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg" "std_msgs/Header:geometry_msgs/Point:hog_haar_person_detection/BoundingBox"
)

get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg" NAME_WE)
add_custom_target(_hog_haar_person_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hog_haar_person_detection" "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg" "std_msgs/Header:geometry_msgs/Point:hog_haar_person_detection/BoundingBox"
)

get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg" NAME_WE)
add_custom_target(_hog_haar_person_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hog_haar_person_detection" "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg" "geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_cpp(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_cpp(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hog_haar_person_detection
)

### Generating Services

### Generating Module File
_generate_module_cpp(hog_haar_person_detection
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hog_haar_person_detection
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(hog_haar_person_detection_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(hog_haar_person_detection_generate_messages hog_haar_person_detection_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_cpp _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_cpp _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_cpp _hog_haar_person_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hog_haar_person_detection_gencpp)
add_dependencies(hog_haar_person_detection_gencpp hog_haar_person_detection_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hog_haar_person_detection_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_eus(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_eus(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hog_haar_person_detection
)

### Generating Services

### Generating Module File
_generate_module_eus(hog_haar_person_detection
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hog_haar_person_detection
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(hog_haar_person_detection_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(hog_haar_person_detection_generate_messages hog_haar_person_detection_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_eus _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_eus _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_eus _hog_haar_person_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hog_haar_person_detection_geneus)
add_dependencies(hog_haar_person_detection_geneus hog_haar_person_detection_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hog_haar_person_detection_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_lisp(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_lisp(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hog_haar_person_detection
)

### Generating Services

### Generating Module File
_generate_module_lisp(hog_haar_person_detection
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hog_haar_person_detection
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(hog_haar_person_detection_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(hog_haar_person_detection_generate_messages hog_haar_person_detection_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_lisp _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_lisp _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_lisp _hog_haar_person_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hog_haar_person_detection_genlisp)
add_dependencies(hog_haar_person_detection_genlisp hog_haar_person_detection_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hog_haar_person_detection_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_nodejs(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_nodejs(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hog_haar_person_detection
)

### Generating Services

### Generating Module File
_generate_module_nodejs(hog_haar_person_detection
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hog_haar_person_detection
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(hog_haar_person_detection_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(hog_haar_person_detection_generate_messages hog_haar_person_detection_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_nodejs _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_nodejs _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_nodejs _hog_haar_person_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hog_haar_person_detection_gennodejs)
add_dependencies(hog_haar_person_detection_gennodejs hog_haar_person_detection_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hog_haar_person_detection_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_py(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hog_haar_person_detection
)
_generate_msg_py(hog_haar_person_detection
  "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hog_haar_person_detection
)

### Generating Services

### Generating Module File
_generate_module_py(hog_haar_person_detection
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hog_haar_person_detection
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(hog_haar_person_detection_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(hog_haar_person_detection_generate_messages hog_haar_person_detection_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Faces.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_py _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/Pedestrians.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_py _hog_haar_person_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/orange/orange_ws/src/hog_haar_person_detection/msg/BoundingBox.msg" NAME_WE)
add_dependencies(hog_haar_person_detection_generate_messages_py _hog_haar_person_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hog_haar_person_detection_genpy)
add_dependencies(hog_haar_person_detection_genpy hog_haar_person_detection_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hog_haar_person_detection_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hog_haar_person_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hog_haar_person_detection
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(hog_haar_person_detection_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(hog_haar_person_detection_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hog_haar_person_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hog_haar_person_detection
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(hog_haar_person_detection_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(hog_haar_person_detection_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hog_haar_person_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hog_haar_person_detection
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(hog_haar_person_detection_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(hog_haar_person_detection_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hog_haar_person_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hog_haar_person_detection
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(hog_haar_person_detection_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(hog_haar_person_detection_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hog_haar_person_detection)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hog_haar_person_detection\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hog_haar_person_detection
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(hog_haar_person_detection_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(hog_haar_person_detection_generate_messages_py geometry_msgs_generate_messages_py)
endif()
