// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find K-th Smallest Pair Distance
//
// https://leetcode.com/problems/find-k-th-smallest-pair-distance/
//
// Question ID: 719
// Difficult  : Hard
// Solve Date : 2024/08/14 21:03

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |719. Find K-th Smallest Pair Distance|:
//
// The distance of a pair of integers |a| and |b| is defined as the absolute
// difference between |a| and |b|. Given an integer array |nums| and an integer
// |k|, return the |kᵗʰ| smallest distance among all the pairs |nums[i]| and
// |nums[j]| where |0 <= i < j < nums.length|.
//
//

LEETCODE_BEGIN_RESOLVING(719, FindKThSmallestPairDistance, Solution);

class Solution {
public:
  int smallestDistancePair(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int lo = 0;
    int hi = nums.back() - nums.front();
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (count(nums, mid) < k) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return lo;
  }

private:
  int count(vector<int> const &nums, int dist) {
    int cnt  = 0;
    int left = 0;
    for (int right = 1; right < nums.size(); ++right) {
      while (nums[right] - nums[left] > dist) {
        ++left;
      }
      cnt += right - left;
    }
    return cnt;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |2 <= n <= 10⁴|
// * |0 <= nums[i] <= 10⁶|
// * |1 <= k <= n * (n - 1) / 2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,1], k = 1
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(719, FindKThSmallestPairDistance, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 1};
  int         k        = 1;
  int         expect   = 0;
  int         actual   = solution->smallestDistancePair(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1], k = 2
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(719, FindKThSmallestPairDistance, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  int         k        = 2;
  int         expect   = 0;
  int         actual   = solution->smallestDistancePair(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,6,1], k = 3
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(719, FindKThSmallestPairDistance, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 6, 1};
  int         k        = 3;
  int         expect   = 5;
  int         actual   = solution->smallestDistancePair(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [62,100,4]
// 2
// Output: 58
//

LEETCODE_SOLUTION_UNITTEST(719, FindKThSmallestPairDistance, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {62, 100, 4};
  int         k        = 2;
  int         expect   = 58;
  int         actual   = solution->smallestDistancePair(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
