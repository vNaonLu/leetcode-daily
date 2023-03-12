set(SOURCE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(leetcode)

if(${ENABLE_LEETCODE_TEST})
  message(STATUS "Enabled leetcode unittests")
  file(
    GLOB_RECURSE LEECODE_SOURCE
    "q*/*.cc"
  )
  add_executable(leetcode_test ${LEECODE_SOURCE})
  target_link_libraries(
    leetcode_test
    PRIVATE gtest_helper
    PRIVATE leetcode_helper
  )
endif(${ENABLE_LEETCODE_TEST})
