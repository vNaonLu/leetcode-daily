// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Binary Subarrays With Sum
//
// https://leetcode.com/problems/binary-subarrays-with-sum/
//
// Question ID: 930
// Difficult  : Medium
// Solve Date : 2024/03/14 21:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |930. Binary Subarrays With Sum|:
//
// Given a binary array |nums| and an integer |goal|, return the number of
// non-empty subarrays with a sum |goal|.
//
// A subarray is a contiguous part of the array.
//
//
//

LEETCODE_BEGIN_RESOLVING(930, BinarySubarraysWithSum, Solution);

class Solution {
public:
  int numSubarraysWithSum(vector<int> &nums, int goal) {
    int         n = nums.size();
    vector<int> freq(goal + n + 1, 0);
    int         sum = 0;
    int         res = 0;
    for (auto x : nums) {
      sum += x;
      if (sum == goal) {
        ++res;
      }

      if (freq[sum] != 0) {
        res += freq[sum];
      }

      ++freq[sum + goal];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 3 * 10⁴|
// * |nums[i]| is either |0| or |1|.
// * |0 <= goal <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,0,1,0,1], goal = 2
// Output: 4
//
// The 4 subarrays are bolded and underlined below:
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]

LEETCODE_SOLUTION_UNITTEST(930, BinarySubarraysWithSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 0, 1, 0, 1};
  int         goal     = 2;
  int         expect   = 4;
  int         actual   = solution->numSubarraysWithSum(nums, goal);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,0,0,0,0], goal = 0
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(930, BinarySubarraysWithSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 0, 0, 0, 0};
  int         goal     = 0;
  int         expect   = 15;
  int         actual   = solution->numSubarraysWithSum(nums, goal);
  LCD_EXPECT_EQ(expect, actual);
}
