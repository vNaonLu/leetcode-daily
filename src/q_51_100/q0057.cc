// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Insert Interval
//
// https://leetcode.com/problems/insert-interval/
//
// Question ID: 57
// Difficult  : Medium
// Solve Date : 2021/12/17 23:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |57. Insert Interval|:
//
// You are given an array of non-overlapping intervals |intervals| where
// |intervals[i] = [startᵢ, endᵢ]| represent the start and the end of the |iᵗʰ|
// interval and |intervals| is sorted in ascending order by |startᵢ|. You are
// also given an interval |newInterval = [start, end]| that represents the start
// and end of another interval. Insert |newInterval| into |intervals| such that
// |intervals| is still sorted in ascending order by |startᵢ| and |intervals|
// still does not have any overlapping intervals (merge overlapping intervals if
// necessary). Return |intervals| after the insertion.  
//

LEETCODE_BEGIN_RESOLVING(57, InsertInterval, Solution);

class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>> &intervals,
                             vector<int>         &newInterval) {
    vector<vector<int>> res;
    for (int i = 0; i < intervals.size(); i++) {
      if (newInterval[1] < intervals[i][0]) {
        res.push_back(newInterval);
        for (int j = i; j < intervals.size(); j++) {
          res.push_back(intervals[j]);
        }
        newInterval.clear();
        break;
      } else {
        if (newInterval[0] <= intervals[i][1]) {
          newInterval[0] = min(newInterval[0], intervals[i][0]);
          newInterval[1] = max(newInterval[1], intervals[i][1]);
        } else {
          res.push_back(intervals[i]);
        }
      }
    }
    if (!newInterval.empty())
      res.push_back(newInterval);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= intervals.length <= 10⁴|
// * |intervals[i].length == 2|
// * |0 <= startᵢ <= endᵢ <= 10⁵|
// * |intervals| is sorted by |startᵢ| in ascending order.
// * |newInterval.length == 2|
// * |0 <= start <= end <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
// Output: [[1,5],[6,9]]
//

LEETCODE_SOLUTION_UNITTEST(57, InsertInterval, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 3},
      {6, 9}
  };
  vector<int>         newInterval = {2, 5};
  vector<vector<int>> expect      = {
      {1, 5},
      {6, 9}
  };
  vector<vector<int>> actual = solution->insert(intervals, newInterval);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
// Output: [[1,2],[3,10],[12,16]]
//
// Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

LEETCODE_SOLUTION_UNITTEST(57, InsertInterval, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      { 1,  2},
      { 3,  5},
      { 6,  7},
      { 8, 10},
      {12, 16}
  };
  vector<int>         newInterval = {4, 8};
  vector<vector<int>> expect      = {
      { 1,  2},
      { 3, 10},
      {12, 16}
  };
  vector<vector<int>> actual = solution->insert(intervals, newInterval);
  LCD_EXPECT_EQ(expect, actual);
}
