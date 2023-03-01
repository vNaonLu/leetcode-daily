// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Duplicate Zeros
//
// https://leetcode.com/problems/duplicate-zeros/
//
// Question ID: 1089
// Difficult  : Easy
// Solve Date : 2022/08/05 18:28

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1089. Duplicate Zeros|:
//
// Given a fixed-length integer array |arr|, duplicate each occurrence of zero,
// shifting the remaining elements to the right. Note that elements beyond the
// length of the original array are not written. Do the above modifications to
// the input array in place and do not return anything.
//

LEETCODE_BEGIN_RESOLVING(1089, DuplicateZeros, Solution);

class Solution {
public:
  void duplicateZeros(vector<int> &arr) {
    auto res    = vector<int>(arr.size(), 0);
    auto it     = res.begin();
    auto arr_it = arr.begin();

    while (it != res.end()) {
      *it++ = *arr_it;
      if (*arr_it++ == 0 && it != res.end()) {
        *it++ = 0;
      }
    }

    arr.swap(res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁴|
// * |0 <= arr[i] <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,0,2,3,0,4,5,0]
// Output: [1,0,0,2,3,0,0,4]
//
// After calling your function, the input array is modified to:
// [1,0,0,2,3,0,0,4]

LEETCODE_SOLUTION_UNITTEST(1089, DuplicateZeros, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 0, 2, 3, 0, 4, 5, 0};
  vector<int> expect   = {1, 0, 0, 2, 3, 0, 0, 4};
  solution->duplicateZeros(arr);
  LCD_EXPECT_EQ(expect, arr);
}

// [Example #2]
//  Input: arr = [1,2,3]
// Output: [1,2,3]
//
// After calling your function, the input array is modified to: [1,2,3]

LEETCODE_SOLUTION_UNITTEST(1089, DuplicateZeros, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3};
  vector<int> expect   = {1, 2, 3};
  solution->duplicateZeros(arr);
  LCD_EXPECT_EQ(expect, arr);
}
