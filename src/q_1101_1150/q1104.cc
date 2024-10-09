// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Path In Zigzag Labelled Binary Tree
//
// https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/
//
// Question ID: 1104
// Difficult  : Medium
// Solve Date : 2024/10/09 14:42

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1104. Path In Zigzag Labelled Binary Tree|:
//
// In an infinite binary tree where every node has two children, the nodes are
// labelled in row order. In the odd numbered rows (ie., the first, third,
// fifth,...), the labelling is left to right, while in the even numbered rows
// (second, fourth, sixth,...), the labelling is right to left.
// ![img](https://assets.leetcode.com/uploads/2019/06/24/tree.png)
// Given the |label| of a node in this tree, return the labels in the path from
// the root of the tree to the node with that |label|.
//
//

LEETCODE_BEGIN_RESOLVING(1104, PathInZigzagLabelledBinaryTree, Solution);

class Solution {
public:
  vector<int> pathInZigZagTree(int label) {
    vector<int> res;
    res.emplace_back(label);
    int d = log2(label);
    while (d) {
      int m = (2 << d) + (2 << (d - 1)) - 1 - label;
      res.emplace_back(m / 2);
      label = m / 2;
      --d;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= label <= 10^6|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: label = 14
// Output: [1,3,4,14]
//

LEETCODE_SOLUTION_UNITTEST(1104, PathInZigzagLabelledBinaryTree, example_1) {
  auto        solution = MakeSolution();
  int         label    = 14;
  vector<int> expect   = {1, 3, 4, 14};
  vector<int> actual   = solution->pathInZigZagTree(label);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: label = 26
// Output: [1,2,6,10,26]
//

LEETCODE_SOLUTION_UNITTEST(1104, PathInZigzagLabelledBinaryTree, example_2) {
  auto        solution = MakeSolution();
  int         label    = 26;
  vector<int> expect   = {1, 2, 6, 10, 26};
  vector<int> actual   = solution->pathInZigZagTree(label);
  LCD_EXPECT_EQ(expect, actual);
}
