// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Majority Element II
//
// https://leetcode.com/problems/majority-element-ii/
//
// Question ID: 229
// Difficult  : Medium
// Solve Date : 2022/08/22 23:47

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |229. Majority Element II|:
//
// Given an integer array of size |n|, find all elements that appear more than
// |⌊ n/3 ⌋| times.
//

LEETCODE_BEGIN_RESOLVING(229, MajorityElementII, Solution);

class Solution {
public:
  vector<int> majorityElement(vector<int> &nums) {
    auto n    = nums.size();
    auto freq = unordered_map<int, int>();
    auto res  = set<int>();

    for (auto x : nums) {
      ++freq[x];
      if (freq[x] > n / 3) {
        res.emplace(x);
      }
    }

    return vector<int>(res.begin(), res.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5 * 10⁴|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,3]
// Output: [3]
//

LEETCODE_SOLUTION_UNITTEST(229, MajorityElementII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 3};
  vector<int> expect   = {3};
  vector<int> actual   = solution->majorityElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(229, MajorityElementII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  vector<int> expect   = {1};
  vector<int> actual   = solution->majorityElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2]
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(229, MajorityElementII, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->majorityElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}
