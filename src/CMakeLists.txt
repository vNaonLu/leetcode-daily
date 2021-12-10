file(GLOB_RECURSE FILES "*.cc")
add_executable(leetcode_test ${FILES})
target_include_directories(leetcode_test 
  PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(leetcode_test 
  PRIVATE gtest_main)