// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Score of an Array After Marking All Elements
//
// https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/
//
// Question ID: 2593
// Difficult  : Medium
// Solve Date : 2024/12/13 22:42

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2593. Find Score of an Array After Marking All Elements|:
//
// You are given an array |nums| consisting of positive integers.
// Starting with |score = 0|, apply the following algorithm:
//
//  • Choose the smallest integer of the array that is not marked. If there is a
//  tie, choose the one with the smallest index.
//
//  • Add the value of the chosen integer to |score|.
//
//  • Mark the chosen element and its two adjacent elements if they exist.
//
//  • Repeat until all the array elements are marked.
// Return the score you get after applying the above algorithm.
//
//

LEETCODE_BEGIN_RESOLVING(2593, FindScoreOfAnArrayAfterMarkingAllElements,
                         Solution);

class Solution {
public:
  long long findScore(vector<int> &nums) {
    int         n = nums.size();
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
      return nums[a] != nums[b] ? nums[a] < nums[b] : a < b;
    });

    vector<bool> m(n, false);
    int64_t      res = 0;
    for (int x : ord) {
      if (m[x]) {
        continue;
      }
      res += nums[x];
      m[x] = true;

      if (x > 0) {
        m[x - 1] = true;
      }

      if (x + 1 < n) {
        m[x + 1] = true;
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
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,3,4,5,2]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(2593, FindScoreOfAnArrayAfterMarkingAllElements,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3, 4, 5, 2};
  long long   expect   = 7;
  long long   actual   = solution->findScore(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,5,1,3,2]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2593, FindScoreOfAnArrayAfterMarkingAllElements,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 5, 1, 3, 2};
  long long   expect   = 5;
  long long   actual   = solution->findScore(nums);
  LCD_EXPECT_EQ(expect, actual);
}
