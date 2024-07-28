// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Number of Good Leaf Nodes Pairs
//
// https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/
//
// Question ID: 1530
// Difficult  : Medium
// Solve Date : 2024/07/18 20:27

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1530. Number of Good Leaf Nodes Pairs|:
//
// You are given the |root| of a binary tree and an integer |distance|. A pair
// of two different leaf nodes of a binary tree is said to be good if the length
// of the shortest path between them is less than or equal to |distance|. Return
// the number of good leaf node pairs in the tree.
//
//

LEETCODE_BEGIN_RESOLVING(1530, NumberOfGoodLeafNodesPairs, Solution);

class Solution {
public:
  int countPairs(TreeNode *root, int distance) {
    int            res = 0;
    vector<string> path;
    string         st;
    getPath(root, &path, &st);
    for (int i = 0; i < path.size(); ++i) {
      for (int j = i + 1; j < path.size(); ++j) {
        if (path[i][0] == path[j][0]) {
          int k   = 1;
          int tmp = 0;
          while (k < path[i].size() && k < path[j].size()) {
            if (path[i][k] != path[j][k]) {
              break;
            }
            ++k;
          }
          tmp += ((path[i].size() - k) + (path[j].size() - k));
          if (tmp <= distance) {
            ++res;
          }
        } else {
          int tmp = path[i].size() + path[j].size();
          if (tmp <= distance) {
            ++res;
          }
        }
      }
    }
    return res;
  }

private:
  void getPath(TreeNode *p, vector<string> *res, string *st) {
    if (!p) {
      return;
    }

    if (!p->left && !p->right) {
      res->push_back(*st);
    }

    if (p->left) {
      *st += 'l';
      getPath(p->left, res, st);
      st->pop_back();
    }

    if (p->right) {
      *st += 'r';
      getPath(p->right, res, st);
      st->pop_back();
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the |tree| is in the range |[1, 2¹⁰].|
// * |1 <= Node.val <= 100|
// * |1 <= distance <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,null,4], distance = 3
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1530, NumberOfGoodLeafNodesPairs, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, null, 4});
  int       distance = 3;
  int       expect   = 1;
  int       actual   = solution->countPairs(root, distance);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3,4,5,6,7], distance = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1530, NumberOfGoodLeafNodesPairs, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 4, 5, 6, 7});
  int       distance = 3;
  int       expect   = 2;
  int       actual   = solution->countPairs(root, distance);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1530, NumberOfGoodLeafNodesPairs, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {7, 1, 4, 6, null, 5, 3, null, null, null, null, null, 2});
  int distance = 3;
  int expect   = 1;
  int actual   = solution->countPairs(root, distance);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
