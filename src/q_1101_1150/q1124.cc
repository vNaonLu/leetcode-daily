// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Well-Performing Interval
//
// https://leetcode.com/problems/longest-well-performing-interval/
//
// Question ID: 1124
// Difficult  : Medium
// Solve Date : 2022/02/24 18:41

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1124. Longest Well-Performing Interval|:
//
// We are given |hours|, a list of the number of hours worked per day for a
// given employee. A day is considered to be a tiring day if and only if the
// number of hours worked is (strictly) greater than |8|. A well-performing
// interval is an interval of days for which the number of tiring days is
// strictly larger than the number of non-tiring days. Return the length of the
// longest well-performing interval.  
//

LEETCODE_BEGIN_RESOLVING(1124, LongestWellPerformingInterval, Solution);

class Solution {
public:
  int longestWPI(vector<int> &hours) {
    unordered_map<int, int> mp;
    int                     res = 0, perf = 0;
    for (int i = 0; i < hours.size(); ++i) {
      perf += hours[i] > 8 ? 1 : -1;
      if (perf > 0)
        res = max(res, i + 1);
      else if (mp.find(perf) == mp.end())
        mp[perf] = i;

      if (mp.find(perf - 1) != mp.end())
        res = max(res, i - mp[perf - 1]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= hours.length <= 10⁴|
// * |0 <= hours[i] <= 16|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: hours = [9,9,6,0,6,6,9]
// Output: 3
//
// The longest well-performing interval is [9,9,6].

LEETCODE_SOLUTION_UNITTEST(1124, LongestWellPerformingInterval, example_1) {
  auto        solution = MakeSolution();
  vector<int> hours    = {9, 9, 6, 0, 6, 6, 9};
  int         expect   = 3;
  int         actual   = solution->longestWPI(hours);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: hours = [6,6,6]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1124, LongestWellPerformingInterval, example_2) {
  auto        solution = MakeSolution();
  vector<int> hours    = {6, 6, 6};
  int         expect   = 0;
  int         actual   = solution->longestWPI(hours);
  LCD_EXPECT_EQ(expect, actual);
}
