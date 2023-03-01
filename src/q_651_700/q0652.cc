// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Duplicate Subtrees
//
// https://leetcode.com/problems/find-duplicate-subtrees/
//
// Question ID: 652
// Difficult  : Medium
// Solve Date : 2023/02/28 14:40

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |652. Find Duplicate Subtrees|:
//
// Given the |root|of a binary tree, return all duplicate subtrees.
// For each kind of duplicate subtrees, you only need to return the root node of
// any one of them. Two trees are duplicate if they have the same structure with
// the same node values.
//

LEETCODE_BEGIN_RESOLVING(652, FindDuplicateSubtrees, Solution);

class Solution {
private:
  string findDuplicates(TreeNode *node, unordered_map<string, int> &frequency,
                        vector<TreeNode *> &result) {
    if (!node) {
      return "#";
    }

    string leftIdentifier  = findDuplicates(node->left, frequency, result);
    string rightIdentifier = findDuplicates(node->right, frequency, result);
    string identifier =
        to_string(node->val) + "," + leftIdentifier + "," + rightIdentifier;
    frequency[identifier]++;

    if (frequency[identifier] == 2) {
      result.push_back(node);
    }

    return identifier;
  }

public:
  vector<TreeNode *> findDuplicateSubtrees(TreeNode *root) {
    unordered_map<string, int> frequency;
    vector<TreeNode *>         result;
    findDuplicates(root, frequency, result);
    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of the nodes in the tree will be in the range |[1, 5000]|
// * |-200 <= Node.val <= 200|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4,null,2,4,null,null,4]
// Output: [[2,4],[4]]
//

LEETCODE_SOLUTION_UNITTEST(652, FindDuplicateSubtrees, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({1, 2, 3, 4, null, 2, 4, null, null, 4});
  vector<TreeNode *> expect = {TreeNode::FromVector({2, 4}),
                               TreeNode::FromVector({4})};
  vector<TreeNode *> actual = solution->findDuplicateSubtrees(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [2,1,1]
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(652, FindDuplicateSubtrees, example_2) {
  auto               solution = MakeSolution();
  TreeNode          *root     = TreeNode::FromVector({2, 1, 1});
  vector<TreeNode *> expect   = {TreeNode::FromVector({1})};
  vector<TreeNode *> actual   = solution->findDuplicateSubtrees(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [2,2,2,3,null,3,null]
// Output: [[2,3],[3]]
//

LEETCODE_SOLUTION_UNITTEST(652, FindDuplicateSubtrees, example_3) {
  auto               solution = MakeSolution();
  TreeNode          *root   = TreeNode::FromVector({2, 2, 2, 3, null, 3, null});
  vector<TreeNode *> expect = {TreeNode::FromVector({2, 3}),
                               TreeNode::FromVector({3})};
  vector<TreeNode *> actual = solution->findDuplicateSubtrees(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}
