// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Pairs That Form a Complete Day I
//
// https://leetcode.com/problems/count-pairs-that-form-a-complete-day-i/
//
// Question ID: 3184
// Difficult  : Easy
// Solve Date : 2024/06/17 20:51

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3184. Count Pairs That Form a Complete Day I|:
//
// Given an integer array |hours| representing times in hours, return an integer
// denoting the number of pairs |i|, |j| where |i < j| and |hours[i] + hours[j]|
// forms a complete day. A complete day is defined as a time duration that is an
// exact multiple of 24 hours. For example, 1 day is 24 hours, 2 days is 48
// hours, 3 days is 72 hours, and so on.
//
//

LEETCODE_BEGIN_RESOLVING(3184, CountPairsThatFormACompleteDayI, Solution);

class Solution {
public:
  int countCompleteDayPairs(vector<int> &hours) {
    int         res = 0;
    vector<int> mp(24);
    for (auto x : hours) {
      res += mp[(24 - x % 24) % 24];
      ++mp[x % 24];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= hours.length <= 100|
// * |1 <= hours[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: hours = [12,12,30,24,24]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3184, CountPairsThatFormACompleteDayI, example_1) {
  auto        solution = MakeSolution();
  vector<int> hours    = {12, 12, 30, 24, 24};
  int         expect   = 2;
  int         actual   = solution->countCompleteDayPairs(hours);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: hours = [72,48,24,3]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3184, CountPairsThatFormACompleteDayI, example_2) {
  auto        solution = MakeSolution();
  vector<int> hours    = {72, 48, 24, 3};
  int         expect   = 3;
  int         actual   = solution->countCompleteDayPairs(hours);
  LCD_EXPECT_EQ(expect, actual);
}
