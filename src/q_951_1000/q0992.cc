// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Subarrays with K Different Integers
//
// https://leetcode.com/problems/subarrays-with-k-different-integers/
//
// Question ID: 992
// Difficult  : Hard
// Solve Date : 2024/03/30 15:10

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |992. Subarrays with K Different Integers|:
//
// Given an integer array |nums| and an integer |k|, return the number of good
// subarrays of |nums|. A good array is an array where the number of different
// integers in that array is exactly |k|.
//
//  • For example, |[1,2,3,1,2]| has |3| different integers: |1|, |2|, and |3|.
// A subarray is a contiguous part of an array.
//
//

LEETCODE_BEGIN_RESOLVING(992, SubarraysWithKDifferentIntegers, Solution);

class Solution {
public:
  int subarraysWithKDistinct(vector<int> &nums, int k) {
    return helper(nums, k) - helper(nums, k - 1);
  }

private:
  int helper(vector<int> &nums, int k) {
    int                     n = nums.size();
    unordered_map<int, int> mp;
    int                     i   = 0;
    int                     j   = 0;
    int                     res = 0;
    while (j < n) {
      ++mp[nums[j]];
      while (i <= j && mp.size() > k) {
        if (--mp[nums[i]] == 0) {
          mp.erase(nums[i]);
        }
        ++i;
      }

      res += (j - i + 1);
      ++j;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁴|
// * |1 <= nums[i], k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1,2,3], k = 2
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(992, SubarraysWithKDifferentIntegers, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 2, 3};
  int         k        = 2;
  int         expect   = 7;
  int         actual   = solution->subarraysWithKDistinct(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,1,3,4], k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(992, SubarraysWithKDifferentIntegers, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 3, 4};
  int         k        = 3;
  int         expect   = 3;
  int         actual   = solution->subarraysWithKDistinct(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
