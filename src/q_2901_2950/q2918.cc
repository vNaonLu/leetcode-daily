// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Equal Sum of Two Arrays After Replacing Zeros
//
// https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/
//
// Question ID: 2918
// Difficult  : Medium
// Solve Date : 2025/05/10 11:56

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2918. Minimum Equal Sum of Two Arrays After Replacing Zeros|:
//
// You are given two arrays |nums1| and |nums2| consisting of positive integers.
// You have to replace all the |0|'s in both arrays with strictly positive
// integers such that the sum of elements of both arrays becomes equal. Return
// the minimum equal sum you can obtain, or |-1| if it is impossible.
//
//

LEETCODE_BEGIN_RESOLVING(2918, MinimumEqualSumOfTwoArraysAfterReplacingZeros,
                         Solution);

class Solution {
public:
  long long minSum(vector<int> &nums1, vector<int> &nums2) {
    int64_t sum1  = 0;
    int64_t sum2  = 0;
    int     zero1 = 0;
    int     zero2 = 0;
    count(nums1.begin(), nums1.end(), &sum1, &zero1);
    count(nums2.begin(), nums2.end(), &sum2, &zero2);
    if (zero1 == 0 && zero2 == 0) {
      return sum1 == sum2 ? sum1 : -1;
    } else if (zero1 == 0) {
      return sum2 + zero2 <= sum1 ? sum1 : -1;
    } else if (zero2 == 0) {
      return sum1 + zero1 <= sum2 ? sum2 : -1;
    }
    return max(sum1 + zero1, sum2 + zero2);
  }

private:
  void count(auto beg, auto end, int64_t *sum, int *zeros) {
    while (beg != end) {
      if (*beg == 0) {
        ++*zeros;
      }
      *sum += *beg++;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 10⁵|
// * |0 <= nums1[i], nums2[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(2918, MinimumEqualSumOfTwoArraysAfterReplacingZeros,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {3, 2, 0, 1, 0};
  vector<int> nums2    = {6, 5, 0};
  long long   expect   = 12;
  long long   actual   = solution->minSum(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [2,0,2,0], nums2 = [1,4]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2918, MinimumEqualSumOfTwoArraysAfterReplacingZeros,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 0, 2, 0};
  vector<int> nums2    = {1, 4};
  long long   expect   = -1;
  long long   actual   = solution->minSum(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}
