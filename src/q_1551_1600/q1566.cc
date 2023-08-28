// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Detect Pattern of Length M Repeated K or More Times
//
// https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/
//
// Question ID: 1566
// Difficult  : Easy
// Solve Date : 2023/08/28 15:45

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1566. Detect Pattern of Length M Repeated K or More Times|:
//
// Given an array of positive integers |arr|, find a pattern of length |m| that
// is repeated |k| or more times. A pattern is a subarray (consecutive
// sub-sequence) that consists of one or more values, repeated multiple times
// consecutively without overlapping. A pattern is defined by its length and the
// number of repetitions. Return |true| if there exists a pattern of length |m|
// that is repeated |k| or more times, otherwise return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(1566, DetectPatternOfLengthMRepeatedKOrMoreTimes,
                         Solution);

class Solution {
public:
  bool containsPattern(vector<int> &arr, int m, int k) {
    int n = arr.size();
    for (int i = 0; i < n - m; ++i) {
      int j = i;
      while (j < n - m && arr[j] == arr[j + m]) {
        ++j;
      }
      if ((j - i) / m + 1 >= k) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= arr.length <= 100|
// * |1 <= arr[i] <= 100|
// * |1 <= m <= 100|
// * |2 <= k <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,4,4,4,4], m = 1, k = 3
// Output: true
//
// The pattern (4) of length 1 is repeated 4 consecutive times. Notice that
// pattern can be repeated k or more times but not less.

LEETCODE_SOLUTION_UNITTEST(1566, DetectPatternOfLengthMRepeatedKOrMoreTimes,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 4, 4, 4, 4};
  int         m        = 1;
  int         k        = 3;
  bool        expect   = true;
  bool        actual   = solution->containsPattern(arr, m, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2,1,2,1,1,1,3], m = 2, k = 2
// Output: true
//
// The pattern (1,2) of length 2 is repeated 2 consecutive times. Another valid
// pattern (2,1) is also repeated 2 times.

LEETCODE_SOLUTION_UNITTEST(1566, DetectPatternOfLengthMRepeatedKOrMoreTimes,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 1, 2, 1, 1, 1, 3};
  int         m        = 2;
  int         k        = 2;
  bool        expect   = true;
  bool        actual   = solution->containsPattern(arr, m, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [1,2,1,2,1,3], m = 2, k = 3
// Output: false
//
// The pattern (1,2) is of length 2 but is repeated only 2 times. There is no
// pattern of length 2 that is repeated 3 or more times.

LEETCODE_SOLUTION_UNITTEST(1566, DetectPatternOfLengthMRepeatedKOrMoreTimes,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 1, 2, 1, 3};
  int         m        = 2;
  int         k        = 3;
  bool        expect   = false;
  bool        actual   = solution->containsPattern(arr, m, k);
  LCD_EXPECT_EQ(expect, actual);
}
