// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Most Frequent Subtree Sum
//
// https://leetcode.com/problems/most-frequent-subtree-sum/
//
// Question ID: 508
// Difficult  : Medium
// Solve Date : 2024/04/24 22:56

#include "leetcode/tree_node.h"
#include <algorithm>
#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |508. Most Frequent Subtree Sum|:
//
// Given the |root| of a binary tree, return the most frequent subtree sum. If
// there is a tie, return all the values with the highest frequency in any
// order. The subtree sum of a node is defined as the sum of all the node values
// formed by the subtree rooted at that node (including the node itself).
//
//

LEETCODE_BEGIN_RESOLVING(508, MostFrequentSubtreeSum, Solution);

class Solution {
public:
  vector<int> findFrequentTreeSum(TreeNode *root) {
    map<int, int> mp;
    traverse(root, &mp);
    vector<int> res;
    int         mx_cnt = max_element(mp.begin(), mp.end(), [](auto a, auto b) {
                   return a.second < b.second;
                 })->second;
    for (auto [s, c] : mp) {
      if (c == mx_cnt) {
        res.emplace_back(s);
      }
    }
    return res;
  }

private:
  template <typename T>
  int traverse(TreeNode *p, T *res) {
    if (!p) {
      return 0;
    }

    int left     = traverse(p->left, res);
    int right    = traverse(p->right, res);
    int this_sum = p->val + left + right;

    ++(*res)[this_sum];
    return this_sum;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-10⁵ <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,2,-3]
// Output: [2,-3,4]
//

LEETCODE_SOLUTION_UNITTEST(508, MostFrequentSubtreeSum, example_1) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({5, 2, -3});
  vector<int> expect   = {2, -3, 4};
  vector<int> actual   = solution->findFrequentTreeSum(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [5,2,-5]
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(508, MostFrequentSubtreeSum, example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({5, 2, -5});
  vector<int> expect   = {2};
  vector<int> actual   = solution->findFrequentTreeSum(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}
