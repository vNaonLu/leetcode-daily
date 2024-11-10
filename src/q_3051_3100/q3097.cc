// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Shortest Subarray With OR at Least K II
//
// https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/
//
// Question ID: 3097
// Difficult  : Medium
// Solve Date : 2024/11/10 14:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3097. Shortest Subarray With OR at Least K II|:
//
// You are given an array |nums| of non-negative integers and an integer |k|.
// An array is called special if the bitwise |OR| of all of its elements is at
// least |k|. Return the length of the shortest special non-empty subarray of
// |nums|, or return |-1| if no special subarray exists.
//
//

LEETCODE_BEGIN_RESOLVING(3097, ShortestSubarrayWithORAtLeastKII, Solution);

class Solution {
public:
  int minimumSubarrayLength(vector<int> &nums, int k) {
    int         res = numeric_limits<int>::max();
    vector<int> v(30, 0);
    auto        beg = nums.begin();
    auto        end = nums.begin();
    while (end != nums.end()) {
      if (*end >= k) {
        return 1;
      }

      int i = 0;
      int t = *end;
      while (t && i < 30) {
        v[i++] += t & 1;
        t >>= 1;
      }

      while (beg != nums.end() && check(v, k)) {
        res = min<int>(res, distance(beg, end) + 1);
        i   = 0;
        t   = *beg;
        while (t && i < 30) {
          v[i++] -= t & 1;
          t >>= 1;
        }
        ++beg;
      }
      ++end;
    }
    return res == numeric_limits<int>::max() ? -1 : res;
  }

private:
  bool check(vector<int> const &v, int k) {
    int res = 0;
    for (int i = 0; i < 30; ++i) {
      res |= (v[i] ? (1 << i) : 0);
    }
    return res >= k;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁵|
// * |0 <= nums[i] <= 10⁹|
// * |0 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3], k = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3097, ShortestSubarrayWithORAtLeastKII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         k        = 2;
  int         expect   = 1;
  int         actual   = solution->minimumSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,8], k = 10
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3097, ShortestSubarrayWithORAtLeastKII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 8};
  int         k        = 10;
  int         expect   = 3;
  int         actual   = solution->minimumSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2], k = 0
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3097, ShortestSubarrayWithORAtLeastKII, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  int         k        = 0;
  int         expect   = 1;
  int         actual   = solution->minimumSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
