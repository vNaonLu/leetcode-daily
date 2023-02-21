


# file(GLOB_RECURSE FILES "*.cc")

# list(REMOVE_ITEM FILES "leetcode/*")

set(SOURCE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

# add_executable(leetcode_test ${FILES})
# target_include_directories(leetcode_test 
#   PRIVATE "${CMAKE_SOURCE_DIR}/include"
#           ${SOURCE_INCLUDES})
# target_link_libraries(leetcode_test 
#   PRIVATE gtest_main)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(testing)
add_subdirectory(leetcode)