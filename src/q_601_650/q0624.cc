// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Distance in Arrays
//
// https://leetcode.com/problems/maximum-distance-in-arrays/
//
// Question ID: 624
// Difficult  : Medium
// Solve Date : 2024/08/16 19:08

#include <iosfwd>
#include <ranges>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |624. Maximum Distance in Arrays|:
//
// You are given |m| |arrays|, where each array is sorted in ascending order.
// You can pick up two integers from two different arrays (each array picks one)
// and calculate the distance. We define the distance between two integers |a|
// and |b| to be their absolute difference ||a - b||. Return the maximum
// distance.
//
//

LEETCODE_BEGIN_RESOLVING(624, MaximumDistanceInArrays, Solution);

class Solution {
public:
  int maxDistance(vector<vector<int>> &arrays) {
    int res = 0;
    int mx  = arrays[0].back();
    int mn  = arrays[0].front();
    for (auto &v : ranges::subrange(arrays.begin() + 1, arrays.end())) {
      res = max(res, abs(v.back() - mn));
      res = max(res, abs(mx - v.front()));
      mn  = min(mn, v.front());
      mx  = max(mx, v.back());
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == arrays.length|
// * |2 <= m <= 10⁵|
// * |1 <= arrays[i].length <= 500|
// * |-10⁴ <= arrays[i][j] <= 10⁴|
// * |arrays[i]| is sorted in ascending order.
// * There will be at most |10⁵| integers in all the arrays.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arrays = [[1,2,3],[4,5],[1,2,3]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(624, MaximumDistanceInArrays, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> arrays   = {
      {1, 2, 3},
      {4, 5},
      {1, 2, 3}
  };
  int expect = 4;
  int actual = solution->maxDistance(arrays);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arrays = [[1],[1]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(624, MaximumDistanceInArrays, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> arrays   = {{1}, {1}};
  int                 expect   = 0;
  int                 actual   = solution->maxDistance(arrays);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[1,5],[3,4]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(624, MaximumDistanceInArrays, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> arrays   = {
      {1, 5},
      {3, 4}
  };
  int expect = 3;
  int actual = solution->maxDistance(arrays);
  LCD_EXPECT_EQ(expect, actual);
}
