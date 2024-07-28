// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Step-By-Step Directions From a Binary Tree Node to Another
//
// https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/
//
// Question ID: 2096
// Difficult  : Medium
// Solve Date : 2024/07/16 19:52

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2096. Step-By-Step Directions From a Binary Tree Node to
// Another|:
//
// You are given the |root| of a binary tree with |n| nodes. Each node is
// uniquely assigned a value from |1| to |n|. You are also given an integer
// |startValue| representing the value of the start node |s|, and a different
// integer |destValue| representing the value of the destination node |t|. Find
// the shortest path starting from node |s| and ending at node |t|. Generate
// step-by-step directions of such path as a string consisting of only the
// uppercase letters |'L'|, |'R'|, and |'U'|. Each letter indicates a specific
// direction:
//
//  • |'L'| means to go from a node to its left child node.
//
//  • |'R'| means to go from a node to its right child node.
//
//  • |'U'| means to go from a node to its parent node.
// Return the step-by-step directions of the shortest path from node |s| to node
// |t|.
//
//

LEETCODE_BEGIN_RESOLVING(2096, StepByStepDirectionsFromABinaryTreeNodeToAnother,
                         Solution);

class Solution {
public:
  string getDirections(TreeNode *root, int startValue, int destValue) {
    string to_beg;
    string to_end;
    find(root, startValue, &to_beg);
    find(root, destValue, &to_end);
    while (!to_beg.empty() && !to_end.empty() &&
           to_beg.back() == to_end.back()) {
      to_beg.pop_back();
      to_end.pop_back();
    }
    reverse(to_end.begin(), to_end.end());
    return string(to_beg.size(), 'U') + to_end;
  }

private:
  bool find(TreeNode *p, int val, string *path) {
    if (p->val == val) {
      return true;
    }

    if (p->left && find(p->left, val, path)) {
      path->push_back('L');
    } else if (p->right && find(p->right, val, path)) {
      path->push_back('R');
    }

    return !path->empty();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is |n|.
// * |2 <= n <= 10⁵|
// * |1 <= Node.val <= n|
// * All the values in the tree are unique.
// * |1 <= startValue, destValue <= n|
// * |startValue != destValue|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
// Output: "UURL"
//

LEETCODE_SOLUTION_UNITTEST(2096,
                           StepByStepDirectionsFromABinaryTreeNodeToAnother,
                           example_1) {
  auto      solution   = MakeSolution();
  TreeNode *root       = TreeNode::FromVector({5, 1, 2, 3, null, 6, 4});
  int       startValue = 3;
  int       destValue  = 6;
  string    expect     = "UURL";
  string    actual     = solution->getDirections(root, startValue, destValue);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [2,1], startValue = 2, destValue = 1
// Output: "L"
//

LEETCODE_SOLUTION_UNITTEST(2096,
                           StepByStepDirectionsFromABinaryTreeNodeToAnother,
                           example_2) {
  auto      solution   = MakeSolution();
  TreeNode *root       = TreeNode::FromVector({2, 1});
  int       startValue = 2;
  int       destValue  = 1;
  string    expect     = "L";
  string    actual     = solution->getDirections(root, startValue, destValue);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
