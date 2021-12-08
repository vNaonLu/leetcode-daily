add_executable(unittest "unittest.cc")
target_include_directories(unittest 
  PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(unittest 
  PRIVATE gtest_main)