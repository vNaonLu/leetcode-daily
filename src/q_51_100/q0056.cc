// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Merge Intervals
//
// https://leetcode.com/problems/merge-intervals/
//
// Question ID: 56
// Difficult  : Medium
// Solve Date : 2021/09/20 08:00

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |56. Merge Intervals|:
//
// Given an array of |intervals| where |intervals[i] = [startᵢ, endᵢ]|, merge
// all overlapping intervals, and return an array of the non-overlapping
// intervals that cover all the intervals in the input.  
//

LEETCODE_BEGIN_RESOLVING(56, MergeIntervals, Solution);

class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    if (intervals.size() == 0)
      return vector<vector<int>>();
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ret;
    vector<int>         cur;
    for (int i = 0; i < intervals.size(); i++) {
      if (cur.empty()) {
        cur = intervals[i];
      } else {
        if (cur[1] >= intervals[i][0]) {
          cur[1] = max(intervals[i][1], cur[1]);
        } else {
          ret.push_back(cur);
          cur = intervals[i];
        }
      }
    }
    if (!cur.empty())
      ret.push_back(cur);
    return ret;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= intervals.length <= 10⁴|
// * |intervals[i].length == 2|
// * |0 <= startᵢ <= endᵢ <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
//
// Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

LEETCODE_SOLUTION_UNITTEST(56, MergeIntervals, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      { 1,  3},
      { 2,  6},
      { 8, 10},
      {15, 18}
  };
  vector<vector<int>> expect = {
      { 1,  6},
      { 8, 10},
      {15, 18}
  };
  vector<vector<int>> actual = solution->merge(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: intervals = [[1,4],[4,5]]
// Output: [[1,5]]
//
// Intervals [1,4] and [4,5] are considered overlapping.

LEETCODE_SOLUTION_UNITTEST(56, MergeIntervals, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 4},
      {4, 5}
  };
  vector<vector<int>> expect = {
      {1, 5}
  };
  vector<vector<int>> actual = solution->merge(intervals);
  LCD_EXPECT_EQ(expect, actual);
}
