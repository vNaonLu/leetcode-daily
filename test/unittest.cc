#include <gtest/gtest.h>

#include <iostream>

#include "q0001_unittest.hpp"
#include "q0088_unittest.hpp"
#include "q0167_unittest.hpp"
#include "q0189_unittest.hpp"
#include "q0206_unittest.hpp"
#include "q0283_unittest.hpp"
#include "q0977_unittest.hpp"
#include "q1629_unittest.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return ::RUN_ALL_TESTS();
}