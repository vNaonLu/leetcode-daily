set(LEETCODE_HELPER_SOURCES "list_node.cc")
add_library(leetcode_helper STATIC ${LEETCODE_HELPER_SOURCES})
target_include_directories(
  leetcode_helper
  PUBLIC ${SOURCE_INCLUDES}
)

if(${ENABLE_INFRA_TEST})
  message(STATUS "ENABLE_INFRA_TEST = ${ENABLE_INFRA_TEST}")
  set(LEETCODE_HELPER_TEST_SOURCES "list_node_unittest.cc")
  add_executable(leetcode_helper_test ${LEETCODE_HELPER_TEST_SOURCES})
  target_link_libraries(
    leetcode_helper_test
    PRIVATE leetcode_helper
    PRIVATE gtest_main
  )
endif(${ENABLE_INFRA_TEST})
