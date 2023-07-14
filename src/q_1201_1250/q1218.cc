// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Arithmetic Subsequence of Given Difference
//
// https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/
//
// Question ID: 1218
// Difficult  : Medium
// Solve Date : 2023/07/14 15:33

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1218. Longest Arithmetic Subsequence of Given Difference|:
//
// Given an integer array |arr| and an integer |difference|, return the length
// of the longest subsequence in |arr| which is an arithmetic sequence such that
// the difference between adjacent elements in the subsequence equals
// |difference|. A subsequence is a sequence that can be derived from |arr| by
// deleting some or no elements without changing the order of the remaining
// elements.
//
//

LEETCODE_BEGIN_RESOLVING(1218, LongestArithmeticSubsequenceOfGivenDifference,
                         Solution);

class Solution {
public:
  int longestSubsequence(vector<int> &arr, int difference) {
    int                     res = 1;
    unordered_map<int, int> memo;
    for (auto x : arr) {
      auto find = memo.find(x - difference);
      if (find != memo.end()) {
        memo[x] = find->second + 1;
      } else {
        memo[x] = 1;
      }
      res = max(res, memo[x]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁵|
// * |-10⁴ <= arr[i], difference <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,3,4], difference = 1
// Output: 4
//
// The longest arithmetic subsequence is [1,2,3,4].

LEETCODE_SOLUTION_UNITTEST(1218, LongestArithmeticSubsequenceOfGivenDifference,
                           example_1) {
  auto        solution   = MakeSolution();
  vector<int> arr        = {1, 2, 3, 4};
  int         difference = 1;
  int         expect     = 4;
  int         actual     = solution->longestSubsequence(arr, difference);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,3,5,7], difference = 1
// Output: 1
//
// The longest arithmetic subsequence is any single element.

LEETCODE_SOLUTION_UNITTEST(1218, LongestArithmeticSubsequenceOfGivenDifference,
                           example_2) {
  auto        solution   = MakeSolution();
  vector<int> arr        = {1, 3, 5, 7};
  int         difference = 1;
  int         expect     = 1;
  int         actual     = solution->longestSubsequence(arr, difference);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
// Output: 4
//
// The longest arithmetic subsequence is [7,5,3,1].

LEETCODE_SOLUTION_UNITTEST(1218, LongestArithmeticSubsequenceOfGivenDifference,
                           example_3) {
  auto        solution   = MakeSolution();
  vector<int> arr        = {1, 5, 7, 8, 5, 3, 4, 2, 1};
  int         difference = -2;
  int         expect     = 4;
  int         actual     = solution->longestSubsequence(arr, difference);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [3,0,-3,4,-4,7,6]
// 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1218, LongestArithmeticSubsequenceOfGivenDifference,
                           extra_testcase_1) {
  auto        solution   = MakeSolution();
  vector<int> arr        = {3, 0, -3, 4, -4, 7, 6};
  int         difference = 3;
  int         expect     = 2;
  int         actual     = solution->longestSubsequence(arr, difference);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [4,12,10,0,-2,7,-8,9,-9,-12,-12,8,8]
// 0
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1218, LongestArithmeticSubsequenceOfGivenDifference,
                           extra_testcase_2) {
  auto        solution   = MakeSolution();
  vector<int> arr        = {4, 12, 10, 0, -2, 7, -8, 9, -9, -12, -12, 8, 8};
  int         difference = 0;
  int         expect     = 2;
  int         actual     = solution->longestSubsequence(arr, difference);
  LCD_EXPECT_EQ(expect, actual);
}
