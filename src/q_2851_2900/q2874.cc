// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Value of an Ordered Triplet II
//
// https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/
//
// Question ID: 2874
// Difficult  : Medium
// Solve Date : 2025/04/03 14:38

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2874. Maximum Value of an Ordered Triplet II|:
//
// You are given a 0-indexed integer array |nums|.
// Return the maximum value over all triplets of indices |(i, j, k)| such that
// |i < j < k|. If all such triplets have a negative value, return |0|. The
// value of a triplet of indices |(i, j, k)| is equal to |(nums[i] - nums[j]) *
// nums[k]|.
//
//

LEETCODE_BEGIN_RESOLVING(2874, MaximumValueOfAnOrderedTripletII, Solution);

class Solution {
public:
  long long maximumTripletValue(vector<int> &nums) {
    int64_t res  = 0;
    int     mx   = numeric_limits<int>::min();
    int     diff = 0;
    int     n    = nums.size();
    for (int i = 0; i < n; ++i) {
      mx = max(mx, nums[i]);
      if (i >= 2) {
        res = max<int64_t>(res, 1ll * diff * nums[i]);
      }
      if (i >= 1) {
        diff = max(diff, mx - nums[i]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [12,6,1,2,7]
// Output: 77
//

LEETCODE_SOLUTION_UNITTEST(2874, MaximumValueOfAnOrderedTripletII, example_1) {
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

LEETCODE_SOLUTION_UNITTEST(2874, MaximumValueOfAnOrderedTripletII, example_2) {
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

LEETCODE_SOLUTION_UNITTEST(2874, MaximumValueOfAnOrderedTripletII, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  long long   expect   = 0;
  long long   actual   = solution->maximumTripletValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}
