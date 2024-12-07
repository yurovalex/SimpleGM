# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/SimpleGM_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/SimpleGM_autogen.dir/ParseCache.txt"
  "SimpleGM_autogen"
  )
endif()
