// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Subsequence of Length K With the Largest Sum
//
// https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/
//
// Question ID: 2099
// Difficult  : Easy
// Solve Date : 2023/09/30 11:40

#include <algorithm>
#include <iosfwd>
#include <numeric>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2099. Find Subsequence of Length K With the Largest Sum|:
//
// You are given an integer array |nums| and an integer |k|. You want to find a
// subsequence of |nums| of length |k| that has the largest sum. Return any such
// subsequence as an integer array of length |k|. A subsequence is an array that
// can be derived from another array by deleting some or no elements without
// changing the order of the remaining elements.
//
//

LEETCODE_BEGIN_RESOLVING(2099, FindSubsequenceOfLengthKWithTheLargestSum,
                         Solution);

class Solution {
public:
  vector<int> maxSubsequence(vector<int> &nums, int k) {
    if (nums.size() == k) {
      return nums;
    }
    vector<int> res;
    vector<int> v(nums.begin(), nums.end());
    nth_element(v.begin(), v.begin() + k - 1, v.end(), greater<int>());
    int cnt = count(v.begin(), v.begin() + k, v[k - 1]);
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] > v[k - 1] || (nums[i] == v[k - 1] && --cnt >= 0)) {
        res.emplace_back(nums[i]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |-10⁵ <= nums[i] <= 10⁵|
// * |1 <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,3,3], k = 2
// Output: [3,3]
//
// The subsequence has the largest sum of 3 + 3 = 6.

LEETCODE_SOLUTION_UNITTEST(2099, FindSubsequenceOfLengthKWithTheLargestSum,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3, 3};
  int         k        = 2;
  vector<int> expect   = {3, 3};
  vector<int> actual   = solution->maxSubsequence(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,-2,3,4], k = 3
// Output: [-1,3,4]
//
// The subsequence has the largest sum of -1 + 3 + 4 = 6.

LEETCODE_SOLUTION_UNITTEST(2099, FindSubsequenceOfLengthKWithTheLargestSum,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -2, 3, 4};
  int         k        = 3;
  vector<int> expect   = {-1, 3, 4};
  vector<int> actual   = solution->maxSubsequence(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,4,3,3], k = 2
// Output: [3,4]
//
// The subsequence has the largest sum of 3 + 4 = 7.
// Another possible subsequence is [4, 3].

LEETCODE_SOLUTION_UNITTEST(2099, FindSubsequenceOfLengthKWithTheLargestSum,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 3, 3};
  int         k        = 2;
  vector<int> expect   = {3, 4};
  vector<int> actual   = solution->maxSubsequence(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [50,-75]
// 2
// Output: [50,-75]
//

LEETCODE_SOLUTION_UNITTEST(2099, FindSubsequenceOfLengthKWithTheLargestSum,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {50, -75};
  int         k        = 2;
  vector<int> expect   = {50, -75};
  vector<int> actual   = solution->maxSubsequence(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
