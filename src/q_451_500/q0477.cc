// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Total Hamming Distance
//
// https://leetcode.com/problems/total-hamming-distance/
//
// Question ID: 477
// Difficult  : Medium
// Solve Date : 2024/04/13 14:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |477. Total Hamming Distance|:
//
// The [Hamming distance] between two integers is the number of positions at
// which the corresponding bits are different. Given an integer array |nums|,
// return the sum of Hamming distances between all the pairs of the integers in
// |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(477, TotalHammingDistance, Solution);

class Solution {
public:
  int totalHammingDistance(vector<int> &nums) {
    int res = 0;
    for (int b = 0; b < 32; ++b) {
      int bit = 0;
      for (auto x : nums) {
        bit += (x >> b) & 1;
      }
      res += bit * (nums.size() - bit);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |0 <= nums[i] <= 10⁹|
// * The answer for the given input will fit in a 32-bit integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,14,2]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(477, TotalHammingDistance, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 14, 2};
  int         expect   = 6;
  int         actual   = solution->totalHammingDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,14,4]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(477, TotalHammingDistance, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 14, 4};
  int         expect   = 4;
  int         actual   = solution->totalHammingDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}
