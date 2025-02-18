#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qt6::LabsSharedImage" for configuration "RelWithDebInfo"
set_property(TARGET Qt6::LabsSharedImage APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Qt6::LabsSharedImage PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/Qt6LabsSharedImage.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELWITHDEBINFO "Qt6::Qml"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/Qt6LabsSharedImage.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qt6::LabsSharedImage )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qt6::LabsSharedImage "${_IMPORT_PREFIX}/lib/Qt6LabsSharedImage.lib" "${_IMPORT_PREFIX}/bin/Qt6LabsSharedImage.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
