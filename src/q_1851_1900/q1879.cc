// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum XOR Sum of Two Arrays
//
// https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/
//
// Question ID: 1879
// Difficult  : Hard
// Solve Date : 2022/02/14 18:15

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1879. Minimum XOR Sum of Two Arrays|:
//
// You are given two integer arrays |nums1| and |nums2| of length |n|.
// The XOR sum of the two integer arrays is |(nums1[0] XOR nums2[0]) + (nums1[1]
// XOR nums2[1]) + ... + (nums1[n - 1] XOR nums2[n - 1])| (0-indexed).
//
//  • For example, the XOR sum of |[1,2,3]| and |[3,2,1]| is equal to |(1 XOR 3)
//  + (2 XOR 2) + (3 XOR 1) = 2 + 0 + 2 = 4|.
// Rearrange the elements of |nums2| such that the resulting XOR sum is
// minimized. Return the XOR sum after the rearrangement.  
//

LEETCODE_BEGIN_RESOLVING(1879, MinimumXORSumOfTwoArrays, Solution);

class Solution {
private:
  vector<int>         n1, n2;
  vector<vector<int>> memos;
  int                 helper(int i, int v) {
    if (i == n1.size())
      return 0;
    if (memos[i][v] != -1)
      return memos[i][v];
    int res = numeric_limits<int>::max();
    for (int j = 0; j < n2.size(); ++j) {
      if (!(v & (1 << j))) {
        auto nv = v | (1 << j);
        res     = min(res, helper(i + 1, nv) + (n1[i] ^ n2[j]));
      }
    }
    return memos[i][v] = res;
  }

public:
  int minimumXORSum(vector<int> &nums1, vector<int> &nums2) {
    n1 = nums1;
    n2 = nums2;
    memos.resize(n1.size(), vector<int>(1 << 15, -1));
    return helper(0, 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums1.length|
// * |n == nums2.length|
// * |1 <= n <= 14|
// * |0 <= nums1[i], nums2[i] <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,2], nums2 = [2,3]
// Output: 2
// Explanation: Rearrange |nums2| so that it becomes |[3,2]|.
// The XOR sum is (1 XOR 3) + (2 XOR 2) = 2 + 0 = 2.
//

LEETCODE_SOLUTION_UNITTEST(1879, MinimumXORSumOfTwoArrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2};
  vector<int> nums2    = {2, 3};
  int         expect   = 2;
  int         actual   = solution->minimumXORSum(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [1,0,3], nums2 = [5,3,4]
// Output: 8
// Explanation: Rearrange |nums2| so that it becomes |[5,4,3]|.
// The XOR sum is (1 XOR 5) + (0 XOR 4) + (3 XOR 3) = 4 + 4 + 0 = 8.
//

LEETCODE_SOLUTION_UNITTEST(1879, MinimumXORSumOfTwoArrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 0, 3};
  vector<int> nums2    = {5, 3, 4};
  int         expect   = 8;
  int         actual   = solution->minimumXORSum(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}
