// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Elements With Maximum Frequency
//
// https://leetcode.com/problems/count-elements-with-maximum-frequency/
//
// Question ID: 3005
// Difficult  : Easy
// Solve Date : 2024/02/21 20:07

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3005. Count Elements With Maximum Frequency|:
//
// You are given an array |nums| consisting of positive integers.
// Return the total frequencies of elements in |nums| such that those elements
// all have the maximum frequency. The frequency of an element is the number of
// occurrences of that element in the array.
//
//

LEETCODE_BEGIN_RESOLVING(3005, CountElementsWithMaximumFrequency, Solution);

class Solution {
public:
  int maxFrequencyElements(vector<int> &nums) {
    int         mx_freq = 0;
    vector<int> ocur(101, 0);
    vector<int> freq(101, 0);
    for (auto x : nums) {
      mx_freq = max(mx_freq, ++ocur[x]);
      ++freq[ocur[x]];
    }
    return freq[mx_freq] * mx_freq;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2,3,1,4]
// Output: 4
//
// The elements 1 and 2 have a frequency of 2 which is the maximum frequency in
// the array. So the number of elements in the array with maximum frequency
// is 4.

LEETCODE_SOLUTION_UNITTEST(3005, CountElementsWithMaximumFrequency, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 3, 1, 4};
  int         expect   = 4;
  int         actual   = solution->maxFrequencyElements(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5]
// Output: 5
//
// All elements of the array have a frequency of 1 which is the maximum.
// So the number of elements in the array with maximum frequency is 5.

LEETCODE_SOLUTION_UNITTEST(3005, CountElementsWithMaximumFrequency, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         expect   = 5;
  int         actual   = solution->maxFrequencyElements(nums);
  LCD_EXPECT_EQ(expect, actual);
}
