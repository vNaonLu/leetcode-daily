include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

add_executable(unittest unittest.cc)

target_include_directories(unittest 
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
  )

target_link_libraries(unittest 
  PRIVATE
    gtest_main
  )

include(GoogleTest)
gtest_discover_tests(unittest
  PROPERTIES    LABELS "unit"
  DISCOVERY_TIMEOUT     240
  )