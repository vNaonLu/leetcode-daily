// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Can Make Arithmetic Progression From Sequence
//
// https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/
//
// Question ID: 1502
// Difficult  : Easy
// Solve Date : 2022/04/17 12:42

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1502. Can Make Arithmetic Progression From Sequence|:
//
// A sequence of numbers is called an arithmetic progression if the difference
// between any two consecutive elements is the same. Given an array of numbers
// |arr|, return |true| if the array can be rearranged to form an arithmetic
// progression. Otherwise, return |false|.  
//

LEETCODE_BEGIN_RESOLVING(1502, CanMakeArithmeticProgressionFromSequence,
                         Solution);

class Solution {
public:
  bool canMakeArithmeticProgression(vector<int> &arr) {
    sort(arr.begin(), arr.end());
    int diff = arr[1] - arr[0];
    for (int i = 2; i < arr.size(); ++i) {
      if (diff != arr[i] - arr[i - 1]) {
        return false;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= arr.length <= 1000|
// * |-10⁶ <= arr[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [3,5,1]
// Output: true
//
// We can reorder the elements as [1,3,5] or [5,3,1] with differences 2 and -2
// respectively, between each consecutive elements.

LEETCODE_SOLUTION_UNITTEST(1502, CanMakeArithmeticProgressionFromSequence,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 5, 1};
  bool        expect   = true;
  bool        actual   = solution->canMakeArithmeticProgression(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2,4]
// Output: false
//
// There is no way to reorder the elements to obtain an arithmetic progression.

LEETCODE_SOLUTION_UNITTEST(1502, CanMakeArithmeticProgressionFromSequence,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 4};
  bool        expect   = false;
  bool        actual   = solution->canMakeArithmeticProgression(arr);
  LCD_EXPECT_EQ(expect, actual);
}
