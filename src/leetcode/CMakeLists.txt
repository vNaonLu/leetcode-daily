set(LEETCODE_HELPER_SOURCES "list_node.cc")

add_library(leetcode_helper STATIC ${LEETCODE_HELPER_SOURCES})

message(INFO ${SOURCE_INCLUDES})

target_include_directories(
  leetcode_helper
  PUBLIC ${SOURCE_INCLUDES}
)