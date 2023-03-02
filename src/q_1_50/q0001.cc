// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Two Sum
//
// https://leetcode.com/problems/two-sum/
//
// Question ID: 1
// Difficult  : Easy
// Solve Date : 2021/09/06 08:00

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1. Two Sum|:
//
// Given an array of integers |nums| and an integer |target|, return indices of
// the two numbers such that they add up to |target|. You may assume that each
// input would have exactly one solution, and you may not use the same element
// twice. You can return the answer in any order.  
//

LEETCODE_BEGIN_RESOLVING(1, TwoSum, Solution);

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    auto memo = unordered_map<int, int>();
    for (int i = 0; i < nums.size(); ++i) {
      auto find = memo.find(target - nums[i]);
      if (find != memo.end()) {
        return vector<int>{find->second, i};
      }
      memo.emplace(nums[i], i);
    }
    return vector<int>{-1, -1};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁴|
// * |-10⁹ <= nums[i] <= 10⁹|
// * |-10⁹ <= target <= 10⁹|
// * Only one valid answer exists.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
//
// Because nums[0] + nums[1] == 9, we return [0, 1].

LEETCODE_SOLUTION_UNITTEST(1, TwoSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 7, 11, 15};
  int         target   = 9;
  vector<int> expect   = {0, 1};
  vector<int> actual   = solution->twoSum(nums, target);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,4], target = 6
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(1, TwoSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 4};
  int         target   = 6;
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->twoSum(nums, target);
  EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,3], target = 6
// Output: [0,1]
//

LEETCODE_SOLUTION_UNITTEST(1, TwoSum, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3};
  int         target   = 6;
  vector<int> expect   = {0, 1};
  vector<int> actual   = solution->twoSum(nums, target);
  EXPECT_EQ(expect, actual);
}
