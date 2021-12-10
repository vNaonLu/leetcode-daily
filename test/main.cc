#include <gtest/gtest.h>
#include <leetcode/listnode.hpp>

vector<vector<ListNode>> ListNode::keep_ = {};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}