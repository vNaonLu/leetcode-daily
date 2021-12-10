set(SOURCE
  "main.cc"
  "listnode.cc")
add_executable(infra_test ${SOURCE})
target_include_directories(infra_test 
  PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(infra_test
  PRIVATE gtest_main)