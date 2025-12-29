// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Number of Distinct Elements After Operations
//
// https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/
//
// Question ID: 3397
// Difficult  : Medium
// Solve Date : 2025/10/18 22:34

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3397. Maximum Number of Distinct Elements After Operations|:
//
// You are given an integer array |nums| and an integer |k|.
// You are allowed to perform the following operation on each element of the
// array at most once:
//
//  • Add an integer in the range |[-k, k]| to the element.
// Return the maximum possible number of distinct elements in |nums| after
// performing the operations.
//
//

LEETCODE_BEGIN_RESOLVING(3397, MaximumNumberOfDistinctElementsAfterOperations,
                         Solution);

class Solution {
public:
  int maxDistinctElements(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int res  = 0;
    int prev = numeric_limits<int>::min();
    for (int i = 0; i < nums.size(); ++i) {
      int l = max(nums[i] - k, prev + 1);
      if (l <= nums[i] + k) {
        prev = l;
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
// * |1 <= nums[i] <= 10⁹|
// * |0 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2,3,3,4], k = 2
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3397, MaximumNumberOfDistinctElementsAfterOperations,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 3, 3, 4};
  int         k        = 2;
  int         expect   = 6;
  int         actual   = solution->maxDistinctElements(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,4,4,4], k = 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3397, MaximumNumberOfDistinctElementsAfterOperations,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 4, 4, 4};
  int         k        = 1;
  int         expect   = 3;
  int         actual   = solution->maxDistinctElements(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
