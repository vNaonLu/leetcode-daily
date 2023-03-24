// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Array by Increasing Frequency
//
// https://leetcode.com/problems/sort-array-by-increasing-frequency/
//
// Question ID: 1636
// Difficult  : Easy
// Solve Date : 2023/03/24 11:38

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1636. Sort Array by Increasing Frequency|:
//
// Given an array of integers |nums|, sort the array in increasing order based
// on the frequency of the values. If multiple values have the same frequency,
// sort them in decreasing order. Return the sorted array.
//
//

LEETCODE_BEGIN_RESOLVING(1636, SortArrayByIncreasingFrequency, Solution);

class Solution {
public:
  vector<int> frequencySort(vector<int> &nums) {
    unordered_map<int, int> freq;
    for (auto x : nums) {
      ++freq[x];
    }
    sort(nums.begin(), nums.end(), [&](int x, int y) {
      return freq[x] == freq[y] ? x > y : freq[x] < freq[y];
    });
    return nums;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,2,2,2,3]
// Output: [3,1,1,2,2,2]
//
// '3' has a frequency of 1, '1' has a frequency of 2, and '2' has a frequency
// of 3.

LEETCODE_SOLUTION_UNITTEST(1636, SortArrayByIncreasingFrequency, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 2, 2, 3};
  vector<int> expect   = {3, 1, 1, 2, 2, 2};
  vector<int> actual   = solution->frequencySort(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,1,3,2]
// Output: [1,3,3,2,2]
//
// '2' and '3' both have a frequency of 2, so they are sorted in decreasing
// order.

LEETCODE_SOLUTION_UNITTEST(1636, SortArrayByIncreasingFrequency, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 1, 3, 2};
  vector<int> expect   = {1, 3, 3, 2, 2};
  vector<int> actual   = solution->frequencySort(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-1,1,-6,4,5,-6,1,4,1]
// Output: [5,-1,4,4,-6,-6,1,1,1]
//

LEETCODE_SOLUTION_UNITTEST(1636, SortArrayByIncreasingFrequency, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 1, -6, 4, 5, -6, 1, 4, 1};
  vector<int> expect   = {5, -1, 4, 4, -6, -6, 1, 1, 1};
  vector<int> actual   = solution->frequencySort(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [-4,31,-12,29,40,-7,3,-12,-12,20,23,-4,-12,-41,-9,-41,-7,31,-9,22]
// Output: [40,29,23,22,20,3,31,31,-4,-4,-7,-7,-9,-9,-41,-41,-12,-12,-12,-12]
//

LEETCODE_SOLUTION_UNITTEST(1636, SortArrayByIncreasingFrequency,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-4, 31, -12, 29,  40, -7,  3,  -12, -12, 20,
                          23, -4, -12, -41, -9, -41, -7, 31,  -9,  22};
  vector<int> expect   = {40, 29, 23, 22, 20,  3,   31,  31,  -4,  -4,
                          -7, -7, -9, -9, -41, -41, -12, -12, -12, -12};
  vector<int> actual   = solution->frequencySort(nums);
  LCD_EXPECT_EQ(expect, actual);
}
