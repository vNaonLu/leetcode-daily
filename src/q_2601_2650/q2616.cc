// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimize the Maximum Difference of Pairs
//
// https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/
//
// Question ID: 2616
// Difficult  : Medium
// Solve Date : 2023/08/09 12:06

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2616. Minimize the Maximum Difference of Pairs|:
//
// You are given a 0-indexed integer array |nums| and an integer |p|. Find |p|
// pairs of indices of |nums| such that the maximum difference amongst all the
// pairs is minimized. Also, ensure no index appears more than once amongst the
// |p| pairs. Note that for a pair of elements at the index |i| and |j|, the
// difference of this pair is ||nums[i] - nums[j]||, where ||x|| represents the
// absolute value of |x|. Return the minimum maximum difference among all |p|
// pairs. We define the maximum of an empty set to be zero.
//
//

LEETCODE_BEGIN_RESOLVING(2616, MinimizeTheMaximumDifferenceOfPairs, Solution);

class Solution {
public:
  int minimizeMax(vector<int> &nums, int p) {
    sort(nums.begin(), nums.end());

    int lo = 0;
    int hi = nums.back() - nums.front();
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (helper(nums, mid, p)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    return lo;
  }

private:
  bool helper(vector<int> &nums, int d, int p) {
    int c = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
      if (nums[i + 1] - nums[i] <= d) {
        ++c;
        ++i;
      }

      if (c >= p) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁹|
// * |0 <= p <= (nums.length)/2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,1,2,7,1,3], p = 2
// Output: 1
//
// The first pair is formed from the indices 1 and 4, and the second pair is
// formed from the indices 2 and 5. The maximum difference is max(|nums[1] -
// nums[4]|, |nums[2] - nums[5]|) = max(0, 1) = 1. Therefore, we return 1.

LEETCODE_SOLUTION_UNITTEST(2616, MinimizeTheMaximumDifferenceOfPairs,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 1, 2, 7, 1, 3};
  int         p        = 2;
  int         expect   = 1;
  int         actual   = solution->minimizeMax(nums, p);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,2,1,2], p = 1
// Output: 0
//
// Let the indices 1 and 3 form a pair. The difference of that pair is |2 - 2| =
// 0, which is the minimum we can attain.

LEETCODE_SOLUTION_UNITTEST(2616, MinimizeTheMaximumDifferenceOfPairs,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 1, 2};
  int         p        = 1;
  int         expect   = 0;
  int         actual   = solution->minimizeMax(nums, p);
  LCD_EXPECT_EQ(expect, actual);
}
