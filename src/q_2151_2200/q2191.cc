// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Sort the Jumbled Numbers
//
// https://leetcode.com/problems/sort-the-jumbled-numbers/
//
// Question ID: 2191
// Difficult  : Medium
// Solve Date : 2024/07/24 12:18

#include <algorithm>
#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2191. Sort the Jumbled Numbers|:
//
// You are given a 0-indexed integer array |mapping| which represents the
// mapping rule of a shuffled decimal system. |mapping[i] = j| means digit |i|
// should be mapped to digit |j| in this system. The mapped value of an integer
// is the new integer obtained by replacing each occurrence of digit |i| in the
// integer with |mapping[i]| for all |0 <= i <= 9|. You are also given another
// integer array |nums|. Return the array |nums| sorted in non-decreasing order
// based on the mapped values of its elements. Notes:
//
//  • Elements with the same mapped values should appear in the same relative
//  order as in the input.
//
//  • The elements of |nums| should only be sorted based on their mapped values
//  and not be replaced by them.
//
//

LEETCODE_BEGIN_RESOLVING(2191, SortTheJumbledNumbers, Solution);

class Solution {
public:
  vector<int> sortJumbled(vector<int> &mapping, vector<int> &nums) {
    int                   n = nums.size();
    vector<array<int, 3>> mpn(n);
    for (int i = 0; i < n; ++i) {
      int x  = nums[i];
      mpn[i] = {decode(mapping, x), i, x};
    }
    sort(mpn.begin(), mpn.end());
    for (int i = 0; i < n; ++i) {
      nums[i] = mpn[i][2];
    }
    return nums;
  }

private:
  int decode(vector<int> const &mp, int x) {
    if (x == 0) {
      return mp[0];
    }
    int ret = 0;
    for (int p = 1; x > 0; p *= 10) {
      auto [q, r] = div(x, 10);
      ret += mp[r] * p;
      x = q;
    }
    return ret;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |mapping.length == 10|
// * |0 <= mapping[i] <= 9|
// * All the values of |mapping[i]| are unique.
// * |1 <= nums.length <= 3 * 10⁴|
// * |0 <= nums[i] < 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
// Output: [338,38,991]
//

LEETCODE_SOLUTION_UNITTEST(2191, SortTheJumbledNumbers, example_1) {
  auto        solution = MakeSolution();
  vector<int> mapping  = {8, 9, 4, 0, 2, 1, 3, 5, 7, 6};
  vector<int> nums     = {991, 338, 38};
  vector<int> expect   = {338, 38, 991};
  vector<int> actual   = solution->sortJumbled(mapping, nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mapping = [0,1,2,3,4,5,6,7,8,9], nums = [789,456,123]
// Output: [123,456,789]
//

LEETCODE_SOLUTION_UNITTEST(2191, SortTheJumbledNumbers, example_2) {
  auto        solution = MakeSolution();
  vector<int> mapping  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> nums     = {789, 456, 123};
  vector<int> expect   = {123, 456, 789};
  vector<int> actual   = solution->sortJumbled(mapping, nums);
  LCD_EXPECT_EQ(expect, actual);
}
