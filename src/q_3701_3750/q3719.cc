// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Longest Balanced Subarray I
//
// https://leetcode.com/problems/longest-balanced-subarray-i/
//
// Question ID: 3719
// Difficult  : Medium
// Solve Date : 2026/02/10 19:06

#include <iosfwd>
#include <optional>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3719. Longest Balanced Subarray I|:
//
// You are given an integer array |nums|.
// A subarray is called balanced if the number of distinct even numbers in the
// subarray is equal to the number of distinct odd numbers. Return the length of
// the longest balanced subarray.
//
//

LEETCODE_BEGIN_RESOLVING(3719, LongestBalancedSubarrayI, Solution);

class Solution {
public:
  int longestBalanced(vector<int> &nums) {
    int  res = 0;
    auto beg = nums.begin();
    while (beg != nums.end()) {
      res = max(res, solve(beg++, nums.end()));
    }
    return res;
  }

private:
  int solve(auto beg, auto end) {
    int      res = 0;
    set<int> even, odd;
    auto     it = beg;
    while (it != end) {
      if (*it & 1) {
        odd.emplace(*it);
      } else {
        even.emplace(*it);
      }
      ++it;
      if (odd.size() == even.size()) {
        res = max<int>(res, distance(beg, it));
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1500|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,4,3]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3719, LongestBalancedSubarrayI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 4, 3};
  int         expect   = 4;
  int         actual   = solution->longestBalanced(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,2,5,4]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3719, LongestBalancedSubarrayI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 2, 5, 4};
  int         expect   = 5;
  int         actual   = solution->longestBalanced(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,2]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3719, LongestBalancedSubarrayI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 2};
  int         expect   = 3;
  int         actual   = solution->longestBalanced(nums);
  LCD_EXPECT_EQ(expect, actual);
}
