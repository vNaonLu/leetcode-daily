// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert Sorted Array to Binary Search Tree
//
// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
//
// Question ID: 108
// Difficult  : Easy
// Solve Date : 2021/10/03 12:07

#include "leetcode/tree_node.h"
#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |108. Convert Sorted Array to Binary Search Tree|:
//
// Given an integer array |nums| where the elements are sorted in ascending
// order, convert it to a height-balanced binary search tree.  
//

LEETCODE_BEGIN_RESOLVING(108, ConvertSortedArrayToBinarySearchTree, Solution);

class Solution {
private:
  template <typename Iterator>
  TreeNode *build(Iterator beg, Iterator end) {
    if (beg == end) {
      return nullptr;
    } else if (beg + 1 == end) {
      return new TreeNode(*beg);
    } else {
      auto mid = beg + distance(beg, end) / 2;
      return new TreeNode(*mid, build(beg, mid), build(mid + 1, end));
    }
  }

public:
  TreeNode *sortedArrayToBST(vector<int> &nums) {
    return build(nums.begin(), nums.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |nums| is sorted in a strictly increasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]
//
// [0,-10,5,null,-3,null,9] is also accepted:
// ![img](https://assets.leetcode.com/uploads/2021/02/18/btree2.jpg)

LEETCODE_SOLUTION_UNITTEST(108, ConvertSortedArrayToBinarySearchTree,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-10, -3, 0, 5, 9};
  TreeNode   *expect   = TreeNode::FromVector({0, -3, 9, -10, null, 5});
  TreeNode   *actual   = solution->sortedArrayToBST(nums);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: nums = [1,3]
// Output: [3,1]
//
// [1,null,3] and [3,1] are both height-balanced BSTs.

LEETCODE_SOLUTION_UNITTEST(108, ConvertSortedArrayToBinarySearchTree,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3};
  TreeNode   *expect   = TreeNode::FromVector({3, 1});
  TreeNode   *actual   = solution->sortedArrayToBST(nums);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}
