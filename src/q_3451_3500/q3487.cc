// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Unique Subarray Sum After Deletion
//
// https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/
//
// Question ID: 3487
// Difficult  : Easy
// Solve Date : 2025/07/25 19:00

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3487. Maximum Unique Subarray Sum After Deletion|:
//
//

LEETCODE_BEGIN_RESOLVING(3487, MaximumUniqueSubarraySumAfterDeletion, Solution);

class Solution {
public:
  int maxSum(vector<int> &nums) {
    int          res = 0;
    vector<bool> seen(101, 0);
    sort(nums.begin(), nums.end());

    if (nums.back() <= 0) {
      return nums.back();
    }

    auto beg = upper_bound(nums.begin(), nums.end(), 0);
    while (beg != nums.end()) {
      if (!seen[*beg]) {
        res += *beg;
      }

      seen[*beg++] = true;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5]
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(3487, MaximumUniqueSubarraySumAfterDeletion,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         expect   = 15;
  int         actual   = solution->maxSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [-100]
// Output: -100
//

LEETCODE_SOLUTION_UNITTEST(3487, MaximumUniqueSubarraySumAfterDeletion,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-100};
  int         expect   = -100;
  int         actual   = solution->maxSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}
