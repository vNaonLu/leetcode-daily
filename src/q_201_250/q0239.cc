// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sliding Window Maximum
//
// https://leetcode.com/problems/sliding-window-maximum/
//
// Question ID: 239
// Difficult  : Hard
// Solve Date : 2023/08/16 11:52

#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |239. Sliding Window Maximum|:
//
// You are given an array of integers |nums|, there is a sliding window of size
// |k| which is moving from the very left of the array to the very right. You
// can only see the |k| numbers in the window. Each time the sliding window
// moves right by one position. Return the max sliding window.
//
//

LEETCODE_BEGIN_RESOLVING(239, SlidingWindowMaximum, Solution);

class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    deque<int>  dq;
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
      if (!dq.empty() && dq.front() == i - k) {
        dq.pop_front();
      }
      while (!dq.empty() && nums[dq.back()] < nums[i]) {
        dq.pop_back();
      }

      dq.push_back(i);
      if (i >= k - 1) {
        res.emplace_back(nums[dq.front()]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |1 <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [3,3,5,5,6,7]
//
// Window position Max
// --------------- -----
// [1 3 -1] -3 5 3 6 7 3
//  1 [3 -1 -3] 5 3 6 7 3
//  1 3 [-1 -3 5] 3 6 7  5
//  1 3 -1 [-3 5 3] 6 7 5
//  1 3 -1 -3 [5 3 6] 7 6
//  1 3 -1 -3 5 [3 6 7] 7

LEETCODE_SOLUTION_UNITTEST(239, SlidingWindowMaximum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, -1, -3, 5, 3, 6, 7};
  int         k        = 3;
  vector<int> expect   = {3, 3, 5, 5, 6, 7};
  vector<int> actual   = solution->maxSlidingWindow(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1], k = 1
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(239, SlidingWindowMaximum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         k        = 1;
  vector<int> expect   = {1};
  vector<int> actual   = solution->maxSlidingWindow(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
