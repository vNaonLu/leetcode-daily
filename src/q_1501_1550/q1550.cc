// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Three Consecutive Odds
//
// https://leetcode.com/problems/three-consecutive-odds/
//
// Question ID: 1550
// Difficult  : Easy
// Solve Date : 2023/04/01 13:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1550. Three Consecutive Odds|:
//
// Given an integer array |arr|, return |true| if there are three consecutive
// odd numbers in the array. Otherwise, return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(1550, ThreeConsecutiveOdds, Solution);

class Solution {
public:
  bool threeConsecutiveOdds(vector<int> &arr) {
    auto beg = arr.begin();
    while (beg != arr.end()) {
      if (*beg & 1) {
        auto it = beg + 1;
        while (it != arr.end()) {
          if ((*it & 1) == 0 || distance(beg, it) >= 3) {
            break;
          }
          ++it;
        }
        if (distance(beg, it) >= 3) {
          return true;
        }
        beg = it;
      } else {
        ++beg;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 1000|
// * |1 <= arr[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,6,4,1]
// Output: false
//
// There are no three consecutive odds.

LEETCODE_SOLUTION_UNITTEST(1550, ThreeConsecutiveOdds, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 6, 4, 1};
  bool        expect   = false;
  bool        actual   = solution->threeConsecutiveOdds(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2,34,3,4,5,7,23,12]
// Output: true
//
// [5,7,23] are three consecutive odds.

LEETCODE_SOLUTION_UNITTEST(1550, ThreeConsecutiveOdds, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 34, 3, 4, 5, 7, 23, 12};
  bool        expect   = true;
  bool        actual   = solution->threeConsecutiveOdds(arr);
  LCD_EXPECT_EQ(expect, actual);
}
