#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::LabsFolderListModel" for configuration "Debug"
set_property(TARGET Qt6::LabsFolderListModel APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qt6::LabsFolderListModel PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/Qt6LabsFolderListModeld.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt6::Qml"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/Qt6LabsFolderListModeld.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::LabsFolderListModel )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::LabsFolderListModel "${_IMPORT_PREFIX}/lib/Qt6LabsFolderListModeld.lib" "${_IMPORT_PREFIX}/bin/Qt6LabsFolderListModeld.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
