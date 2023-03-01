// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Difference of Two Arrays
//
// https://leetcode.com/problems/find-the-difference-of-two-arrays/
//
// Question ID: 2215
// Difficult  : Easy
// Solve Date : 2023/02/08 18:17

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2215. Find the Difference of Two Arrays|:
//
// Given two 0-indexed integer arrays |nums1| and |nums2|, return a list
// |answer| of size |2| where:
//
//  • |answer[0]| is a list of all distinct integers in |nums1| which are not
//  present in |nums2|.
//
//  • |answer[1]| is a list of all distinct integers in |nums2| which are not
//  present in |nums1|.
// Note that the integers in the lists may be returned in any order.
//

LEETCODE_BEGIN_RESOLVING(2215, FindTheDifferenceOfTwoArrays, Solution);

class Solution {
public:
  vector<vector<int>> findDifference(vector<int> &nums1, vector<int> &nums2) {
    unordered_set<int> occ1(nums1.begin(), nums1.end());
    unordered_set<int> occ2(nums2.begin(), nums2.end());
    vector<set<int>>   res(2);
    for (auto x : nums1) {
      if (!occ2.count(x)) {
        res[0].emplace(x);
      }
    }
    for (auto x : nums2) {
      if (!occ1.count(x)) {
        res[1].emplace(x);
      }
    }
    return vector<vector<int>>{vector<int>(res[0].begin(), res[0].end()),
                               vector<int>(res[1].begin(), res[1].end())};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 1000|
// * |-1000 <= nums1[i], nums2[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,2,3], nums2 = [2,4,6]
// Output: [[1,3],[4,6]]
// Explanation:
// For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] = 1
// and nums1[2] = 3 are not present in nums2. Therefore, answer[0] = [1,3]. For
// nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] = 4 and
// nums2[2] = 6 are not present in nums2. Therefore, answer[1] = [4,6].
//

LEETCODE_SOLUTION_UNITTEST(2215, FindTheDifferenceOfTwoArrays, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums1    = {1, 2, 3};
  vector<int>         nums2    = {2, 4, 6};
  vector<vector<int>> expect   = {
      {1, 3},
      {4, 6}
  };
  vector<vector<int>> actual = solution->findDifference(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [1,2,3,3], nums2 = [1,1,2,2]
// Output: [[3],[]]
// Explanation:
// For nums1, nums1[2] and nums1[3] are not present in nums2. Since nums1[2] ==
// nums1[3], their value is only included once and answer[0] = [3]. Every
// integer in nums2 is present in nums1. Therefore, answer[1] = [].
//

LEETCODE_SOLUTION_UNITTEST(2215, FindTheDifferenceOfTwoArrays, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums1    = {1, 2, 3, 3};
  vector<int>         nums2    = {1, 1, 2, 2};
  vector<vector<int>> expect   = {{3}, {}};
  vector<vector<int>> actual   = solution->findDifference(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}
