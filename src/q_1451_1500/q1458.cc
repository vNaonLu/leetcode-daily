// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Max Dot Product of Two Subsequences
//
// https://leetcode.com/problems/max-dot-product-of-two-subsequences/
//
// Question ID: 1458
// Difficult  : Hard
// Solve Date : 2023/10/08 12:31

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1458. Max Dot Product of Two Subsequences|:
//
// Given two arrays |nums1| and |nums2|.
// Return the maximum dot product between non-empty subsequences of nums1 and
// nums2 with the same length. A subsequence of a array is a new array which is
// formed from the original array by deleting some (can be none) of the
// characters without disturbing the relative positions of the remaining
// characters. (ie, |[2,3,5]| is a subsequence of |[1,2,3,4,5]| while |[1,5,3]|
// is not).
//
//

LEETCODE_BEGIN_RESOLVING(1458, MaxDotProductOfTwoSubsequences, Solution);

class Solution {
public:
  int maxDotProduct(vector<int> &nums1, vector<int> &nums2) {
    int         m = nums1.size();
    int         n = nums2.size();
    vector<int> curr(n + 1, numeric_limits<int>::min());
    vector<int> prev(n + 1, numeric_limits<int>::min());
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        int p   = nums1[i - 1] * nums2[j - 1];
        curr[j] = max({p, prev[j], curr[j - 1], p + max(0, prev[j - 1])});
      }
      swap(curr, prev);
    }
    return prev[n];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 500|
// * |-1000 <= nums1[i], nums2[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
// Output: 18
//
// Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
// Their dot product is (2*3 + (-2)*(-6)) = 18.

LEETCODE_SOLUTION_UNITTEST(1458, MaxDotProductOfTwoSubsequences, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 1, -2, 5};
  vector<int> nums2    = {3, 0, -6};
  int         expect   = 18;
  int         actual   = solution->maxDotProduct(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [3,-2], nums2 = [2,-6,7]
// Output: 21
//
// Take subsequence [3] from nums1 and subsequence [7] from nums2.
// Their dot product is (3*7) = 21.

LEETCODE_SOLUTION_UNITTEST(1458, MaxDotProductOfTwoSubsequences, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {3, -2};
  vector<int> nums2    = {2, -6, 7};
  int         expect   = 21;
  int         actual   = solution->maxDotProduct(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums1 = [-1,-1], nums2 = [1,1]
// Output: -1
//
// Take subsequence [-1] from nums1 and subsequence [1] from nums2.
// Their dot product is -1.

LEETCODE_SOLUTION_UNITTEST(1458, MaxDotProductOfTwoSubsequences, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {-1, -1};
  vector<int> nums2    = {1, 1};
  int         expect   = -1;
  int         actual   = solution->maxDotProduct(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}
