#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qmqtt" for configuration "Release"
set_property(TARGET qmqtt APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(qmqtt PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libqmqtt.so.1.0.5"
  IMPORTED_SONAME_RELEASE "libqmqtt.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS qmqtt )
list(APPEND _IMPORT_CHECK_FILES_FOR_qmqtt "${_IMPORT_PREFIX}/lib/libqmqtt.so.1.0.5" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
