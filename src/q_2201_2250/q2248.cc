// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Intersection of Multiple Arrays
//
// https://leetcode.com/problems/intersection-of-multiple-arrays/
//
// Question ID: 2248
// Difficult  : Easy
// Solve Date : 2023/01/10 14:06

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2248. Intersection of Multiple Arrays|:
//
// Given a 2D integer array |nums| where |nums[i]| is a non-empty array of
// distinct positive integers, return the list of integers that are present in
// each array of |nums| sorted in ascending order.
//

LEETCODE_BEGIN_RESOLVING(2248, IntersectionOfMultipleArrays, Solution);

class Solution {
public:
  vector<int> intersection(vector<vector<int>> &nums) {
    map<int, int> freq;
    vector<int>   res;
    for (auto &v : nums) {
      for (auto x : v) {
        ++freq[x];
      }
    }
    for (auto [x, cnt] : freq) {
      if (cnt == nums.size()) {
        res.emplace_back(x);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= sum(nums[i].length) <= 1000|
// * |1 <= nums[i][j] <= 1000|
// * All the values of |nums[i]| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [[3,1,2,4,5],[1,2,3,4],[3,4,5,6]]
// Output: [3,4]
//
// The only integers present in each of nums[0] = [3,1,2,4,5], nums[1] =
// [1,2,3,4], and nums[2] = [3,4,5,6] are 3 and 4, so we return [3,4].

LEETCODE_SOLUTION_UNITTEST(2248, IntersectionOfMultipleArrays, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {3, 1, 2, 4, 5},
      {1, 2, 3, 4},
      {3, 4, 5, 6}
  };
  vector<int> expect = {3, 4};
  vector<int> actual = solution->intersection(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [[1,2,3],[4,5,6]]
// Output: []
//
// There does not exist any integer present both in nums[0] and nums[1], so we
// return an empty list [].

LEETCODE_SOLUTION_UNITTEST(2248, IntersectionOfMultipleArrays, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {1, 2, 3},
      {4, 5, 6}
  };
  vector<int> expect = {};
  vector<int> actual = solution->intersection(nums);
  LCD_EXPECT_EQ(expect, actual);
}
