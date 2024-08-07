set(SOURCE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 391ce627def20c1e8a54d10b12949b15086473dd)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(leetcode)

if(${ENABLE_LEETCODE_TEST})
  set(LEECODE_SOURCE)

  if(${ENABLE_UNITED_BUILD})
    file(GLOB MENIFEST_DIRS LIST_DIRECTORIES TRUE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")

    foreach(MENIFEST_NAME ${MENIFEST_DIRS})
      set(MENIFEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${MENIFEST_NAME}")

      if(NOT IS_DIRECTORY ${MENIFEST_DIR} OR ${MENIFEST_DIR} STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/leetcode")
        continue()
      endif(NOT IS_DIRECTORY ${MENIFEST_DIR} OR ${MENIFEST_DIR} STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/leetcode")

      file(
        GLOB_RECURSE MENIFEST_SOURCE
        "${MENIFEST_DIR}/*.cc"
      )

      set(UNITY_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${MENIFEST_NAME}.unity.cc")
      file(REMOVE ${UNITY_SOURCE})

      foreach(SOLUTION ${MENIFEST_SOURCE})
        if(${SOLUTION} STREQUAL ${UNITY_SOURCE})
          continue()
        endif(${SOLUTION} STREQUAL ${UNITY_SOURCE})

        file(STRINGS ${SOLUTION} SOLUTION_CONTENT NEWLINE_CONSUME)

        # remove comments
        set(COMPRESSED_SOLUTION_CONTENT "${SOLUTION_CONTENT}")
        string(REGEX REPLACE "\n+" "\n" COMPRESSED_SOLUTION_CONTENT "${COMPRESSED_SOLUTION_CONTENT}")
        string(REGEX REPLACE "\\\\;" ";" COMPRESSED_SOLUTION_CONTENT "${COMPRESSED_SOLUTION_CONTENT}")

        file(APPEND ${UNITY_SOURCE} "${COMPRESSED_SOLUTION_CONTENT}")
      endforeach()

      list(APPEND LEECODE_SOURCE ${UNITY_SOURCE})
      message(VERBOSE "Unified ${MENIFEST_NAME} solutions: ${UNITY_SOURCE}")
    endforeach()
  elseif(NOT "${ENABLE_BUILD_PARTIAL_SOURCE}" STREQUAL "")
    message(STATUS "Enabled partial leetcode unittests")
    set(LEECODE_SOURCE)
    foreach(V ${ENABLE_BUILD_PARTIAL_SOURCE})
      string(REGEX REPLACE "^([1-9][1-9][1-9][1-9])$" "q*/q\\1.cc" VAR ${V})
      string(REGEX REPLACE "^([1-9][1-9][1-9])$" "q*/q0\\1.cc" VAR ${VAR})
      string(REGEX REPLACE "^([1-9][1-9])$" "q*/q00\\1.cc" VAR ${VAR})
      string(REGEX REPLACE "^([1-9])$" "q*/q000\\1.cc" VAR ${VAR})
      file(
        GLOB_RECURSE SOURCE
        "${VAR}"
      )
      list(APPEND LEECODE_SOURCE ${SOURCE})
    endforeach(V ${ENABLE_BUILD_PARTIAL_SOURCE})
  else()
    message(STATUS "Enabled leetcode unittests")
    file(
      GLOB_RECURSE LEECODE_SOURCE
      "q*/*.cc"
    )
  endif()

  add_executable(leetcode_test ${LEECODE_SOURCE})
  target_link_libraries(
    leetcode_test
    PRIVATE gtest_helper
  )
endif(${ENABLE_LEETCODE_TEST})
