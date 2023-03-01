// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Unsorted Continuous Subarray
//
// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
//
// Question ID: 581
// Difficult  : Medium
// Solve Date : 2022/05/03 17:59

#include <algorithm>
#include <array>
#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |581. Shortest Unsorted Continuous Subarray|:
//
// Given an integer array |nums|, you need to find one continuous subarray that
// if you only sort this subarray in ascending order, then the whole array will
// be sorted in ascending order. Return the shortest such subarray and output
// its length.  
//

LEETCODE_BEGIN_RESOLVING(581, ShortestUnsortedContinuousSubarray, Solution);

class Solution {
public:
  int findUnsortedSubarray(vector<int> &nums) {
    stack<int> stk;

    int l = nums.size(), r = 0;
    for (int i = 0; i < nums.size(); ++i) {
      while (!stk.empty() && nums[stk.top()] > nums[i]) {
        l = min(l, stk.top());
        stk.pop();
      }
      stk.emplace(i);
    }
    stack<int>{}.swap(stk);

    for (int i = nums.size() - 1; i >= 0; --i) {
      while (!stk.empty() && nums[stk.top()] < nums[i]) {
        r = max(r, stk.top());
        stk.pop();
      }
      stk.emplace(i);
    }

    return r - l > 0 ? r - l + 1 : 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁵ <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,6,4,8,10,9,15]
// Output: 5
//
// You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array
// sorted in ascending order.

LEETCODE_SOLUTION_UNITTEST(581, ShortestUnsortedContinuousSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 6, 4, 8, 10, 9, 15};
  int         expect   = 5;
  int         actual   = solution->findUnsortedSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(581, ShortestUnsortedContinuousSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 0;
  int         actual   = solution->findUnsortedSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(581, ShortestUnsortedContinuousSubarray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         expect   = 0;
  int         actual   = solution->findUnsortedSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
