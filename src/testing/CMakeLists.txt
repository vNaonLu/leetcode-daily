set(TESTING_HELPER_SOURCES
  "test_helper.cc")

add_library(gtest_helper STATIC ${TESTING_HELPER_SOURCES})
target_include_directories(
  gtest_helper
  PUBLIC ${SOURCE_INCLUDES}
)
target_link_libraries(
  gtest_helper
  PUBLIC gtest_main
)