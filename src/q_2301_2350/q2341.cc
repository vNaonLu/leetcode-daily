// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Pairs in Array
//
// https://leetcode.com/problems/maximum-number-of-pairs-in-array/
//
// Question ID: 2341
// Difficult  : Easy
// Solve Date : 2023/05/02 18:43

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2341. Maximum Number of Pairs in Array|:
//
// You are given a 0-indexed integer array |nums|. In one operation, you may do
// the following:
//
//  • Choose two integers in |nums| that are equal.
//
//  • Remove both integers from |nums|, forming a pair.
// The operation is done on |nums| as many times as possible.
// Return a 0-indexed integer array |answer| of size |2| where |answer[0]| is
// the number of pairs that are formed and |answer[1]| is the number of leftover
// integers in |nums| after doing the operation as many times as possible.
//
//

LEETCODE_BEGIN_RESOLVING(2341, MaximumNumberOfPairsInArray, Solution);

class Solution {
public:
  vector<int> numberOfPairs(vector<int> &nums) {
    vector<int> freq(101);
    vector<int> res(2, 0);
    for (auto x : nums) {
      ++freq[x];
    }
    for (auto cnt : freq) {
      if (cnt & 1) {
        ++res[1];
      }
      res[0] += cnt / 2;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |0 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,2,1,3,2,2]
// Output: [3,1]
//
// Form a pair with nums[0] and nums[3] and remove them from nums. Now, nums =
// [3,2,3,2,2]. Form a pair with nums[0] and nums[2] and remove them from nums.
// Now, nums = [2,2,2]. Form a pair with nums[0] and nums[1] and remove them
// from nums. Now, nums = [2]. No more pairs can be formed. A total of 3 pairs
// have been formed, and there is 1 number leftover in nums.

LEETCODE_SOLUTION_UNITTEST(2341, MaximumNumberOfPairsInArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 2, 1, 3, 2, 2};
  vector<int> expect   = {3, 1};
  vector<int> actual   = solution->numberOfPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1]
// Output: [1,0]
//
// Form a pair with nums[0] and nums[1] and remove them from nums. Now, nums =
// []. No more pairs can be formed. A total of 1 pair has been formed, and there
// are 0 numbers leftover in nums.

LEETCODE_SOLUTION_UNITTEST(2341, MaximumNumberOfPairsInArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1};
  vector<int> expect   = {1, 0};
  vector<int> actual   = solution->numberOfPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [0]
// Output: [0,1]
//
// No pairs can be formed, and there is 1 number leftover in nums.

LEETCODE_SOLUTION_UNITTEST(2341, MaximumNumberOfPairsInArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0};
  vector<int> expect   = {0, 1};
  vector<int> actual   = solution->numberOfPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}
