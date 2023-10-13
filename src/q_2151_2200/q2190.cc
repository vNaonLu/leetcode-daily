// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Most Frequent Number Following Key In an Array
//
// https://leetcode.com/problems/most-frequent-number-following-key-in-an-array/
//
// Question ID: 2190
// Difficult  : Easy
// Solve Date : 2023/10/13 10:56

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2190. Most Frequent Number Following Key In an Array|:
//
// You are given a 0-indexed integer array |nums|. You are also given an integer
// |key|, which is present in |nums|. For every unique integer |target| in
// |nums|, count the number of times |target| immediately follows an occurrence
// of |key| in |nums|. In other words, count the number of indices |i| such
// that:
//
//  • |0 <= i <= nums.length - 2|,
//
//  • |nums[i] == key| and,
//
//  • |nums[i + 1] == target|.
// Return the |target| with the maximum count. The test cases will be generated
// such that the |target| with maximum count is unique.
//
//

LEETCODE_BEGIN_RESOLVING(2190, MostFrequentNumberFollowingKeyInAnArray,
                         Solution);

class Solution {
public:
  int mostFrequent(vector<int> &nums, int key) {
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size() - 1; ++i) {
      if (nums[i] == key) {
        ++mp[nums[i + 1]];
      }
    }
    int maxi = -1;
    int res  = -1;
    for (auto it : mp) {
      if (maxi < it.second) {
        maxi = it.second;
        res  = it.first;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 1000|
// * |1 <= nums[i] <= 1000|
// * The test cases will be generated such that the answer is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,100,200,1,100], key = 1
// Output: 100
//
// For target = 100, there are 2 occurrences at indices 1 and 4 which follow an
// occurrence of key. No other integers follow an occurrence of key, so we
// return 100.

LEETCODE_SOLUTION_UNITTEST(2190, MostFrequentNumberFollowingKeyInAnArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 100, 200, 1, 100};
  int         key      = 1;
  int         expect   = 100;
  int         actual   = solution->mostFrequent(nums, key);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,2,2,3], key = 2
// Output: 2
//
// For target = 2, there are 3 occurrences at indices 1, 2, and 3 which follow
// an occurrence of key. For target = 3, there is only one occurrence at index 4
// which follows an occurrence of key. target = 2 has the maximum number of
// occurrences following an occurrence of key, so we return 2.

LEETCODE_SOLUTION_UNITTEST(2190, MostFrequentNumberFollowingKeyInAnArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2, 2, 3};
  int         key      = 2;
  int         expect   = 2;
  int         actual   = solution->mostFrequent(nums, key);
  LCD_EXPECT_EQ(expect, actual);
}
