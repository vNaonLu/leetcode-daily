// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Covered Intervals
//
// https://leetcode.com/problems/remove-covered-intervals/
//
// Question ID: 1288
// Difficult  : Medium
// Solve Date : 2022/02/20 14:19

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1288. Remove Covered Intervals|:
//
// Given an array |intervals| where |intervals[i] = [lᵢ, rᵢ]| represent the
// interval |[lᵢ, rᵢ)|, remove all intervals that are covered by another
// interval in the list. The interval |[a, b)| is covered by the interval |[c,
// d)| if and only if |c <= a| and |b <= d|. Return the number of remaining
// intervals.  
//

LEETCODE_BEGIN_RESOLVING(1288, RemoveCoveredIntervals, Solution);

class Solution {
public:
  int removeCoveredIntervals(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end(),
         [](const vector<int> &x, const vector<int> &y) {
           return x[0] == y[0] ? x[1] > y[1] : x[0] < y[0];
         });
    int         res  = intervals.size();
    vector<int> curr = intervals.front();
    for (auto it = intervals.begin() + 1; it != intervals.end(); ++it) {
      int l = curr[0], r = curr[1];
      if (l <= (*it)[0] && r >= (*it)[1]) {
        --res;
      } else {
        curr = *it;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= intervals.length <= 1000|
// * |intervals[i].length == 2|
// * |0 <= lᵢ < rᵢ <= 10⁵|
// * All the given intervals are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: intervals = [[1,4],[3,6],[2,8]]
// Output: 2
//
// Interval [3,6] is covered by [2,8], therefore it is removed.

LEETCODE_SOLUTION_UNITTEST(1288, RemoveCoveredIntervals, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 4},
      {3, 6},
      {2, 8}
  };
  int expect = 2;
  int actual = solution->removeCoveredIntervals(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: intervals = [[1,4],[2,3]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1288, RemoveCoveredIntervals, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 4},
      {2, 3}
  };
  int expect = 1;
  int actual = solution->removeCoveredIntervals(intervals);
  LCD_EXPECT_EQ(expect, actual);
}
