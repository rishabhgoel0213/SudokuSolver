# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/SudokuGame_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/SudokuGame_autogen.dir/ParseCache.txt"
  "SudokuGame_autogen"
  )
endif()
