// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count the Number of Good Subarrays
//
// https://leetcode.com/problems/count-the-number-of-good-subarrays/
//
// Question ID: 2537
// Difficult  : Medium
// Solve Date : 2025/04/16 20:49

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2537. Count the Number of Good Subarrays|:
//
// Given an integer array |nums| and an integer |k|, return the number of good
// subarrays of |nums|. A subarray |arr| is good if there are at least |k| pairs
// of indices |(i, j)| such that |i < j| and |arr[i] == arr[j]|. A subarray is a
// contiguous non-empty sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2537, CountTheNumberOfGoodSubarrays, Solution);

class Solution {
public:
  long long countGood(vector<int> &nums, int k) {
    unordered_map<int, int> freq;
    int64_t                 res = 0;
    int64_t                 cur = 0;
    auto                    lo  = nums.begin();
    auto                    hi  = nums.begin();
    while (hi != nums.end()) {
      cur += freq[*hi]++;
      while (cur >= k) {
        res += distance(hi, nums.end());
        cur -= --freq[*lo++];
      }
      ++hi;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i], k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,1,1,1], k = 10
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2537, CountTheNumberOfGoodSubarrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1, 1};
  int         k        = 10;
  long long   expect   = 1;
  long long   actual   = solution->countGood(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,1,4,3,2,2,4], k = 2
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2537, CountTheNumberOfGoodSubarrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 4, 3, 2, 2, 4};
  int         k        = 2;
  long long   expect   = 4;
  long long   actual   = solution->countGood(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
