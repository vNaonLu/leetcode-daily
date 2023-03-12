add_subdirectory(testing)

set(LEETCODE_HELPER_SOURCES
  "list_node.cc"
  "tree_node.cc")

add_library(leetcode_helper STATIC ${LEETCODE_HELPER_SOURCES})
target_include_directories(
  leetcode_helper
  PUBLIC ${SOURCE_INCLUDES}
)

message(STATUS "ENABLE_INFRA_TEST = ${ENABLE_INFRA_TEST}")

if(${ENABLE_INFRA_TEST})
  message(STATUS "Enabled infrastructure unittests")
  set(LEETCODE_HELPER_TEST_SOURCES
    "solution_unittest.cc"
    "expect_anyorder_unittest.cc"
    "list_node_unittest.cc"
    "tree_node_unittest.cc")

  add_executable(leetcode_helper_test ${LEETCODE_HELPER_TEST_SOURCES})
  target_link_libraries(
    leetcode_helper_test
    PRIVATE gtest_helper
    PRIVATE leetcode_helper
  )
endif(${ENABLE_INFRA_TEST})
