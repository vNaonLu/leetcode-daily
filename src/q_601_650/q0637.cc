// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Average of Levels in Binary Tree
//
// https://leetcode.com/problems/average-of-levels-in-binary-tree/
//
// Question ID: 637
// Difficult  : Easy
// Solve Date : 2022/09/02 20:17

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |637. Average of Levels in Binary Tree|:
//
// Given the |root| of a binary tree, return the average value of the nodes on
// each level in the form of an array. Answers within |10⁻⁵| of the actual
// answer will be accepted.
//

LEETCODE_BEGIN_RESOLVING(637, AverageOfLevelsInBinaryTree, Solution);

class Solution {
private:
  void solve(TreeNode *p, vector<vector<int64_t>> &vals, int lvl = 0) {
    if (nullptr == p) {
      return;
    }

    if (lvl >= vals.size()) {
      vals.resize(lvl + 1);
    }

    vals[lvl].emplace_back(p->val);
    solve(p->left, vals, lvl + 1);
    solve(p->right, vals, lvl + 1);
  }

public:
  vector<double> averageOfLevels(TreeNode *root) {
    auto res = vector<double>();
    auto cnt = vector<vector<int64_t>>();
    solve(root, cnt);
    for (auto &v : cnt) {
      res.emplace_back(accumulate(v.begin(), v.end(), 0.0) /
                       static_cast<double>(v.size()));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-2³¹ <= Node.val <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,9,20,null,null,15,7]
// Output: [3.00000,14.50000,11.00000]
// Explanation: The average value of nodes on level 0 is 3, on level 1 is 14.5,
// and on level 2 is 11. Hence return [3, 14.5, 11].
//

LEETCODE_SOLUTION_UNITTEST(637, AverageOfLevelsInBinaryTree, example_1) {
  auto           solution = MakeSolution();
  TreeNode      *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  vector<double> expect   = {3.00000, 14.50000, 11.00000};
  vector<double> actual   = solution->averageOfLevels(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [3,9,20,15,7]
// Output: [3.00000,14.50000,11.00000]
//

LEETCODE_SOLUTION_UNITTEST(637, AverageOfLevelsInBinaryTree, example_2) {
  auto           solution = MakeSolution();
  TreeNode      *root     = TreeNode::FromVector({3, 9, 20, 15, 7});
  vector<double> expect   = {3.00000, 14.50000, 11.00000};
  vector<double> actual   = solution->averageOfLevels(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
