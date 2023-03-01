// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Kth Missing Positive Number
//
// https://leetcode.com/problems/kth-missing-positive-number/
//
// Question ID: 1539
// Difficult  : Easy
// Solve Date : 2022/04/08 18:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1539. Kth Missing Positive Number|:
//
// Given an array |arr| of positive integers sorted in a strictly increasing
// order, and an integer |k|. Return the |kᵗʰ| positive integer that is missing
// from this array.  
//

LEETCODE_BEGIN_RESOLVING(1539, KthMissingPositiveNumber, Solution);

class Solution {
public:
  int findKthPositive(vector<int> &arr, int k) {
    int l = 0, r = arr.size();
    while (l < r) {
      int m    = l + (r - l) / 2;
      int miss = arr[m] - m - 1;
      if (miss < k) {
        l = m + 1;
      } else {
        r = m;
      }
    }

    return l + k;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 1000|
// * |1 <= arr[i] <= 1000|
// * |1 <= k <= 1000|
// * |arr[i] < arr[j]| for |1 <= i < j <= arr.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,3,4,7,11], k = 5
// Output: 9
//
// The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5ᵗʰ missing
// positive integer is 9.

LEETCODE_SOLUTION_UNITTEST(1539, KthMissingPositiveNumber, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 3, 4, 7, 11};
  int         k        = 5;
  int         expect   = 9;
  int         actual   = solution->findKthPositive(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2,3,4], k = 2
// Output: 6
//
// The missing positive integers are [5,6,7,...]. The 2ⁿᵈ missing positive
// integer is 6.

LEETCODE_SOLUTION_UNITTEST(1539, KthMissingPositiveNumber, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4};
  int         k        = 2;
  int         expect   = 6;
  int         actual   = solution->findKthPositive(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}
