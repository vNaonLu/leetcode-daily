// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Unique Binary String
//
// https://leetcode.com/problems/find-unique-binary-string/
//
// Question ID: 1980
// Difficult  : Medium
// Solve Date : 2023/11/16 19:11

#include <iosfwd>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1980. Find Unique Binary String|:
//
// Given an array of strings |nums| containing |n| unique binary strings each of
// length |n|, return a binary string of length |n| that does not appear in
// |nums|. If there are multiple answers, you may return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(1980, FindUniqueBinaryString, Solution);

class Solution {
public:
  string findDifferentBinaryString(vector<string> &nums) {
    string res;
    for (int i = 0; i < nums.size(); ++i) {
      res.push_back(nums[i][i] == '1' ? '0' : '1');
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 16|
// * |nums[i].length == n|
// * |nums[i] |is either |'0'| or |'1'|.
// * All the strings of |nums| are unique.
///////////////////////////////////////////////////////////////////////////////

bool Verify(vector<string> const &nums, string const &res) {
  unordered_set<string> memo(nums.begin(), nums.end());
  return !memo.count(res);
}

// [Example #1]
//  Input: nums = ["01","10"]
// Output: "11"
//
// "11" does not appear in nums. "00" would also be correct.

LEETCODE_SOLUTION_UNITTEST(1980, FindUniqueBinaryString, example_1) {
  auto           solution = MakeSolution();
  vector<string> nums     = {"01", "10"};
  // string         expect   = "11";
  string actual = solution->findDifferentBinaryString(nums);
  // LCD_EXPECT_EQ(expect, actual);
  EXPECT_TRUE(Verify(nums, actual));
}

// [Example #2]
//  Input: nums = ["00","01"]
// Output: "11"
//
// "11" does not appear in nums. "10" would also be correct.

LEETCODE_SOLUTION_UNITTEST(1980, FindUniqueBinaryString, example_2) {
  auto           solution = MakeSolution();
  vector<string> nums     = {"00", "01"};
  // string         expect   = "11";
  string actual = solution->findDifferentBinaryString(nums);
  // LCD_EXPECT_EQ(expect, actual);
  EXPECT_TRUE(Verify(nums, actual));
}

// [Example #3]
//  Input: nums = ["111","011","001"]
// Output: "101"
//
// "101" does not appear in nums. "000", "010", "100", and "110" would also be
// correct.

LEETCODE_SOLUTION_UNITTEST(1980, FindUniqueBinaryString, example_3) {
  auto           solution = MakeSolution();
  vector<string> nums     = {"111", "011", "001"};
  // string         expect   = "101";
  string actual = solution->findDifferentBinaryString(nums);
  // LCD_EXPECT_EQ(expect, actual);
  EXPECT_TRUE(Verify(nums, actual));
}
