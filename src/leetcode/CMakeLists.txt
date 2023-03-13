set(LEETCODE_HELPER_SOURCES
  "list_node.cc"
  "tree_node.cc")

add_library(leetcode_helper STATIC ${LEETCODE_HELPER_SOURCES})
target_include_directories(
  leetcode_helper
  PUBLIC ${SOURCE_INCLUDES}
)

if(${ENABLE_LEETCODE_TEST} OR ${ENABLE_INFRA_TEST})
  add_library(
    gtest_helper
    STATIC ${CMAKE_CURRENT_SOURCE_DIR}/testing/solution_test_helper.cc)
  target_include_directories(
    gtest_helper
    PUBLIC ${SOURCE_INCLUDES}
  )
  target_link_libraries(
    gtest_helper
    PUBLIC leetcode_helper
    PUBLIC gtest_main
  )
endif(${ENABLE_LEETCODE_TEST} OR ${ENABLE_INFRA_TEST})


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
  )
endif(${ENABLE_INFRA_TEST})
