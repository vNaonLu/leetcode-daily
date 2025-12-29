// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Smallest Subarrays With Maximum Bitwise OR
//
// https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/
//
// Question ID: 2411
// Difficult  : Medium
// Solve Date : 2025/07/29 20:46

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2411. Smallest Subarrays With Maximum Bitwise OR|:
//
// You are given a 0-indexed array |nums| of length |n|, consisting of
// non-negative integers. For each index |i| from |0| to |n - 1|, you must
// determine the size of the minimum sized non-empty subarray of |nums| starting
// at |i| (inclusive) that has the maximum possible bitwise OR.
//
//  • In other words, let |Bᵢⱼ| be the bitwise OR of the subarray |nums[i...j]|.
//  You need to find the smallest subarray starting at |i|, such that bitwise OR
//  of this subarray is equal to |max(Bᵢₖ)| where |i <= k <= n - 1|.
// The bitwise OR of an array is the bitwise OR of all the numbers in it.
// Return an integer array |answer| of size |n| where |answer[i]| is the length
// of the minimum sized subarray starting at |i| with maximum bitwise OR. A
// subarray is a contiguous non-empty sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2411, SmallestSubarraysWithMaximumBitwiseOR, Solution);

class Solution {
public:
  vector<int> smallestSubarrays(vector<int> &nums) {
    int         n = nums.size();
    vector<int> last_seen(30, 0);
    vector<int> res(n, 1);
    for (int i = n - 1; i >= 0; --i) {
      for (int bit = 0; bit < 30; ++bit) {
        if ((nums[i] & (1 << bit)) > 0) {
          last_seen[bit] = i;
        }
        res[i] = max(res[i], last_seen[bit] - i + 1);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 10⁵|
// * |0 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,0,2,1,3]
// Output: [3,3,2,2,1]
//

LEETCODE_SOLUTION_UNITTEST(2411, SmallestSubarraysWithMaximumBitwiseOR,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 0, 2, 1, 3};
  vector<int> expect   = {3, 3, 2, 2, 1};
  vector<int> actual   = solution->smallestSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2]
// Output: [2,1]
// Explanation:
// Starting at index 0, the shortest subarray that yields the maximum bitwise OR
// is of length 2. Starting at index 1, the shortest subarray that yields the
// maximum bitwise OR is of length 1. Therefore, we return [2,1].
//

LEETCODE_SOLUTION_UNITTEST(2411, SmallestSubarraysWithMaximumBitwiseOR,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  vector<int> expect   = {2, 1};
  vector<int> actual   = solution->smallestSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [4,0,5,6,3,2]
// Output: [4,3,2,2,1,1]
//

LEETCODE_SOLUTION_UNITTEST(2411, SmallestSubarraysWithMaximumBitwiseOR,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 0, 5, 6, 3, 2};
  vector<int> expect   = {4, 3, 2, 2, 1, 1};
  vector<int> actual   = solution->smallestSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}
