// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Binary Search Trees II
//
// https://leetcode.com/problems/unique-binary-search-trees-ii/
//
// Question ID: 95
// Difficult  : Medium
// Solve Date : 2022/01/19 18:21

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |95. Unique Binary Search Trees II|:
//
// Given an integer |n|, return all the structurally unique BST's (binary search
// trees), which has exactly |n| nodes of unique values from |1| to |n|. Return
// the answer in any order.  
//

LEETCODE_BEGIN_RESOLVING(95, UniqueBinarySearchTreesII, Solution);

class Solution {
private:
  vector<TreeNode *> helper(int beg, int end,
                            map<pair<int, int>, vector<TreeNode *>> &dp) {
    vector<TreeNode *> res;
    if (beg > end) {
      res.push_back(nullptr);
      return res;
    }

    if (dp.count({beg, end}))
      return dp[{beg, end}];

    for (int i = beg; i <= end; ++i) {
      auto left  = helper(beg, i - 1, dp);
      auto right = helper(i + 1, end, dp);
      for (auto l : left) {
        for (auto r : right) {
          TreeNode *p = new TreeNode(i, l, r);
          res.push_back(p);
        }
      }
    }

    dp[{beg, end}] = res;
    return res;
  }

public:
  vector<TreeNode *> generateTrees(int n) {
    map<pair<int, int>, vector<TreeNode *>> dp;
    return helper(1, n, dp);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 8|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output:
// [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
//

LEETCODE_SOLUTION_UNITTEST(95, UniqueBinarySearchTreesII, example_1) {
  auto               solution = MakeSolution();
  int                n        = 3;
  vector<TreeNode *> expect   = {TreeNode::FromVector({1, null, 2, null, 3}),
                                 TreeNode::FromVector({1, null, 3, 2}),
                                 TreeNode::FromVector({2, 1, 3}),
                                 TreeNode::FromVector({3, 1, null, null, 2}),
                                 TreeNode::FromVector({3, 2, null, 1})};
  vector<TreeNode *> actual   = solution->generateTrees(n);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::ReleaseRange(expect.begin(), expect.end());
  TreeNode::ReleaseRange(actual.begin(), actual.end());
}

// [Example #2]
//  Input: n = 1
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(95, UniqueBinarySearchTreesII, example_2) {
  auto               solution = MakeSolution();
  int                n        = 1;
  vector<TreeNode *> expect   = {TreeNode::FromVector({1})};
  vector<TreeNode *> actual   = solution->generateTrees(n);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::ReleaseRange(expect.begin(), expect.end());
  TreeNode::ReleaseRange(actual.begin(), actual.end());
}
