// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Number of Operations to Make Elements in Array Distinct
//
// https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/
//
// Question ID: 3396
// Difficult  : Easy
// Solve Date : 2025/04/08 18:46

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3396. Minimum Number of Operations to Make Elements in Array
// Distinct|:
//
//

LEETCODE_BEGIN_RESOLVING(3396,
                         MinimumNumberOfOperationsToMakeElementsInArrayDistinct,
                         Solution);

class Solution {
public:
  int minimumOperations(vector<int> &nums) {
    vector<int> cnt(101);
    int         distinct_len = 0;
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
      if (++cnt[*it] > 1) {
        break;
      }
      ++distinct_len;
    }

    int res = nums.size() - distinct_len;
    return res / 3 + (res % 3 == 0 ? 0 : 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,2,3,3,5,7]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(
    3396, MinimumNumberOfOperationsToMakeElementsInArrayDistinct, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 2, 3, 3, 5, 7};
  int         expect   = 2;
  int         actual   = solution->minimumOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [6,7,8,9]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(
    3396, MinimumNumberOfOperationsToMakeElementsInArrayDistinct,
    extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 7, 8, 9};
  int         expect   = 0;
  int         actual   = solution->minimumOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}
