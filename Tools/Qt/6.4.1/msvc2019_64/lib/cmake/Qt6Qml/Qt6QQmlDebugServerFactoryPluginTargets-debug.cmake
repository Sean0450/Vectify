#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QQmlDebugServerFactoryPlugin" for configuration "Debug"
set_property(TARGET Qt6::QQmlDebugServerFactoryPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qt6::QQmlDebugServerFactoryPlugin PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_DEBUG ""
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/./plugins/qmltooling/qmldbg_serverd.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QQmlDebugServerFactoryPlugin )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QQmlDebugServerFactoryPlugin "${_IMPORT_PREFIX}/./plugins/qmltooling/qmldbg_serverd.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
