// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Single Number III
//
// https://leetcode.com/problems/single-number-iii/
//
// Question ID: 260
// Difficult  : Medium
// Solve Date : 2021/11/06 20:07

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |260. Single Number III|:
//
// Given an integer array |nums|, in which exactly two elements appear only once
// and all the other elements appear exactly twice. Find the two elements that
// appear only once. You can return the answer in any order. You must write
// an algorithm that runs in linear runtime complexity and uses only constant
// extra space.  
//

LEETCODE_BEGIN_RESOLVING(260, SingleNumberIII, Solution);

class Solution {
public:
  vector<int> singleNumber(vector<int> &nums) {
    vector<int> res;
    res.reserve(nums.size());
    unordered_map<int, int> cnt;
    for (const auto &x : nums)
      ++cnt[x];
    for (auto it = cnt.begin(); it != cnt.end(); ++it)
      if (it->second == 1)
        res.emplace_back(it->first);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 3 * 10⁴|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
// * Each integer in |nums| will appear twice, only two integers will appear
// once.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1,3,2,5]
// Output: [3,5]
//
// [5, 3] is also a valid answer.

LEETCODE_SOLUTION_UNITTEST(260, SingleNumberIII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 3, 2, 5};
  vector<int> expect   = {3, 5};
  vector<int> actual   = solution->singleNumber(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,0]
// Output: [-1,0]
//

LEETCODE_SOLUTION_UNITTEST(260, SingleNumberIII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 0};
  vector<int> expect   = {-1, 0};
  vector<int> actual   = solution->singleNumber(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [0,1]
// Output: [1,0]
//

LEETCODE_SOLUTION_UNITTEST(260, SingleNumberIII, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1};
  vector<int> expect   = {1, 0};
  vector<int> actual   = solution->singleNumber(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}
