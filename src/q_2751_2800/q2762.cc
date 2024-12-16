// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Continuous Subarrays
//
// https://leetcode.com/problems/continuous-subarrays/
//
// Question ID: 2762
// Difficult  : Medium
// Solve Date : 2024/12/14 21:48

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2762. Continuous Subarrays|:
//
// You are given a 0-indexed integer array |nums|. A subarray of |nums| is
// called continuous if:
//
//  • Let |i|, |i + 1|, ..., |j|_{ }be the indices in the subarray. Then, for
//  each pair of indices |i <= i₁, i₂ <= j|, |0 <= |nums[i₁] - nums[i₂]| <= 2|.
// Return the total number of continuous subarrays.
// A subarray is a contiguous non-empty sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2762, ContinuousSubarrays, Solution);

class Solution {
public:
  long long continuousSubarrays(vector<int> &nums) {
    map<int, int> freq;
    int           left  = 0;
    int           right = 0;
    int           n     = nums.size();
    int64_t       res   = 0;
    while (right < n) {
      ++freq[nums[right]];
      while (freq.rbegin()->first - freq.begin()->first > 2) {
        --freq[nums[left]];
        if (freq[nums[left]] == 0) {
          freq.erase(nums[left]);
        }
        ++left;
      }
      res += right - left + 1;
      ++right;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,4,2,4]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(2762, ContinuousSubarrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 4, 2, 4};
  long long   expect   = 8;
  long long   actual   = solution->continuousSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(2762, ContinuousSubarrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  long long   expect   = 6;
  long long   actual   = solution->continuousSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}
