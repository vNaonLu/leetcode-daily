// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Spiral Matrix IV
//
// https://leetcode.com/problems/spiral-matrix-iv/
//
// Question ID: 2326
// Difficult  : Medium
// Solve Date : 2024/09/09 21:34

#include "leetcode/list_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2326. Spiral Matrix IV|:
//
// You are given two integers |m| and |n|, which represent the dimensions of a
// matrix. You are also given the |head| of a linked list of integers. Generate
// an |m x n| matrix that contains the integers in the linked list presented in
// spiral order (clockwise), starting from the top-left of the matrix. If there
// are remaining empty spaces, fill them with |-1|. Return the generated matrix.
//
//

LEETCODE_BEGIN_RESOLVING(2326, SpiralMatrixIV, Solution);

class Solution {
public:
  vector<vector<int>> spiralMatrix(int m, int n, ListNode *head) {
    vector<vector<int>>    res(m, vector<int>(n, -1));
    vector<pair<int, int>> dir{
        { 0,  1},
        { 1,  0},
        { 0, -1},
        {-1,  0}
    };
    pair<int, int> cur{0, 0};
    int            i = 0;
    while (head) {
      auto [x, y] = dir[i % dir.size()];
      auto dx     = cur.first + x;
      auto dy     = cur.second + y;

      if (head->next) {
        if (dx < 0 || dx >= m || dy < 0 || dy >= n || res[dx][dy] != -1) {
          ++i;
          continue;
        }
      }

      res[cur.first][cur.second] = head->val;
      head                       = head->next;
      cur.first                  = dx;
      cur.second                 = dy;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= m, n <= 10⁵|
// * |1 <= m * n <= 10⁵|
// * The number of nodes in the list is in the range |[1, m * n]|.
// * |0 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
// Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
//

LEETCODE_SOLUTION_UNITTEST(2326, SpiralMatrixIV, example_1) {
  auto      solution = MakeSolution();
  int       m        = 3;
  int       n        = 5;
  ListNode *head     = ListNode::FromVector(
      {3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0} /*, looped_index*/);
  vector<vector<int>> expect = {
      {3, 0,  2,  6, 8},
      {5, 0, -1, -1, 1},
      {5, 2,  4,  9, 7}
  };
  vector<vector<int>> actual = solution->spiralMatrix(m, n, head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: m = 1, n = 4, head = [0,1,2]
// Output: [[0,1,2,-1]]
//

LEETCODE_SOLUTION_UNITTEST(2326, SpiralMatrixIV, example_2) {
  auto                solution = MakeSolution();
  int                 m        = 1;
  int                 n        = 4;
  ListNode           *head = ListNode::FromVector({0, 1, 2} /*, looped_index*/);
  vector<vector<int>> expect = {
      {0, 1, 2, -1}
  };
  vector<vector<int>> actual = solution->spiralMatrix(m, n, head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Extra Testcase #1]
//  Input: 10
// 1
// [8,24,5,21,10,11,11,12,6,17]
// Output: [[8],[24],[5],[21],[10],[11],[11],[12],[6],[17]]
//

LEETCODE_SOLUTION_UNITTEST_WITH_TIMED_OUT(2326, SpiralMatrixIV,
                                          extra_testcase_1, 4009) {
  auto      solution = MakeSolution();
  int       m        = 10;
  int       n        = 1;
  ListNode *head     = ListNode::FromVector(
      {8, 24, 5, 21, 10, 11, 11, 12, 6, 17} /*, looped_index*/);
  vector<vector<int>> expect = {{8},  {24}, {5},  {21}, {10},
                                {11}, {11}, {12}, {6},  {17}};
  vector<vector<int>> actual = solution->spiralMatrix(m, n, head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}
