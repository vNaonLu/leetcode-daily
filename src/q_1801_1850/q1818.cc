// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Absolute Sum Difference
//
// https://leetcode.com/problems/minimum-absolute-sum-difference/
//
// Question ID: 1818
// Difficult  : Medium
// Solve Date : 2022/07/20 19:02

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1818. Minimum Absolute Sum Difference|:
//
// You are given two positive integer arrays |nums1| and |nums2|, both of length
// |n|. The absolute sum difference of arrays |nums1| and |nums2| is defined as
// the sum of ||nums1[i] - nums2[i]|| for each |0 <= i < n| (0-indexed). You can
// replace at most one element of |nums1| with any other element in |nums1| to
// minimize the absolute sum difference. Return the minimum absolute sum
// difference after replacing at most one element in the array |nums1|. Since
// the answer may be large, return it modulo |10⁹ + 7|.
// ||x|| is defined as:
//
//  • |x| if |x >= 0|, or
//
//  • |-x| if |x < 0|.
//

LEETCODE_BEGIN_RESOLVING(1818, MinimumAbsoluteSumDifference, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;
  int                         helper(vector<int> &nums1, vector<int> &nums2) {
    auto it1 = nums1.begin(), it2 = nums2.begin();
    int  res = 0;
    while (it1 != nums1.end() && it2 != nums2.end()) {
      res += abs(*it1++ - *it2++);
    }

    return res;
  }

public:
  int minAbsoluteSumDiff(vector<int> &nums1, vector<int> &nums2) {
    vector<int> memo(nums1.begin(), nums1.end());
    sort(memo.begin(), memo.end());

    auto     it1 = nums1.begin(), it2 = nums2.begin();
    uint64_t origin = 0;
    while (it1 != nums1.end() && it2 != nums2.end()) {
      origin += abs(*it1++ - *it2++);
    }

    uint64_t res = origin;
    for (int i = 0; i < nums1.size(); ++i) {
      auto revert = origin - abs(nums1[i] - nums2[i]);
      auto ub     = upper_bound(memo.begin(), memo.end(), nums2[i]);
      auto lb     = lower_bound(memo.begin(), memo.end(), nums2[i]);

      if (lb != memo.end()) {
        res = min(res, revert + abs(*lb - nums2[i]));
      }
      if (ub != memo.begin()) {
        res = min(res, revert + abs(*(ub - 1) - nums2[i]));
      }
    }

    return res % kMod;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums1.length|
// * |n == nums2.length|
// * |1 <= n <= 10⁵|
// * |1 <= nums1[i], nums2[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,7,5], nums2 = [2,3,5]
// Output: 3
//
// There are two possible optimal solutions:
// - Replace the second element with the first: [1,7,5] => [1,1,5], or
// - Replace the second element with the third: [1,7,5] => [1,5,5].
// Both will yield an absolute sum difference of ||1-2| + (|1-3| or |5-3|) +
// |5-5| = |3.

LEETCODE_SOLUTION_UNITTEST(1818, MinimumAbsoluteSumDifference, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 7, 5};
  vector<int> nums2    = {2, 3, 5};
  int         expect   = 3;
  int         actual   = solution->minAbsoluteSumDiff(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [2,4,6,8,10], nums2 = [2,4,6,8,10]
// Output: 0
//
// nums1 is equal to nums2 so no replacement is needed. This will result in an
// absolute sum difference of 0.

LEETCODE_SOLUTION_UNITTEST(1818, MinimumAbsoluteSumDifference, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 4, 6, 8, 10};
  vector<int> nums2    = {2, 4, 6, 8, 10};
  int         expect   = 0;
  int         actual   = solution->minAbsoluteSumDiff(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums1 = [1,10,4,4,2,7], nums2 = [9,3,5,1,7,4]
// Output: 20
//
// Replace the first element with the second: [1,10,4,4,2,7] => [10,10,4,4,2,7].
// This yields an absolute sum difference of ||10-9| + |10-3| + |4-5| + |4-1| +
// |2-7| + |7-4| = 20|

LEETCODE_SOLUTION_UNITTEST(1818, MinimumAbsoluteSumDifference, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 10, 4, 4, 2, 7};
  vector<int> nums2    = {9, 3, 5, 1, 7, 4};
  int         expect   = 20;
  int         actual   = solution->minAbsoluteSumDiff(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}
