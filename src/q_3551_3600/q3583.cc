// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Special Triplets
//
// https://leetcode.com/problems/count-special-triplets/
//
// Question ID: 3583
// Difficult  : Medium
// Solve Date : 2025/12/09 22:13

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3583. Count Special Triplets|:
//
// You are given an integer array |nums|.
// A special triplet is defined as a triplet of indices |(i, j, k)| such that:
//
//  • |0 <= i < j < k < n|, where |n = nums.length|
//
//  • |nums[i] == nums[j] * 2|
//
//  • |nums[k] == nums[j] * 2|
// Return the total number of special triplets in the array.
// Since the answer may be large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(3583, CountSpecialTriplets, Solution);

class Solution {
public:
  int specialTriplets(vector<int> &nums) {
    const int               mod = 1e9 + 7;
    unordered_map<int, int> suffix;
    unordered_map<int, int> prefix;
    for (auto x : nums)
      suffix[x] += 1;
    long long ans = 0;
    for (auto x : nums) {
      suffix[x] -= 1;
      ans += (int64_t)prefix[2 * x] * suffix[2 * x];
      prefix[x] += 1;
    }
    return ans % mod;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= n == nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [6,3,6]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3583, CountSpecialTriplets, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 3, 6};
  int         expect   = 1;
  int         actual   = solution->specialTriplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,0,0]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3583, CountSpecialTriplets, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 0, 0};
  int         expect   = 1;
  int         actual   = solution->specialTriplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [8,4,2,8,4]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3583, CountSpecialTriplets, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8, 4, 2, 8, 4};
  int         expect   = 2;
  int         actual   = solution->specialTriplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}
