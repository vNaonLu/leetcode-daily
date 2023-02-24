add_library(gtest_helper INTERFACE)
target_include_directories(
  gtest_helper
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(
  gtest_helper
  INTERFACE gtest_main
)