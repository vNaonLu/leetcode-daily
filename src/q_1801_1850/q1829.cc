// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum XOR for Each Query
//
// https://leetcode.com/problems/maximum-xor-for-each-query/
//
// Question ID: 1829
// Difficult  : Medium
// Solve Date : 2022/03/30 18:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1829. Maximum XOR for Each Query|:
//
// You are given a sorted array |nums| of |n| non-negative integers and an
// integer |maximumBit|. You want to perform the following query |n| times:
//
//  1. Find a non-negative integer |k < 2^{maximumBit}| such that |nums[0] XOR
//  nums[1] XOR ... XOR nums[nums.length-1] XOR k| is maximized. |k| is the
//  answer to the |iᵗʰ| query.
//
//  2. Remove the last element from the current array |nums|.
// Return an array |answer|, where |answer[i]| is the answer to the |iᵗʰ| query.
//  
//

LEETCODE_BEGIN_RESOLVING(1829, MaximumXORForEachQuery, Solution);

class Solution {
public:
  vector<int> getMaximumXor(vector<int> &nums, int maximumBit) {
    int         n    = nums.size();
    int         mask = (1 << maximumBit) - 1;
    vector<int> res(nums.size(), 0);
    res.back() = nums.front();
    for (int i = 1; i < n; ++i) {
      res[n - i - 1] = res[n - i] ^ nums[i];
    }

    for (auto it = res.begin(); it != res.end(); ++it) {
      *it ^= mask;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |nums.length == n|
// * |1 <= n <= 10⁵|
// * |1 <= maximumBit <= 20|
// * |0 <= nums[i] < 2^{maximumBit}|
// * |nums|​​​ is sorted in ascending order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,1,3], maximumBit = 2
// Output: [0,3,2,3]
//
// : The queries are answered as follows:
// 1ˢᵗ query: nums = [0,1,1,3], k = 0 since 0 XOR 1 XOR 1 XOR 3 XOR 0 = 3.
// 2ⁿᵈ query: nums = [0,1,1], k = 3 since 0 XOR 1 XOR 1 XOR 3 = 3.
// 3ʳᵈ query: nums = [0,1], k = 2 since 0 XOR 1 XOR 2 = 3.
// 4ᵗʰ query: nums = [0], k = 3 since 0 XOR 3 = 3.

LEETCODE_SOLUTION_UNITTEST(1829, MaximumXORForEachQuery, example_1) {
  auto        solution   = MakeSolution();
  vector<int> nums       = {0, 1, 1, 3};
  int         maximumBit = 2;
  vector<int> expect     = {0, 3, 2, 3};
  vector<int> actual     = solution->getMaximumXor(nums, maximumBit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,4,7], maximumBit = 3
// Output: [5,2,6,5]
//
// : The queries are answered as follows:
// 1ˢᵗ query: nums = [2,3,4,7], k = 5 since 2 XOR 3 XOR 4 XOR 7 XOR 5 = 7.
// 2ⁿᵈ query: nums = [2,3,4], k = 2 since 2 XOR 3 XOR 4 XOR 2 = 7.
// 3ʳᵈ query: nums = [2,3], k = 6 since 2 XOR 3 XOR 6 = 7.
// 4ᵗʰ query: nums = [2], k = 5 since 2 XOR 5 = 7.

LEETCODE_SOLUTION_UNITTEST(1829, MaximumXORForEachQuery, example_2) {
  auto        solution   = MakeSolution();
  vector<int> nums       = {2, 3, 4, 7};
  int         maximumBit = 3;
  vector<int> expect     = {5, 2, 6, 5};
  vector<int> actual     = solution->getMaximumXor(nums, maximumBit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [0,1,2,2,5,7], maximumBit = 3
// Output: [4,3,6,4,6,7]
//

LEETCODE_SOLUTION_UNITTEST(1829, MaximumXORForEachQuery, example_3) {
  auto        solution   = MakeSolution();
  vector<int> nums       = {0, 1, 2, 2, 5, 7};
  int         maximumBit = 3;
  vector<int> expect     = {4, 3, 6, 4, 6, 7};
  vector<int> actual     = solution->getMaximumXor(nums, maximumBit);
  LCD_EXPECT_EQ(expect, actual);
}
