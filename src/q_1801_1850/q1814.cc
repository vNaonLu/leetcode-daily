// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Nice Pairs in an Array
//
// https://leetcode.com/problems/count-nice-pairs-in-an-array/
//
// Question ID: 1814
// Difficult  : Medium
// Solve Date : 2023/11/21 19:11

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1814. Count Nice Pairs in an Array|:
//
// You are given an array |nums| that consists of non-negative integers. Let us
// define |rev(x)| as the reverse of the non-negative integer |x|. For example,
// |rev(123) = 321|, and |rev(120) = 21|. A pair of indices |(i, j)| is nice if
// it satisfies all of the following conditions:
//
//  • |0 <= i < j < nums.length|
//
//  • |nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])|
// Return the number of nice pairs of indices. Since that number can be too
// large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1814, CountNicePairsInAnArray, Solution);

class Solution {
public:
  int countNicePairs(vector<int> &nums) {
    int           res = 0;
    map<int, int> mp;
    for (int i = 0; i < nums.size(); ++i) {
      nums[i] = nums[i] - rev(nums[i]);
      ++mp[nums[i]];
    }
    for (auto &[x, cnt] : mp) {
      if (cnt > 1) {
        res = (res + fact(cnt - 1)) % kMod;
      }
    }
    return res;
  }

private:
  constexpr static int kMod = 1e9 + 7;
  int                  rev(int n) {
    int res = 0;
    while (n) {
      res = res * 10 + n % 10;
      n /= 10;
    }
    return res;
  }

  int64_t fact(int64_t n) { return n * (n + 1) / 2; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [42,11,1,97]
// Output: 2
//
// The two pairs are:
//  - (0,3) : 42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121.
//  - (1,2) : 11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12.

LEETCODE_SOLUTION_UNITTEST(1814, CountNicePairsInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {42, 11, 1, 97};
  int         expect   = 2;
  int         actual   = solution->countNicePairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [13,10,35,24,76]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1814, CountNicePairsInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {13, 10, 35, 24, 76};
  int         expect   = 4;
  int         actual   = solution->countNicePairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}
