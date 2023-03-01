// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Subarray Sum Equals K
//
// https://leetcode.com/problems/subarray-sum-equals-k/
//
// Question ID: 560
// Difficult  : Medium
// Solve Date : 2021/09/23 08:00

#include <array>
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |560. Subarray Sum Equals K|:
//
// Given an array of integers |nums| and an integer |k|, return the total number
// of subarrays whose sum equals to |k|. A subarray is a contiguous non-empty
// sequence of elements within an array.  
//

LEETCODE_BEGIN_RESOLVING(560, SubarraySumEqualsK, Solution);

class Solution {
public:
  int subarraySum(vector<int> &nums, int k) {
    int                     res = 0, sum = 0;
    unordered_map<int, int> hash;
    hash[sum] = 1;
    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];
      if (hash.count(sum - k))
        res += hash.at(sum - k);
      ++hash[sum];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁴|
// * |-1000 <= nums[i] <= 1000|
// * |-10⁷ <= k <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,1], k = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(560, SubarraySumEqualsK, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  int         k        = 2;
  int         expect   = 2;
  int         actual   = solution->subarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3], k = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(560, SubarraySumEqualsK, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         k        = 3;
  int         expect   = 2;
  int         actual   = solution->subarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
