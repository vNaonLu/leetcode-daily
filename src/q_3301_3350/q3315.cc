// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Construct the Minimum Bitwise Array II
//
// https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/
//
// Question ID: 3315
// Difficult  : Medium
// Solve Date : 2026/01/21 21:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3315. Construct the Minimum Bitwise Array II|:
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

LEETCODE_BEGIN_RESOLVING(3315, ConstructTheMinimumBitwiseArrayII, Solution);

class Solution {
public:
  vector<int> minBitwiseArray(vector<int> &nums) {
    vector<int> res;
    for (auto x : nums) {
      if (x & 1) {
        res.emplace_back(x - (((x + 1) & (-x - 1)) >> 1));
      } else {
        res.emplace_back(-1);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |2 <= nums[i] <= 10⁹|
// * |nums[i]| is a prime number.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,5,7]
// Output: [-1,1,4,3]
//

LEETCODE_SOLUTION_UNITTEST(3315, ConstructTheMinimumBitwiseArrayII, example_1) {
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

LEETCODE_SOLUTION_UNITTEST(3315, ConstructTheMinimumBitwiseArrayII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {11, 13, 31};
  vector<int> expect   = {9, 12, 15};
  vector<int> actual   = solution->minBitwiseArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
