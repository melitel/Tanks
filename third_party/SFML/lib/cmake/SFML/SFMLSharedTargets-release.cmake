#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SFML::System" for configuration "Release"
set_property(TARGET SFML::System APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::System PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/sfml-system.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/sfml-system-3.dll"
  )

list(APPEND _cmake_import_check_targets SFML::System )
list(APPEND _cmake_import_check_files_for_SFML::System "${_IMPORT_PREFIX}/lib/sfml-system.lib" "${_IMPORT_PREFIX}/bin/sfml-system-3.dll" )

# Import target "SFML::Main" for configuration "Release"
set_property(TARGET SFML::Main APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Main PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/sfml-main-s.lib"
  )

list(APPEND _cmake_import_check_targets SFML::Main )
list(APPEND _cmake_import_check_files_for_SFML::Main "${_IMPORT_PREFIX}/lib/sfml-main-s.lib" )

# Import target "SFML::Window" for configuration "Release"
set_property(TARGET SFML::Window APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Window PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/sfml-window.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/sfml-window-3.dll"
  )

list(APPEND _cmake_import_check_targets SFML::Window )
list(APPEND _cmake_import_check_files_for_SFML::Window "${_IMPORT_PREFIX}/lib/sfml-window.lib" "${_IMPORT_PREFIX}/bin/sfml-window-3.dll" )

# Import target "SFML::Network" for configuration "Release"
set_property(TARGET SFML::Network APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Network PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/sfml-network.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/sfml-network-3.dll"
  )

list(APPEND _cmake_import_check_targets SFML::Network )
list(APPEND _cmake_import_check_files_for_SFML::Network "${_IMPORT_PREFIX}/lib/sfml-network.lib" "${_IMPORT_PREFIX}/bin/sfml-network-3.dll" )

# Import target "SFML::Graphics" for configuration "Release"
set_property(TARGET SFML::Graphics APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Graphics PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/sfml-graphics.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/sfml-graphics-3.dll"
  )

list(APPEND _cmake_import_check_targets SFML::Graphics )
list(APPEND _cmake_import_check_files_for_SFML::Graphics "${_IMPORT_PREFIX}/lib/sfml-graphics.lib" "${_IMPORT_PREFIX}/bin/sfml-graphics-3.dll" )

# Import target "SFML::Audio" for configuration "Release"
set_property(TARGET SFML::Audio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Audio PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/sfml-audio.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/sfml-audio-3.dll"
  )

list(APPEND _cmake_import_check_targets SFML::Audio )
list(APPEND _cmake_import_check_files_for_SFML::Audio "${_IMPORT_PREFIX}/lib/sfml-audio.lib" "${_IMPORT_PREFIX}/bin/sfml-audio-3.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)