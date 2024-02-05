// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Value of an Ordered Triplet I
//
// https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/
//
// Question ID: 2873
// Difficult  : Easy
// Solve Date : 2024/01/24 19:43

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2873. Maximum Value of an Ordered Triplet I|:
//
// You are given a 0-indexed integer array |nums|.
// Return the maximum value over all triplets of indices |(i, j, k)| such that
// |i < j < k|. If all such triplets have a negative value, return |0|. The
// value of a triplet of indices |(i, j, k)| is equal to |(nums[i] - nums[j]) *
// nums[k]|.
//
//

LEETCODE_BEGIN_RESOLVING(2873, MaximumValueOfAnOrderedTripletI, Solution);

class Solution {
public:
  long long maximumTripletValue(vector<int> &nums) {
    int64_t     res = 0;
    vector<int> L(nums.size());
    vector<int> R(nums.size());
    L[0] = nums[0];
    for (int i = 1; i < nums.size() - 1; ++i) {
      L[i] = max(L[i - 1], nums[i - 1]);
    }
    R.back() = nums.back();
    for (int i = nums.size() - 2; i >= 1; --i) {
      R[i] = max(R[i + 1], nums[i + 1]);
    }

    for (int i = 1; i < nums.size() - 1; ++i) {
      res = max<int64_t>(res, (int64_t)(L[i] - nums[i]) * R[i]);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 100|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [12,6,1,2,7]
// Output: 77
//
// The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
// It can be shown that there are no ordered triplets of indices with a value
// greater than 77.

LEETCODE_SOLUTION_UNITTEST(2873, MaximumValueOfAnOrderedTripletI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {12, 6, 1, 2, 7};
  long long   expect   = 77;
  long long   actual   = solution->maximumTripletValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,10,3,4,19]
// Output: 133
//
// The value of the triplet (1, 2, 4) is (nums[1] - nums[2]) * nums[4] = 133.
// It can be shown that there are no ordered triplets of indices with a value
// greater than 133.

LEETCODE_SOLUTION_UNITTEST(2873, MaximumValueOfAnOrderedTripletI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 10, 3, 4, 19};
  long long   expect   = 133;
  long long   actual   = solution->maximumTripletValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3]
// Output: 0
//
// The only ordered triplet of indices (0, 1, 2) has a negative value of
// (nums[0] - nums[1]) * nums[2] = -3. Hence, the answer would be 0.

LEETCODE_SOLUTION_UNITTEST(2873, MaximumValueOfAnOrderedTripletI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  long long   expect   = 0;
  long long   actual   = solution->maximumTripletValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [1000000,1,1000000]
// Output: 999999000000
//

LEETCODE_SOLUTION_UNITTEST(2873, MaximumValueOfAnOrderedTripletI,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1000000, 1, 1000000};
  long long   expect   = 999999000000;
  long long   actual   = solution->maximumTripletValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}
