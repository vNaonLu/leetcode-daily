// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Number of Good Pairs I
//
// https://leetcode.com/problems/find-the-number-of-good-pairs-i/
//
// Question ID: 3162
// Difficult  : Easy
// Solve Date : 2024/05/31 22:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3162. Find the Number of Good Pairs I|:
//
// You are given 2 integer arrays |nums1| and |nums2| of lengths |n| and |m|
// respectively. You are also given a positive integer |k|. A pair |(i, j)| is
// called good if |nums1[i]| is divisible by |nums2[j] * k| ( |0 <= i <= n - 1|,
// |0 <= j <= m - 1|). Return the total number of good pairs.
//
//

LEETCODE_BEGIN_RESOLVING(3162, FindTheNumberOfGoodPairsI, Solution);

class Solution {
public:
  int numberOfPairs(vector<int> &nums1, vector<int> &nums2, int k) {
    int res = 0;
    for (auto x : nums1) {
      for (auto y : nums2) {
        if ((x % (y * k)) == 0) {
          ++res;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n, m <= 50|
// * |1 <= nums1[i], nums2[j] <= 50|
// * |1 <= k <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,3,4], nums2 = [1,3,4], k = 1
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3162, FindTheNumberOfGoodPairsI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 3, 4};
  vector<int> nums2    = {1, 3, 4};
  int         k        = 1;
  int         expect   = 5;
  int         actual   = solution->numberOfPairs(nums1, nums2, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [1,2,4,12], nums2 = [2,4], k = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3162, FindTheNumberOfGoodPairsI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2, 4, 12};
  vector<int> nums2    = {2, 4};
  int         k        = 3;
  int         expect   = 2;
  int         actual   = solution->numberOfPairs(nums1, nums2, k);
  LCD_EXPECT_EQ(expect, actual);
}
