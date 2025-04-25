// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count of Interesting Subarrays
//
// https://leetcode.com/problems/count-of-interesting-subarrays/
//
// Question ID: 2845
// Difficult  : Medium
// Solve Date : 2025/04/25 19:12

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2845. Count of Interesting Subarrays|:
//
// You are given a 0-indexed integer array |nums|, an integer |modulo|, and an
// integer |k|. Your task is to find the count of subarrays that are
// interesting. A subarray |nums[l..r]| is interesting if the following
// condition holds:
//
//  • Let |cnt| be the number of indices |i| in the range |[l, r]| such that
//  |nums[i] % modulo == k|. Then, |cnt % modulo == k|.
// Return an integer denoting the count of interesting subarrays.
// Note: A subarray is a contiguous non-empty sequence of elements within an
// array.
//
//

LEETCODE_BEGIN_RESOLVING(2845, CountOfInterestingSubarrays, Solution);

class Solution {
public:
  long long countInterestingSubarrays(vector<int> &nums, int modulo, int k) {
    int64_t                     res = 0;
    int64_t                     eq  = 0;
    unordered_map<int, int64_t> mp{
        {0, 1}
    };

    for (auto x : nums) {
      if (x % modulo == k) {
        ++eq;
      }

      int rem    = eq % modulo;
      int needed = (rem - k + modulo) % modulo;
      res += mp[needed];
      ++mp[rem];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10^{5 }|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= modulo <= 10⁹|
// * |0 <= k < modulo|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,4], modulo = 2, k = 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2845, CountOfInterestingSubarrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 4};
  int         modulo   = 2;
  int         k        = 1;
  long long   expect   = 3;
  long long   actual   = solution->countInterestingSubarrays(nums, modulo, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,1,9,6], modulo = 3, k = 0
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2845, CountOfInterestingSubarrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 9, 6};
  int         modulo   = 3;
  int         k        = 0;
  long long   expect   = 2;
  long long   actual   = solution->countInterestingSubarrays(nums, modulo, k);
  LCD_EXPECT_EQ(expect, actual);
}
