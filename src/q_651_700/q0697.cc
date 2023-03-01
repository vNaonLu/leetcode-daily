// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Degree of an Array
//
// https://leetcode.com/problems/degree-of-an-array/
//
// Question ID: 697
// Difficult  : Easy
// Solve Date : 2022/11/02 22:03

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |697. Degree of an Array|:
//
// Given a non-empty array of non-negative integers |nums|, the degree of this
// array is defined as the maximum frequency of any one of its elements. Your
// task is to find the smallest possible length of a (contiguous) subarray of
// |nums|, that has the same degree as |nums|.
//

LEETCODE_BEGIN_RESOLVING(697, DegreeOfAnArray, Solution);

class Solution {
public:
  int findShortestSubArray(vector<int> &nums) {
    auto left  = unordered_map<int, int>();
    auto right = unordered_map<int, int>();
    auto count = unordered_map<int, int>();
    for (int i = 0; i < nums.size(); ++i) {
      auto x = nums[i];
      if (!left.count(x)) {
        left[x] = i;
      }
      right[x] = i;
      ++count[x];
    }

    auto res    = (int)nums.size();
    auto degree = max_element(count.begin(), count.end(), [](auto &x, auto &y) {
                    return x.second < y.second;
                  })->second;
    for (auto [x, c] : count) {
      if (c == degree) {
        res = min(res, right[x] - left[x] + 1);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |nums.length| will be between 1 and 50,000.
// * |nums[i]| will be an integer between 0 and 49,999.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2,3,1]
// Output: 2
//
// The input array has a degree of 2 because both elements 1 and 2 appear twice.
// Of the subarrays that have the same degree:
// [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
// The shortest length is 2. So return 2.

LEETCODE_SOLUTION_UNITTEST(697, DegreeOfAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 3, 1};
  int         expect   = 2;
  int         actual   = solution->findShortestSubArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,2,3,1,4,2]
// Output: 6
//
// The degree is 3 because the element 2 is repeated 3 times.
// So [2,2,3,1,4,2] is the shortest subarray, therefore returning 6.

LEETCODE_SOLUTION_UNITTEST(697, DegreeOfAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 3, 1, 4, 2};
  int         expect   = 6;
  int         actual   = solution->findShortestSubArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
