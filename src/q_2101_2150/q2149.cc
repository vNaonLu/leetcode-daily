// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rearrange Array Elements by Sign
//
// https://leetcode.com/problems/rearrange-array-elements-by-sign/
//
// Question ID: 2149
// Difficult  : Medium
// Solve Date : 2022/04/01 18:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2149. Rearrange Array Elements by Sign|:
//
// You are given a 0-indexed integer array |nums| of even length consisting of
// an equal number of positive and negative integers. You should rearrange the
// elements of |nums| such that the modified array follows the given conditions:
//
//  1. Every consecutive pair of integers have opposite signs.
//
//  2. For all integers with the same sign, the order in which they were present
//  in |nums| is preserved.
//
//  3. The rearranged array begins with a positive integer.
// Return the modified array after rearranging the elements to satisfy the
// aforementioned conditions.  
//

LEETCODE_BEGIN_RESOLVING(2149, RearrangeArrayElementsBySign, Solution);

class Solution {
public:
  vector<int> rearrangeArray(vector<int> &nums) {
    int         n = nums.size();
    int         i = 0, j = 1;
    auto        it = nums.begin();
    vector<int> res(n, 0);

    while (i < n || j < n) {
      if (*it > 0) {
        res[i] = *it;
        ++ ++i;
      } else {
        res[j] = *it;
        ++ ++j;
      }

      ++it;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 2 * 10⁵|
// * |nums.length| is even
// * |1 <= |nums[i]| <= 10⁵|
// * |nums| consists of equal number of positive and negative integers.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1,-2,-5,2,-4]
// Output: [3,-2,1,-5,2,-4]
//
// The positive integers in nums are [3,1,2]. The negative integers are
// [-2,-5,-4]. The only possible way to rearrange them such that they satisfy
// all conditions is [3,-2,1,-5,2,-4]. Other ways such as [1,-2,2,-5,3,-4],
// [3,1,2,-2,-5,-4], [-2,3,-5,1,-4,2] are incorrect because they do not satisfy
// one or more conditions.

LEETCODE_SOLUTION_UNITTEST(2149, RearrangeArrayElementsBySign, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, -2, -5, 2, -4};
  vector<int> expect   = {3, -2, 1, -5, 2, -4};
  vector<int> actual   = solution->rearrangeArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,1]
// Output: [1,-1]
//
// 1 is the only positive integer and -1 the only negative integer in nums.
// So nums is rearranged to [1,-1].

LEETCODE_SOLUTION_UNITTEST(2149, RearrangeArrayElementsBySign, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 1};
  vector<int> expect   = {1, -1};
  vector<int> actual   = solution->rearrangeArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
