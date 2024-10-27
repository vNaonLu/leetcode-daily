// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximal Score After Applying K Operations
//
// https://leetcode.com/problems/maximal-score-after-applying-k-operations/
//
// Question ID: 2530
// Difficult  : Medium
// Solve Date : 2024/10/14 19:12

#include <cmath>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2530. Maximal Score After Applying K Operations|:
//
// You are given a 0-indexed integer array |nums| and an integer |k|. You have a
// starting score of |0|. In one operation:
//
//  1. choose an index |i| such that |0 <= i < nums.length|,
//
//  2. increase your score by |nums[i]|, and
//
//  3. replace |nums[i]| with |ceil(nums[i] / 3)|.
// Return the maximum possible score you can attain after applying exactly |k|
// operations. The ceiling function |ceil(val)| is the least integer greater
// than or equal to |val|.
//
//

LEETCODE_BEGIN_RESOLVING(2530, MaximalScoreAfterApplyingKOperations, Solution);

class Solution {
public:
  long long maxKelements(vector<int> &nums, int k) {
    int64_t             res = 0;
    priority_queue<int> pq(nums.begin(), nums.end());
    while (k-- > 0) {
      auto x = pq.top();
      pq.pop();
      pq.emplace(ceil(x / 3.0));
      res += x;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length, k <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,10,10,10,10], k = 5
// Output: 50
//

LEETCODE_SOLUTION_UNITTEST(2530, MaximalScoreAfterApplyingKOperations,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 10, 10, 10, 10};
  int         k        = 5;
  long long   expect   = 50;
  long long   actual   = solution->maxKelements(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,10,3,3,3], k = 3
// Output: 17
//

LEETCODE_SOLUTION_UNITTEST(2530, MaximalScoreAfterApplyingKOperations,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 10, 3, 3, 3};
  int         k        = 3;
  long long   expect   = 17;
  long long   actual   = solution->maxKelements(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
