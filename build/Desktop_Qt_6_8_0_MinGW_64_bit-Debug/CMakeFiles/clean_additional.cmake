# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\LibraryApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LibraryApp_autogen.dir\\ParseCache.txt"
  "LibraryApp_autogen"
  )
endif()
