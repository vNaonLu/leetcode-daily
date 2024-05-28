// Copyright 2024 Naon Lu
//
// This file describes the solution of
// The Number of Beautiful Subsets
//
// https://leetcode.com/problems/the-number-of-beautiful-subsets/
//
// Question ID: 2597
// Difficult  : Medium
// Solve Date : 2024/05/23 21:10

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2597. The Number of Beautiful Subsets|:
//
// You are given an array |nums| of positive integers and a positive integer
// |k|. A subset of |nums| is beautiful if it does not contain two integers with
// an absolute difference equal to |k|. Return the number of non-empty beautiful
// subsets of the array |nums|. A subset of |nums| is an array that can be
// obtained by deleting some (possibly none) elements from |nums|. Two subsets
// are different if and only if the chosen indices to delete are different.
//
//

LEETCODE_BEGIN_RESOLVING(2597, TheNumberOfBeautifulSubsets, Solution);

class Solution {
public:
  int beautifulSubsets(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int                 res = 1;
    int                 m   = nums.back();
    int                 q   = (m + k) / k;
    vector<vector<int>> freq(k, vector<int>(q + 1));

    for (auto x : nums) {
      auto [i, r] = div(x, k);
      ++freq[r][i];
    }

    for (int r = 0; r < k; ++r) {
      vector<int> cnt(q + 1, 1);

      for (int i = q - 1; i >= 0; --i) {
        int take = (1 << freq[r][i]) - 1;
        if (i + 1 < q) {
          take *= cnt[i + 2];
        } else {
          take *= cnt[i + 1];
        }
        cnt[i] = cnt[i + 1] + take;
      }

      res *= cnt[0];
    }

    return res - 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 20|
// * |1 <= nums[i], k <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,4,6], k = 2
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2597, TheNumberOfBeautifulSubsets, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 4, 6};
  int         k        = 2;
  int         expect   = 4;
  int         actual   = solution->beautifulSubsets(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1], k = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2597, TheNumberOfBeautifulSubsets, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         k        = 1;
  int         expect   = 1;
  int         actual   = solution->beautifulSubsets(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
