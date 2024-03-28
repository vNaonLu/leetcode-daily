// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Length of Longest Subarray With at Most K Frequency
//
// https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/
//
// Question ID: 2958
// Difficult  : Medium
// Solve Date : 2024/03/28 19:06

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2958. Length of Longest Subarray With at Most K Frequency|:
//
// You are given an integer array |nums| and an integer |k|.
// The frequency of an element |x| is the number of times it occurs in an array.
// An array is called good if the frequency of each element in this array is
// less than or equal to |k|. Return the length of the longest good subarray of
// |nums|. A subarray is a contiguous non-empty sequence of elements within an
// array.
//
//

LEETCODE_BEGIN_RESOLVING(2958, LengthOfLongestSubarrayWithAtMostKFrequency,
                         Solution);

class Solution {
public:
  int maxSubarrayLength(vector<int> &nums, int k) {
    int                     n   = nums.size();
    int                     res = 0;
    unordered_map<int, int> freq;
    for (int l = 0, r = 0; r < n; ++r) {
      int x = nums[r];
      if (!freq.count(x)) {
        freq[x] = 1;
      } else {
        ++freq[x];
      }

      while (freq[x] > k) {
        --freq[nums[l++]];
      }
      res = max(res, r - l + 1);
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
// * |1 <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,1,2,3,1,2], k = 2
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(2958, LengthOfLongestSubarrayWithAtMostKFrequency,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 1, 2, 3, 1, 2};
  int         k        = 2;
  int         expect   = 6;
  int         actual   = solution->maxSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,1,2,1,2,1,2], k = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2958, LengthOfLongestSubarrayWithAtMostKFrequency,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 2, 1, 2, 1, 2};
  int         k        = 1;
  int         expect   = 2;
  int         actual   = solution->maxSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [5,5,5,5,5,5,5], k = 4
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2958, LengthOfLongestSubarrayWithAtMostKFrequency,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 5, 5, 5, 5, 5, 5};
  int         k        = 4;
  int         expect   = 4;
  int         actual   = solution->maxSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
