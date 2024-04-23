// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Smallest String Starting From Leaf
//
// https://leetcode.com/problems/smallest-string-starting-from-leaf/
//
// Question ID: 988
// Difficult  : Medium
// Solve Date : 2024/04/17 19:39

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |988. Smallest String Starting From Leaf|:
//
// You are given the |root| of a binary tree where each node has a value in the
// range |[0, 25]| representing the letters |'a'| to |'z'|. Return the
// lexicographically smallest string that starts at a leaf of this tree and ends
// at the root. As a reminder, any shorter prefix of a string is
// lexicographically smaller.
//
//  • For example, |"ab"| is lexicographically smaller than |"aba"|.
// A leaf of a node is a node that has no children.
//
//

LEETCODE_BEGIN_RESOLVING(988, SmallestStringStartingFromLeaf, Solution);

class Solution {
public:
  string smallestFromLeaf(TreeNode *root) {
    string res;
    string curr;
    traverse(root, &res, &curr);
    return res;
  }

private:
  void traverse(TreeNode *p, string *res, string *curr) {
    if (!p) {
      return;
    }

    curr->push_back(p->val + 'a');
    if (!p->left && !p->right) {
      string t1 = *res;
      string t2(curr->rbegin(), curr->rend());

      if (t1.empty() || t2 < t1) {
        *res = t2;
      }
    } else {
      traverse(p->left, res, curr);
      traverse(p->right, res, curr);
    }
    curr->pop_back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 8500]|.
// * |0 <= Node.val <= 25|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [0,1,2,3,4,3,4]
// Output: "dba"
//

LEETCODE_SOLUTION_UNITTEST(988, SmallestStringStartingFromLeaf, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0, 1, 2, 3, 4, 3, 4});
  string    expect   = "dba";
  string    actual   = solution->smallestFromLeaf(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [25,1,3,1,3,0,2]
// Output: "adz"
//

LEETCODE_SOLUTION_UNITTEST(988, SmallestStringStartingFromLeaf, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({25, 1, 3, 1, 3, 0, 2});
  string    expect   = "adz";
  string    actual   = solution->smallestFromLeaf(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [2,2,1,null,1,0,null,0]
// Output: "abc"
//

LEETCODE_SOLUTION_UNITTEST(988, SmallestStringStartingFromLeaf, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 2, 1, null, 1, 0, null, 0});
  string    expect   = "abc";
  string    actual   = solution->smallestFromLeaf(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Extra Testcase #1]
//  Input: [0,null,1]
// Output: "ba"
//

LEETCODE_SOLUTION_UNITTEST(988, SmallestStringStartingFromLeaf,
                           extra_testcase_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0, null, 1});
  string    expect   = "ba";
  string    actual   = solution->smallestFromLeaf(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
