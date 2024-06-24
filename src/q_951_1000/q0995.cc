// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of K Consecutive Bit Flips
//
// https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/
//
// Question ID: 995
// Difficult  : Hard
// Solve Date : 2024/06/24 20:13

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |995. Minimum Number of K Consecutive Bit Flips|:
//
// You are given a binary array |nums| and an integer |k|.
// A k-bit flip is choosing a subarray of length |k| from |nums| and
// simultaneously changing every |0| in the subarray to |1|, and every |1| in
// the subarray to |0|. Return the minimum number of k-bit flips required so
// that there is no |0| in the array. If it is not possible, return |-1|. A
// subarray is a contiguous part of an array.
//
//

LEETCODE_BEGIN_RESOLVING(995, MinimumNumberOfKConsecutiveBitFlips, Solution);

class Solution {
public:
  int minKBitFlips(vector<int> &nums, int k) {
    int         n       = nums.size();
    int         flipped = 0;
    int         res     = 0;
    vector<int> isFlipped(n, 0);
    for (int i = 0; i < n; ++i) {
      if (i >= k) {
        flipped ^= isFlipped[i - k];
      }
      if (flipped == nums[i]) {
        if (i + k > n) {
          return -1;
        }
        isFlipped[i] = 1;
        flipped ^= 1;
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,0], k = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(995, MinimumNumberOfKConsecutiveBitFlips,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 0};
  int         k        = 1;
  int         expect   = 2;
  int         actual   = solution->minKBitFlips(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,0], k = 2
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(995, MinimumNumberOfKConsecutiveBitFlips,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 0};
  int         k        = 2;
  int         expect   = -1;
  int         actual   = solution->minKBitFlips(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [0,0,0,1,0,1,1,0], k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(995, MinimumNumberOfKConsecutiveBitFlips,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 0, 0, 1, 0, 1, 1, 0};
  int         k        = 3;
  int         expect   = 3;
  int         actual   = solution->minKBitFlips(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
