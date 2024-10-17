// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Construct the Minimum Bitwise Array I
//
// https://leetcode.com/problems/construct-the-minimum-bitwise-array-i/
//
// Question ID: 3314
// Difficult  : Easy
// Solve Date : 2024/10/17 20:00

#include <array>
#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3314. Construct the Minimum Bitwise Array I|:
//
// You are given an array |nums| consisting of |n| prime integers.
// You need to construct an array |ans| of length |n|, such that, for each index
// |i|, the bitwise |OR| of |ans[i]| and |ans[i] + 1| is equal to |nums[i]|,
// i.e. |ans[i] OR (ans[i] + 1) == nums[i]|. Additionally, you must minimize
// each value of |ans[i]| in the resulting array. If it is not possible to find
// such a value for |ans[i]| that satisfies the condition, then set |ans[i] =
// -1|.
//
//

LEETCODE_BEGIN_RESOLVING(3314, ConstructTheMinimumBitwiseArrayI, Solution);

class Solution {
  static consteval int log2_32(uint32_t value) {
    const int tab32[32] = {0,  9,  1,  10, 13, 21, 2,  29, 11, 14, 16,
                           18, 22, 25, 3,  30, 8,  12, 20, 28, 15, 17,
                           24, 7,  19, 27, 23, 6,  26, 5,  4,  31};
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return tab32[(uint32_t)(value * 0x07C4ACDD) >> 27];
  }
  static consteval array<int, 1000> getAns() {
    array<int, 1000> res;
    for (int i = 0; i < res.size(); ++i) {
      if (i % 4 == 1) {
        res[i] = i - 1;
      } else if (i % 4 == 3) {
        int x = i;
        for (int j = 0; j < log2_32(i) + 1; ++j) {
          x /= 2;
          if (x % 2 == 0) {
            res[i] = i - (1 << j);
            break;
          }
        }
      } else {
        res[i] = -1;
      }
    }
    return res;
  }

public:
  vector<int> minBitwiseArray(vector<int> &nums) {
    vector<int> res;
    const auto  table = getAns();
    for (auto x : nums) {
      res.emplace_back(table[x]);
    }
    return res;
  }

private:
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |2 <= nums[i] <= 1000|
// * |nums[i]| is a prime number.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,5,7]
// Output: [-1,1,4,3]
//

LEETCODE_SOLUTION_UNITTEST(3314, ConstructTheMinimumBitwiseArrayI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 5, 7};
  vector<int> expect   = {-1, 1, 4, 3};
  vector<int> actual   = solution->minBitwiseArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [11,13,31]
// Output: [9,12,15]
//

LEETCODE_SOLUTION_UNITTEST(3314, ConstructTheMinimumBitwiseArrayI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {11, 13, 31};
  vector<int> expect   = {9, 12, 15};
  vector<int> actual   = solution->minBitwiseArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
