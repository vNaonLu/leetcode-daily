// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Array is Good
//
// https://leetcode.com/problems/check-if-array-is-good/
//
// Question ID: 2784
// Difficult  : Easy
// Solve Date : 2023/12/31 14:19

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2784. Check if Array is Good|:
//
// You are given an integer array |nums|. We consider an array good if it is a
// permutation of an array |base[n]|. |base[n] = [1, 2, ..., n - 1, n, n] |(in
// other words, it is an array of length |n + 1| which contains |1| to |n - 1
// |exactly once, plus two occurrences of |n|). For example, |base[1] = [1, 1]|
// and | base[3] = [1, 2, 3, 3]|. Return |true| if the given array is good,
// otherwise return |false|. Note: A permutation of integers represents an
// arrangement of these numbers.
//
//

LEETCODE_BEGIN_RESOLVING(2784, CheckIfArrayIsGood, Solution);

class Solution {
public:
  bool isGood(vector<int> &nums) {
    int           n = nums.size();
    map<int, int> mp;
    for (auto x : nums) {
      ++mp[x];
    }
    for (int i = 1; i < n; ++i) {
      if (i == n - 1 && mp[i] != 2) {
        return false;
      } else if (i != n - 1 && mp[i] != 1) {
        return false;
      }
    }
    if (mp.size() != n - 1) {
      return false;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= num[i] <= 200|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2, 1, 3]
// Output: false
//
// Since the maximum element of the array is 3, the only candidate n for which
// this array could be a permutation of base[n], is n = 3. However, base[3] has
// four elements but array nums has three. Therefore, it can not be a
// permutation of base[3] = [1, 2, 3, 3]. So the answer is false.

LEETCODE_SOLUTION_UNITTEST(2784, CheckIfArrayIsGood, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3};
  bool        expect   = false;
  bool        actual   = solution->isGood(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1, 3, 3, 2]
// Output: true
//
// Since the maximum element of the array is 3, the only candidate n for which
// this array could be a permutation of base[n], is n = 3. It can be seen that
// nums is a permutation of base[3] = [1, 2, 3, 3] (by swapping the second and
// fourth elements in nums, we reach base[3]). Therefore, the answer is true.

LEETCODE_SOLUTION_UNITTEST(2784, CheckIfArrayIsGood, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 3, 2};
  bool        expect   = true;
  bool        actual   = solution->isGood(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1, 1]
// Output: true
//
// Since the maximum element of the array is 1, the only candidate n for which
// this array could be a permutation of base[n], is n = 1. It can be seen that
// nums is a permutation of base[1] = [1, 1]. Therefore, the answer is true.

LEETCODE_SOLUTION_UNITTEST(2784, CheckIfArrayIsGood, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1};
  bool        expect   = true;
  bool        actual   = solution->isGood(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #4]
//  Input: nums = [3, 4, 4, 1, 2, 1]
// Output: false
//
// Since the maximum element of the array is 4, the only candidate n for which
// this array could be a permutation of base[n], is n = 4. However, base[4] has
// five elements but array nums has six. Therefore, it can not be a permutation
// of base[4] = [1, 2, 3, 4, 4]. So the answer is false.

LEETCODE_SOLUTION_UNITTEST(2784, CheckIfArrayIsGood, example_4) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 4, 1, 2, 1};
  bool        expect   = false;
  bool        actual   = solution->isGood(nums);
  LCD_EXPECT_EQ(expect, actual);
}
