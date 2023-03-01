// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Contains Duplicate II
//
// https://leetcode.com/problems/contains-duplicate-ii/
//
// Question ID: 219
// Difficult  : Easy
// Solve Date : 2022/06/07 18:25

#include <algorithm>
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |219. Contains Duplicate II|:
//
// Given an integer array |nums| and an integer |k|, return |true| if there are
// two distinct indices |i| and |j| in the array such that |nums[i] == nums[j]|
// and |abs(i - j) <= k|.
//

LEETCODE_BEGIN_RESOLVING(219, ContainsDuplicateII, Solution);

class Solution {
public:
  bool containsNearbyDuplicate(vector<int> &nums, int k) {
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < nums.size(); ++i) {
      mp[nums[i]].emplace_back(i);
    }

    for (auto &[c, v] : mp) {
      if (v.size() > 1) {
        sort(v.begin(), v.end());

        for (int i = 1; i < v.size(); ++i) {
          if (abs(v[i - 1] - v[i]) <= k) {
            return true;
          }
        }
      }
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
// * |0 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,1], k = 3
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(219, ContainsDuplicateII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 1};
  int         k        = 3;
  bool        expect   = true;
  bool        actual   = solution->containsNearbyDuplicate(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,0,1,1], k = 1
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(219, ContainsDuplicateII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 0, 1, 1};
  int         k        = 1;
  bool        expect   = true;
  bool        actual   = solution->containsNearbyDuplicate(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,1,2,3], k = 2
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(219, ContainsDuplicateII, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 1, 2, 3};
  int         k        = 2;
  bool        expect   = false;
  bool        actual   = solution->containsNearbyDuplicate(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
