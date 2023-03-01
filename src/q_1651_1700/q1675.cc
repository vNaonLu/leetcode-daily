// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimize Deviation in Array
//
// https://leetcode.com/problems/minimize-deviation-in-array/
//
// Question ID: 1675
// Difficult  : Hard
// Solve Date : 2022/02/19 14:39

#include <iosfwd>
#include <limits>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1675. Minimize Deviation in Array|:
//
// You are given an array |nums| of |n| positive integers.
// You can perform two types of operations on any element of the array any
// number of times:
//
//  • If the element is even, divide it by |2|.
//
//
//    • For example, if the array is |[1,2,3,4]|, then you can do this operation
//    on the last element, and the array will be |[1,2,3,2].|
//
//
//
//  • If the element is odd, multiply it by |2|.
//
//
//    • For example, if the array is |[1,2,3,4]|, then you can do this operation
//    on the first element, and the array will be |[2,2,3,4].|
//
//
// The deviation of the array is the maximum difference between any two elements
// in the array. Return the minimum deviation the array can have after
// performing some number of operations.  
//

LEETCODE_BEGIN_RESOLVING(1675, MinimizeDeviationInArray, Solution);

class Solution {
public:
  int minimumDeviation(vector<int> &nums) {
    int mx = numeric_limits<int>::min(), mn = numeric_limits<int>::max();
    for (auto &x : nums) {
      if (x % 2 != 0) {
        x *= 2;
      }
      mx = max(mx, x);
      mn = min(mn, x);
    }
    int                 res = mx - mn;
    priority_queue<int> pq;
    for (const auto &x : nums)
      pq.push(x);
    while (pq.top() % 2 == 0) {
      auto t = pq.top();
      pq.pop();
      res = min(res, t - mn);
      t /= 2;
      mn = min(mn, t);
      pq.push(t);
    }
    res = min(res, pq.top() - mn);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |2 <= n <= 5 * 104|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: 1
//
// You can transform the array to [1,2,3,2], then to [2,2,3,2], then the
// deviation will be 3 - 2 = 1.

LEETCODE_SOLUTION_UNITTEST(1675, MinimizeDeviationInArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 1;
  int         actual   = solution->minimumDeviation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,1,5,20,3]
// Output: 3
//
// You can transform the array after two operations to [4,2,5,5,3], then the
// deviation will be 5 - 2 = 3.

LEETCODE_SOLUTION_UNITTEST(1675, MinimizeDeviationInArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 1, 5, 20, 3};
  int         expect   = 3;
  int         actual   = solution->minimumDeviation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,10,8]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1675, MinimizeDeviationInArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 10, 8};
  int         expect   = 3;
  int         actual   = solution->minimumDeviation(nums);
  LCD_EXPECT_EQ(expect, actual);
}
