# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/CRMsystem_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CRMsystem_autogen.dir/ParseCache.txt"
  "CRMsystem_autogen"
  )
endif()
