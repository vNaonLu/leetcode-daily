// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Non-overlapping Intervals
//
// https://leetcode.com/problems/non-overlapping-intervals/
//
// Question ID: 435
// Difficult  : Medium
// Solve Date : 2021/09/22 08:00

#include <iosfwd>
#include <limits>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |435. Non-overlapping Intervals|:
//
// Given an array of intervals |intervals| where |intervals[i] = [startᵢ,
// endᵢ]|, return the minimum number of intervals you need to remove to make the
// rest of the intervals non-overlapping.  
//

LEETCODE_BEGIN_RESOLVING(435, NonOverlappingIntervals, Solution);

class Solution {
public:
  int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    set<pair<int, int>> uniq_intv;
    for (const auto &intv : intervals)
      uniq_intv.insert({intv[1], intv[0]});
    int res = intervals.size();
    int end = numeric_limits<int>::min();
    for (const auto &intv : uniq_intv) {
      if (intv.second >= end || intv.first < end) {
        --res;
        end = intv.first;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= intervals.length <= 10⁵|
// * |intervals[i].length == 2|
// * |-5 * 10⁴ <= startᵢ < endᵢ <= 5 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
// Output: 1
//
// [1,3] can be removed and the rest of the intervals are non-overlapping.

LEETCODE_SOLUTION_UNITTEST(435, NonOverlappingIntervals, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 2},
      {2, 3},
      {3, 4},
      {1, 3}
  };
  int expect = 1;
  int actual = solution->eraseOverlapIntervals(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: intervals = [[1,2],[1,2],[1,2]]
// Output: 2
//
// You need to remove two [1,2] to make the rest of the intervals
// non-overlapping.

LEETCODE_SOLUTION_UNITTEST(435, NonOverlappingIntervals, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 2},
      {1, 2},
      {1, 2}
  };
  int expect = 2;
  int actual = solution->eraseOverlapIntervals(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: intervals = [[1,2],[2,3]]
// Output: 0
//
// You don't need to remove any of the intervals since they're already
// non-overlapping.

LEETCODE_SOLUTION_UNITTEST(435, NonOverlappingIntervals, example_3) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 2},
      {2, 3}
  };
  int expect = 0;
  int actual = solution->eraseOverlapIntervals(intervals);
  LCD_EXPECT_EQ(expect, actual);
}
