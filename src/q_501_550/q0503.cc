// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Next Greater Element II
//
// https://leetcode.com/problems/next-greater-element-ii/
//
// Question ID: 503
// Difficult  : Medium
// Solve Date : 2022/05/05 18:41

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |503. Next Greater Element II|:
//
// Given a circular integer array |nums| (i.e., the next element of
// |nums[nums.length - 1]| is |nums[0]|), return the next greater number for
// every element in |nums|. The next greater number of a number |x| is the first
// greater number to its traversing-order next in the array, which means you
// could search circularly to find its next greater number. If it doesn't exist,
// return |-1| for this number.  
//

LEETCODE_BEGIN_RESOLVING(503, NextGreaterElementII, Solution);

class Solution {
public:
  vector<int> nextGreaterElements(vector<int> &nums) {
    int         n = nums.size();
    stack<int>  stk;
    vector<int> res(n);

    for (int i = 2 * n - 1; i >= 0; --i) {
      while (!stk.empty() && stk.top() <= nums[i % n]) {
        stk.pop();
      }

      if (stk.empty()) {
        res[i % n] = -1;
      } else {
        res[i % n] = stk.top();
      }
      stk.emplace(nums[i % n]);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1]
// Output: [2,-1,2]
// Explanation: The first 1's next greater number is 2;
// The number 2 can't find next greater number.
// The second 1's next greater number needs to search circularly, which is
// also 2.
//

LEETCODE_SOLUTION_UNITTEST(503, NextGreaterElementII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1};
  vector<int> expect   = {2, -1, 2};
  vector<int> actual   = solution->nextGreaterElements(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,3]
// Output: [2,3,4,-1,4]
//

LEETCODE_SOLUTION_UNITTEST(503, NextGreaterElementII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 3};
  vector<int> expect   = {2, 3, 4, -1, 4};
  vector<int> actual   = solution->nextGreaterElements(nums);
  LCD_EXPECT_EQ(expect, actual);
}
