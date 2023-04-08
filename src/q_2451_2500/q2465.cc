// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Distinct Averages
//
// https://leetcode.com/problems/number-of-distinct-averages/
//
// Question ID: 2465
// Difficult  : Easy
// Solve Date : 2023/04/08 10:01

#include <algorithm>
#include <iosfwd>
#include <list>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2465. Number of Distinct Averages|:
//
// You are given a 0-indexed integer array |nums| of even length.
// As long as |nums| is not empty, you must repetitively:
//
//  • Find the minimum number in |nums| and remove it.
//
//  • Find the maximum number in |nums| and remove it.
//
//  • Calculate the average of the two removed numbers.
// The average of two numbers |a| and |b| is |(a + b) / 2|.
//
//  • For example, the average of |2| and |3| is |(2 + 3) / 2 = 2.5|.
// Return the number of distinct averages calculated using the above process.
// Note that when there is a tie for a minimum or maximum number, any can be
// removed.
//
//

LEETCODE_BEGIN_RESOLVING(2465, NumberOfDistinctAverages, Solution);

class Solution {
public:
  int distinctAverages(vector<int> &nums) {
    int                res = 0;
    list<int>          nums_list(nums.begin(), nums.end());
    unordered_set<int> memo;
    nums_list.sort();
    while (!nums_list.empty()) {
      if (memo.emplace(nums_list.front() + nums_list.back()).second) {
        ++res;
      }
      nums_list.pop_front();
      nums_list.pop_back();
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 100|
// * |nums.length| is even.
// * |0 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,1,4,0,3,5]
// Output: 2
//
// 1. Remove 0 and 5, and the average is (0 + 5) / 2 = 2.5. Now, nums =
// [4,1,4,3].
// 2. Remove 1 and 4. The average is (1 + 4) / 2 = 2.5, and nums = [4,3].
// 3. Remove 3 and 4, and the average is (3 + 4) / 2 = 3.5.
// Since there are 2 distinct numbers among 2.5, 2.5, and 3.5, we return 2.

LEETCODE_SOLUTION_UNITTEST(2465, NumberOfDistinctAverages, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 1, 4, 0, 3, 5};
  int         expect   = 2;
  int         actual   = solution->distinctAverages(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,100]
// Output: 1
//
// There is only one average to be calculated after removing 1 and 100, so we
// return 1.

LEETCODE_SOLUTION_UNITTEST(2465, NumberOfDistinctAverages, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 100};
  int         expect   = 1;
  int         actual   = solution->distinctAverages(nums);
  LCD_EXPECT_EQ(expect, actual);
}
