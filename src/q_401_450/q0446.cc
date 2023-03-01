// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Arithmetic Slices II - Subsequence
//
// https://leetcode.com/problems/arithmetic-slices-ii-subsequence/
//
// Question ID: 446
// Difficult  : Hard
// Solve Date : 2021/09/10 08:00

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |446. Arithmetic Slices II - Subsequence|:
//
// Given an integer array |nums|, return the number of all the arithmetic
// subsequences of |nums|. A sequence of numbers is called arithmetic if it
// consists of at least three elements and if the difference between any two
// consecutive elements is the same.
//
//  • For example, |[1, 3, 5, 7, 9]|, |[7, 7, 7, 7]|, and |[3, -1, -5, -9]| are
//  arithmetic sequences.
//
//  • For example, |[1, 1, 2, 5, 7]| is not an arithmetic sequence.
// A subsequence of an array is a sequence that can be formed by removing some
// elements (possibly none) of the array.
//
//  • For example, |[2,5,10]| is a subsequence of |[1,2,1,2,4,1,5,10]|.
// The test cases are generated so that the answer fits in 32-bit integer.
//  
//

LEETCODE_BEGIN_RESOLVING(446, ArithmeticSlicesIISubequence, Solution);

class Solution {
public:
  int numberOfArithmeticSlices(vector<int> &nums) {
    int                         n   = nums.size();
    long long                   res = 0;
    vector<map<long long, int>> cnt(n);
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        long long d   = (long long)nums[i] - (long long)nums[j];
        int       sum = 0;
        if (cnt[j].find(d) != cnt[j].end()) {
          sum = cnt[j][d];
        }
        cnt[i][d] += sum + 1;
        res += sum;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1  <= nums.length <= 1000|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,4,6,8,10]
// Output: 7
//
// All arithmetic subsequence slices are:
// [2,4,6]
// [4,6,8]
// [6,8,10]
// [2,4,6,8]
// [4,6,8,10]
// [2,4,6,8,10]
// [2,6,10]

LEETCODE_SOLUTION_UNITTEST(446, ArithmeticSlicesIISubequence, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 4, 6, 8, 10};
  int         expect   = 7;
  int         actual   = solution->numberOfArithmeticSlices(nums);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [7,7,7,7,7]
// Output: 16
//
// Any subsequence of this array is arithmetic.

LEETCODE_SOLUTION_UNITTEST(446, ArithmeticSlicesIISubequence, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 7, 7, 7, 7};
  int         expect   = 16;
  int         actual   = solution->numberOfArithmeticSlices(nums);
  EXPECT_EQ(expect, actual);
}
