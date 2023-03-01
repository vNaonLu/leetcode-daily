// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Validate Binary Tree Nodes
//
// https://leetcode.com/problems/validate-binary-tree-nodes/
//
// Question ID: 1361
// Difficult  : Medium
// Solve Date : 2021/10/17 15:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1361. Validate Binary Tree Nodes|:
//
// You have |n| binary tree nodes numbered from |0| to |n - 1| where node |i|
// has two children |leftChild[i]| and |rightChild[i]|, return |true| if and
// only if all the given nodes form exactly one valid binary tree. If node |i|
// has no left child then |leftChild[i]| will equal |-1|, similarly for the
// right child. Note that the nodes have no values and that we only use the node
// numbers in this problem.  
//

LEETCODE_BEGIN_RESOLVING(1361, ValidateBinaryTreeNodes, Solution);

class Solution {
private:
  vector<int>  indegree;
  vector<bool> visited;
  vector<bool> visiting;
  bool         hasCycle(int n, const vector<int> &l, const vector<int> &r) {
    if (n >= 0) {
      if (visiting[n]) {
        return true;
      } else if (visited[n]) {
        ++indegree[n];
        return false;
      }
      visiting[n] = true;
      if (hasCycle(l[n], l, r) || hasCycle(r[n], l, r))
        return true;
      visiting[n] = false;
      visited[n]  = true;
    }
    return false;
  }

public:
  bool validateBinaryTreeNodes(int n, vector<int> &leftChild,
                               vector<int> &rightChild) {
    indegree.resize(n, 0);
    visited.resize(n, false);
    visiting.resize(n, false);
    for (int i = 0; i < n; ++i)
      if (hasCycle(i, leftChild, rightChild))
        return false;
    int root = 0;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] > 1)
        return false;
      if (indegree[i] == 0)
        ++root;
    }
    return root == 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == leftChild.length == rightChild.length|
// * |1 <= n <= 10⁴|
// * |-1 <= leftChild[i], rightChild[i] <= n - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1361, ValidateBinaryTreeNodes, example_1) {
  auto        solution   = MakeSolution();
  int         n          = 4;
  vector<int> leftChild  = {1, -1, 3, -1};
  vector<int> rightChild = {2, -1, -1, -1};
  bool        expect     = true;
  bool actual = solution->validateBinaryTreeNodes(n, leftChild, rightChild);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1361, ValidateBinaryTreeNodes, example_2) {
  auto        solution   = MakeSolution();
  int         n          = 4;
  vector<int> leftChild  = {1, -1, 3, -1};
  vector<int> rightChild = {2, 3, -1, -1};
  bool        expect     = false;
  bool actual = solution->validateBinaryTreeNodes(n, leftChild, rightChild);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1361, ValidateBinaryTreeNodes, example_3) {
  auto        solution   = MakeSolution();
  int         n          = 2;
  vector<int> leftChild  = {1, 0};
  vector<int> rightChild = {-1, -1};
  bool        expect     = false;
  bool actual = solution->validateBinaryTreeNodes(n, leftChild, rightChild);
  LCD_EXPECT_EQ(expect, actual);
}
