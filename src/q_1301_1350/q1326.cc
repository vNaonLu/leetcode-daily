// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Taps to Open to Water a Garden
//
// https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/
//
// Question ID: 1326
// Difficult  : Hard
// Solve Date : 2023/09/06 09:50

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1326. Minimum Number of Taps to Open to Water a Garden|:
//
// There is a one-dimensional garden on the x-axis. The garden starts at the
// point |0| and ends at the point |n|. (i.e., the length of the garden is |n|).
// There are |n + 1| taps located at points |[0, 1, ..., n]| in the garden.
// Given an integer |n| and an integer array |ranges| of length |n + 1| where
// |ranges[i]| (0-indexed) means the |i-th| tap can water the area |[i -
// ranges[i], i + ranges[i]]| if it was open. Return the minimum number of taps
// that should be open to water the whole garden, If the garden cannot be
// watered return -1.
//
//

LEETCODE_BEGIN_RESOLVING(1326, MinimumNumberOfTapsToOpenToWaterAGarden,
                         Solution);

class Solution {
public:
  int minTaps(int n, vector<int> &ranges) {
    vector<int> max_range(n + 1, 0);
    for (int i = 0; i < ranges.size(); ++i) {
      int l        = max(0, i - ranges[i]);
      int r        = min(n, i + ranges[i]);
      max_range[l] = max(max_range[l], r);
    }
    int end = 0;
    int far = 0;
    int res = 0;
    int i   = 0;
    while (end < n) {
      while (i <= end) {
        far = max(far, max_range[i]);
        ++i;
      }

      if (far <= end) {
        return -1;
      }

      end = far;
      ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁴|
// * |ranges.length == n + 1|
// * |0 <= ranges[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, ranges = [3,4,1,1,0,0]
// Output: 1
//
// The tap at point 0 can cover the interval [-3,3]
// The tap at point 1 can cover the interval [-3,5]
// The tap at point 2 can cover the interval [1,3]
// The tap at point 3 can cover the interval [2,4]
// The tap at point 4 can cover the interval [4,4]
// The tap at point 5 can cover the interval [5,5]
// Opening Only the second tap will water the whole garden [0,5]

LEETCODE_SOLUTION_UNITTEST(1326, MinimumNumberOfTapsToOpenToWaterAGarden,
                           example_1) {
  auto        solution = MakeSolution();
  int         n        = 5;
  vector<int> ranges   = {3, 4, 1, 1, 0, 0};
  int         expect   = 1;
  int         actual   = solution->minTaps(n, ranges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, ranges = [0,0,0,0]
// Output: -1
//
// Even if you activate all the four taps you cannot water the whole garden.

LEETCODE_SOLUTION_UNITTEST(1326, MinimumNumberOfTapsToOpenToWaterAGarden,
                           example_2) {
  auto        solution = MakeSolution();
  int         n        = 3;
  vector<int> ranges   = {0, 0, 0, 0};
  int         expect   = -1;
  int         actual   = solution->minTaps(n, ranges);
  LCD_EXPECT_EQ(expect, actual);
}
