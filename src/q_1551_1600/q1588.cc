// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of All Odd Length Subarrays
//
// https://leetcode.com/problems/sum-of-all-odd-length-subarrays/
//
// Question ID: 1588
// Difficult  : Easy
// Solve Date : 2022/04/19 11:57

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1588. Sum of All Odd Length Subarrays|:
//
// Given an array of positive integers |arr|, return the sum of all possible
// odd-length subarrays of |arr|. A subarray is a contiguous subsequence of the
// array.  
//

LEETCODE_BEGIN_RESOLVING(1588, SumOfAllOddLengthSubarrays, Solution);

class Solution {
public:
  int sumOddLengthSubarrays(vector<int> &arr) {
    int length = 1, res = 0;

    vector<int> summary(arr.size() + 1, 0);
    for (int i = 0; i < arr.size(); ++i) {
      summary[i + 1] = summary[i] + arr[i];
    }

    while (length <= arr.size()) {
      for (int i = 0; i + length < summary.size(); ++i) {
        res += summary[i + length] - summary[i];
      }
      ++ ++length;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 100|
// * |1 <= arr[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,4,2,5,3]
// Output: 58
//
// The odd-length subarrays of arr and their sums are:
// [1] = 1
// [4] = 4
// [2] = 2
// [5] = 5
// [3] = 3
// [1,4,2] = 7
// [4,2,5] = 11
// [2,5,3] = 10
// [1,4,2,5,3] = 15
// If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58

LEETCODE_SOLUTION_UNITTEST(1588, SumOfAllOddLengthSubarrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 4, 2, 5, 3};
  int         expect   = 58;
  int         actual   = solution->sumOddLengthSubarrays(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2]
// Output: 3
// Explanation: There are only 2 subarrays of odd length, [1] and [2]. Their sum
// is 3.
//

LEETCODE_SOLUTION_UNITTEST(1588, SumOfAllOddLengthSubarrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2};
  int         expect   = 3;
  int         actual   = solution->sumOddLengthSubarrays(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [10,11,12]
// Output: 66
//

LEETCODE_SOLUTION_UNITTEST(1588, SumOfAllOddLengthSubarrays, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {10, 11, 12};
  int         expect   = 66;
  int         actual   = solution->sumOddLengthSubarrays(arr);
  LCD_EXPECT_EQ(expect, actual);
}
