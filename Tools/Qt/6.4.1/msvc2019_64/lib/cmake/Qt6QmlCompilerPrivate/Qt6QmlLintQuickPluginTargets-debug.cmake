#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::QmlLintQuickPlugin" for configuration "Debug"
set_property(TARGET Qt6::QmlLintQuickPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qt6::QmlLintQuickPlugin PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_DEBUG ""
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/./plugins/qmllint/quicklintplugind.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::QmlLintQuickPlugin )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::QmlLintQuickPlugin "${_IMPORT_PREFIX}/./plugins/qmllint/quicklintplugind.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
