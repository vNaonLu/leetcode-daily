// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Largest Time for Given Digits
//
// https://leetcode.com/problems/largest-time-for-given-digits/
//
// Question ID: 949
// Difficult  : Medium
// Solve Date : 2024/09/28 13:40

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |949. Largest Time for Given Digits|:
//
// Given an array |arr| of 4 digits, find the latest 24-hour time that can be
// made using each digit exactly once. 24-hour times are formatted as |"HH:MM"|,
// where |HH| is between |00| and |23|, and |MM| is between |00| and |59|. The
// earliest 24-hour time is |00:00|, and the latest is |23:59|. Return the
// latest 24-hour time in |"HH:MM"| format. If no valid time can be made, return
// an empty string.
//
//

LEETCODE_BEGIN_RESOLVING(949, LargestTimeForGivenDigits, Solution);

class Solution {
public:
  string largestTimeFromDigits(vector<int> &arr) {
    sort(arr.begin(), arr.end(), greater<int>{});
    do {
      if ((arr[0] < 2 || (arr[0] == 2 && arr[1] < 4)) && arr[2] < 6) {
        return to_string(arr[0]) + to_string(arr[1]) + ":" + to_string(arr[2]) +
               to_string(arr[3]);
      }
    } while (prev_permutation(arr.begin(), arr.end()));
    return "";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |arr.length == 4|
// * |0 <= arr[i] <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,3,4]
// Output: "23:41"
//

LEETCODE_SOLUTION_UNITTEST(949, LargestTimeForGivenDigits, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4};
  string      expect   = "23:41";
  string      actual   = solution->largestTimeFromDigits(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [5,5,5,5]
// Output: ""
//

LEETCODE_SOLUTION_UNITTEST(949, LargestTimeForGivenDigits, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {5, 5, 5, 5};
  string      expect   = "";
  string      actual   = solution->largestTimeFromDigits(arr);
  LCD_EXPECT_EQ(expect, actual);
}
