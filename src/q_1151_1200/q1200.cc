// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Absolute Difference
//
// https://leetcode.com/problems/minimum-absolute-difference/
//
// Question ID: 1200
// Difficult  : Easy
// Solve Date : 2021/12/20 18:07

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1200. Minimum Absolute Difference|:
//
// Given an array of distinct integers |arr|, find all pairs of elements with
// the minimum absolute difference of any two elements. Return a list of pairs
// in ascending order(with respect to pairs), each pair |[a, b]| follows
//
//  • |a, b| are from |arr|
//
//  • |a < b|
//
//  • |b - a| equals to the minimum absolute difference of any two elements in
//  |arr|
//  
//

LEETCODE_BEGIN_RESOLVING(1200, MinimumAbsoluteDifference, Solution);

class Solution {
public:
  vector<vector<int>> minimumAbsDifference(vector<int> &arr) {
    int max_elem = numeric_limits<int>::min(),
        min_elem = numeric_limits<int>::max();
    for (const auto &x : arr) {
      max_elem = max(max_elem, x);
      min_elem = min(min_elem, x);
    }
    int                 shift    = -min_elem;
    int                 min_diff = max_elem - min_elem;
    int                 prev     = 0;
    vector<uint8_t>     line(max_elem - min_elem + 1);
    vector<vector<int>> res;
    for (const auto &x : arr)
      line[x + shift] = 1;
    for (int cur = 1; cur <= max_elem + shift; ++cur) {
      if (line[cur] == 0)
        continue;
      int diff = cur - prev;
      if (diff == min_diff)
        res.push_back({prev - shift, cur - shift});
      else if (diff < min_diff) {
        min_diff = diff;
        res      = {
            {prev - shift, cur - shift}
        };
      }
      prev = cur;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= arr.length <= 10⁵|
// * |-10⁶ <= arr[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [4,2,1,3]
// Output: [[1,2],[2,3],[3,4]]
//
// The minimum absolute difference is 1. List all pairs with difference equal to
// 1 in ascending order.

LEETCODE_SOLUTION_UNITTEST(1200, MinimumAbsoluteDifference, example_1) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {4, 2, 1, 3};
  vector<vector<int>> expect   = {
      {1, 2},
      {2, 3},
      {3, 4}
  };
  vector<vector<int>> actual = solution->minimumAbsDifference(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,3,6,10,15]
// Output: [[1,3]]
//

LEETCODE_SOLUTION_UNITTEST(1200, MinimumAbsoluteDifference, example_2) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {1, 3, 6, 10, 15};
  vector<vector<int>> expect   = {
      {1, 3}
  };
  vector<vector<int>> actual = solution->minimumAbsDifference(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [3,8,-10,23,19,-4,-14,27]
// Output: [[-14,-10],[19,23],[23,27]]
//

LEETCODE_SOLUTION_UNITTEST(1200, MinimumAbsoluteDifference, example_3) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {3, 8, -10, 23, 19, -4, -14, 27};
  vector<vector<int>> expect   = {
      {-14, -10},
      { 19,  23},
      { 23,  27}
  };
  vector<vector<int>> actual = solution->minimumAbsDifference(arr);
  LCD_EXPECT_EQ(expect, actual);
}
