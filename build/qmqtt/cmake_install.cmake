# Install script for directory: /home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/arty/Documents/video_ros2/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xLibraryx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so.1.0.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/arty/Documents/video_ros2/build/qmqtt/libqmqtt.so.1.0.5"
    "/home/arty/Documents/video_ros2/build/qmqtt/libqmqtt.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so.1.0.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xLibraryx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/arty/Documents/video_ros2/build/qmqtt/libqmqtt.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqmqtt.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt/qmqttTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt/qmqttTargets.cmake"
         "/home/arty/Documents/video_ros2/build/qmqtt/CMakeFiles/Export/lib/cmake/qmqtt/qmqttTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt/qmqttTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt/qmqttTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt" TYPE FILE FILES "/home/arty/Documents/video_ros2/build/qmqtt/CMakeFiles/Export/lib/cmake/qmqtt/qmqttTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt" TYPE FILE FILES "/home/arty/Documents/video_ros2/build/qmqtt/CMakeFiles/Export/lib/cmake/qmqtt/qmqttTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE OPTIONAL FILES
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_global.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_client.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_frame.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_message.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_routesubscription.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_routedmessage.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_router.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_networkinterface.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_socketinterface.h"
    "/home/arty/Documents/video_ros2/src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_timerinterface.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt/qmqtt.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt/qmqtt.cmake"
         "/home/arty/Documents/video_ros2/build/qmqtt/CMakeFiles/Export/lib/cmake/qmqtt/qmqtt.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt/qmqtt-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt/qmqtt.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt" TYPE FILE FILES "/home/arty/Documents/video_ros2/build/qmqtt/CMakeFiles/Export/lib/cmake/qmqtt/qmqtt.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt" TYPE FILE FILES "/home/arty/Documents/video_ros2/build/qmqtt/CMakeFiles/Export/lib/cmake/qmqtt/qmqtt-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/qmqtt" TYPE FILE FILES
    "/home/arty/Documents/video_ros2/build/qmqtt/qmqttConfig.cmake"
    "/home/arty/Documents/video_ros2/build/qmqtt/qmqttConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/arty/Documents/video_ros2/build/qmqtt/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
