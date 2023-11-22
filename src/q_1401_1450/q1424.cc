// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Diagonal Traverse II
//
// https://leetcode.com/problems/diagonal-traverse-ii/
//
// Question ID: 1424
// Difficult  : Medium
// Solve Date : 2023/11/22 19:24

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1424. Diagonal Traverse II|:
//
// Given a 2D integer array |nums|, return all elements of |nums| in diagonal
// order as shown in the below images.
//
//

LEETCODE_BEGIN_RESOLVING(1424, DiagonalTraverseII, Solution);

class Solution {
public:
  vector<int> findDiagonalOrder(vector<vector<int>> &nums) {
    vector<int>           res;
    int                   m = nums.size();
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    while (!q.empty()) {
      auto [i, j] = q.front();
      q.pop();
      res.emplace_back(nums[i][j]);

      if (!j && i + 1 < m) {
        q.emplace(i + 1, 0);
      }
      if (j + 1 < nums[i].size()) {
        q.emplace(i, j + 1);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i].length <= 10⁵|
// * |1 <= sum(nums[i].length) <= 10⁵|
// * |1 <= nums[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,4,2,7,5,3,8,6,9]
//

LEETCODE_SOLUTION_UNITTEST(1424, DiagonalTraverseII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  vector<int> expect = {1, 4, 2, 7, 5, 3, 8, 6, 9};
  vector<int> actual = solution->findDiagonalOrder(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
// Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
//

LEETCODE_SOLUTION_UNITTEST(1424, DiagonalTraverseII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {1, 2, 3, 4, 5},
      {6, 7},
      {8},
      {9, 10, 11},
      {12, 13, 14, 15, 16}
  };
  vector<int> expect = {1, 6, 2, 8, 7, 3, 9, 4, 12, 10, 5, 13, 11, 14, 15, 16};
  vector<int> actual = solution->findDiagonalOrder(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[14,12,19,16,9],[13,14,15,8,11],[11,13,1]]
// Output: [14,13,12,11,14,19,13,15,16,1,8,9,11]
//

LEETCODE_SOLUTION_UNITTEST(1424, DiagonalTraverseII, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {14, 12, 19, 16, 9},
      {13, 14, 15, 8, 11},
      {11, 13, 1}
  };
  vector<int> expect = {14, 13, 12, 11, 14, 19, 13, 15, 16, 1, 8, 9, 11};
  vector<int> actual = solution->findDiagonalOrder(nums);
  LCD_EXPECT_EQ(expect, actual);
}
