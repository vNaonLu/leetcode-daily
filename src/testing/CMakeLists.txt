set(TEST_HELPER_SOURCES "test_helper.cc")

add_library(test_helper STATIC ${TEST_HELPER_SOURCES})

target_include_directories(
  test_helper
  PUBLIC ${SOURCE_INCLUDES}
)

target_link_libraries(
  test_helper
  PUBLIC gtest_main
)