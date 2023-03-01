// Copyright 2023 Naon Lu
//
// This file describes the solution of
// All Elements in Two Binary Search Trees
//
// https://leetcode.com/problems/all-elements-in-two-binary-search-trees/
//
// Question ID: 1305
// Difficult  : Medium
// Solve Date : 2022/01/26 18:06

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1305. All Elements in Two Binary Search Trees|:
//
// Given two binary search trees |root1| and |root2|, return a list containing
// all the integers from both trees sorted in ascending order.  
//

LEETCODE_BEGIN_RESOLVING(1305, AllElementsInTwoBinarySearchTrees, Solution);

class Solution {
private:
  void travals(vector<int> &r, TreeNode *p) {
    if (nullptr == p)
      return;
    travals(r, p->left);
    r.emplace_back(p->val);
    travals(r, p->right);
  }

public:
  vector<int> getAllElements(TreeNode *root1, TreeNode *root2) {
    vector<int> res, p1, p2;
    travals(p1, root1);
    travals(p2, root2);
    auto it1 = p1.begin(), it2 = p2.begin();
    while (it1 != p1.end() && it2 != p2.end()) {
      if (*it1 > *it2) {
        res.emplace_back(*it2++);
      } else {
        res.emplace_back(*it1++);
      }
    }
    while (it1 != p1.end())
      res.emplace_back(*it1++);
    while (it2 != p2.end())
      res.emplace_back(*it2++);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in each tree is in the range |[0, 5000]|.
// * |-10⁵ <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root1 = [2,1,4], root2 = [1,0,3]
// Output: [0,1,1,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(1305, AllElementsInTwoBinarySearchTrees, example_1) {
  auto        solution = MakeSolution();
  TreeNode   *root1    = TreeNode::FromVector({2, 1, 4});
  TreeNode   *root2    = TreeNode::FromVector({1, 0, 3});
  vector<int> expect   = {0, 1, 1, 2, 3, 4};
  vector<int> actual   = solution->getAllElements(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2);
}

// [Example #2]
//  Input: root1 = [1,null,8], root2 = [8,1]
// Output: [1,1,8,8]
//

LEETCODE_SOLUTION_UNITTEST(1305, AllElementsInTwoBinarySearchTrees, example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root1    = TreeNode::FromVector({1, null, 8});
  TreeNode   *root2    = TreeNode::FromVector({8, 1});
  vector<int> expect   = {1, 1, 8, 8};
  vector<int> actual   = solution->getAllElements(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2);
}
