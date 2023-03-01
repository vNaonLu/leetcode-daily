// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Binary Tree
//
// https://leetcode.com/problems/maximum-binary-tree/
//
// Question ID: 654
// Difficult  : Medium
// Solve Date : 2022/06/05 13:57

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |654. Maximum Binary Tree|:
//
// You are given an integer array |nums| with no duplicates. A maximum binary
// tree can be built recursively from |nums| using the following algorithm:
//
//  1. Create a root node whose value is the maximum value in |nums|.
//
//  2. Recursively build the left subtree on the subarray prefix to the left of
//  the maximum value.
//
//  3. Recursively build the right subtree on the subarray suffix to the right
//  of the maximum value.
// Return the maximum binary tree built from |nums|.
//

LEETCODE_BEGIN_RESOLVING(654, MaximumBinaryTree, Solution);

class Solution {
private:
  template <typename Iter>
  TreeNode *buildTree(Iter curr, Iter beg, Iter end) {
    if (curr == end) {
      return nullptr;
    }

    auto left  = buildTree(max_element(beg, curr), beg, curr),
         right = buildTree(max_element(curr + 1, end), curr + 1, end);

    return new TreeNode(*curr, left, right);
  }

public:
  TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
    return buildTree(max_element(nums.begin(), nums.end()), nums.begin(),
                     nums.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |0 <= nums[i] <= 1000|
// * All integers in |nums| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,1,6,0,5]
// Output: [6,3,5,null,2,0,null,null,1]
//
// The recursive calls are as follow:
// - The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right
// suffix is [0,5].
//  - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is
//  [2,1].
//  - Empty array, so no child.
//  - The largest value in [2,1] is 2. Left prefix is [] and right suffix is
//  [1].
//  - Empty array, so no child.
//  - Only one element, so child is a node with value 1.
//  - The largest value in [0,5] is 5. Left prefix is [0] and right suffix is
//  [].
//  - Only one element, so child is a node with value 0.
//  - Empty array, so no child.

LEETCODE_SOLUTION_UNITTEST(654, MaximumBinaryTree, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 6, 0, 5};
  TreeNode *expect = TreeNode::FromVector({6, 3, 5, null, 2, 0, null, null, 1});
  TreeNode *actual = solution->constructMaximumBinaryTree(nums);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,1]
// Output: [3,null,2,null,1]
//

LEETCODE_SOLUTION_UNITTEST(654, MaximumBinaryTree, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1};
  TreeNode   *expect   = TreeNode::FromVector({3, null, 2, null, 1});
  TreeNode   *actual   = solution->constructMaximumBinaryTree(nums);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}
