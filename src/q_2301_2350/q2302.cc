// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Subarrays With Score Less Than K
//
// https://leetcode.com/problems/count-subarrays-with-score-less-than-k/
//
// Question ID: 2302
// Difficult  : Hard
// Solve Date : 2025/04/28 20:06

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2302. Count Subarrays With Score Less Than K|:
//
// The score of an array is defined as the product of its sum and its length.
//
//  • For example, the score of |[1, 2, 3, 4, 5]| is |(1 + 2 + 3 + 4 + 5) * 5 =
//  75|.
// Given a positive integer array |nums| and an integer |k|, return the number
// of non-empty subarrays of |nums| whose score is strictly less than |k|. A
// subarray is a contiguous sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2302, CountSubarraysWithScoreLessThanK, Solution);

class Solution {
public:
  long long countSubarrays(vector<int> &nums, long long k) {
    int64_t res = 0;
    int64_t sum = 0;
    int64_t lo  = 0;
    for (auto hi = 0; hi < nums.size(); ++hi) {
      sum += nums[hi];
      while (sum * (hi - lo + 1) >= k) {
        sum -= nums[lo++];
      }
      res += (hi - lo + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
// * |1 <= k <= 10¹⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,4,3,5], k = 10
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(2302, CountSubarraysWithScoreLessThanK, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 4, 3, 5};
  long long   k        = 10;
  long long   expect   = 6;
  long long   actual   = solution->countSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1], k = 5
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2302, CountSubarraysWithScoreLessThanK, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  long long   k        = 5;
  long long   expect   = 5;
  long long   actual   = solution->countSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
