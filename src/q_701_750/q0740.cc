// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Delete and Earn
//
// https://leetcode.com/problems/delete-and-earn/
//
// Question ID: 740
// Difficult  : Medium
// Solve Date : 2021/10/12 11:52

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |740. Delete and Earn|:
//
// You are given an integer array |nums|. You want to maximize the number of
// points you get by performing the following operation any number of times:
//
//  • Pick any |nums[i]| and delete it to earn |nums[i]| points. Afterwards, you
//  must delete every element equal to |nums[i] - 1| and every element equal to
//  |nums[i] + 1|.
// Return the maximum number of points you can earn by applying the above
// operation some number of times.  
//

LEETCODE_BEGIN_RESOLVING(740, DeleteAndEarn, Solution);

class Solution {
public:
  int deleteAndEarn(vector<int> &nums) {
    map<int, int> freq;
    for (const auto &x : nums)
      ++freq[x];
    int  res   = 0;
    int  avoid = 0, prev = 0;
    auto beg = freq.begin();
    while (beg != freq.end()) {
      int earn = prev == beg->first - 1
                     ? avoid + beg->first * beg->second
                     : max(avoid, res) + beg->first * beg->second;
      avoid    = res;
      res      = max(res, earn);
      prev     = (beg++)->first;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁴|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,4,2]
// Output: 6
//
// You can perform the following operations:
// - Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
// - Delete 2 to earn 2 points. nums = [].
// You earn a total of 6 points.

LEETCODE_SOLUTION_UNITTEST(740, DeleteAndEarn, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 2};
  int         expect   = 6;
  int         actual   = solution->deleteAndEarn(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,3,3,3,4]
// Output: 9
//
// You can perform the following operations:
// - Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums =
// [3,3].
// - Delete a 3 again to earn 3 points. nums = [3].
// - Delete a 3 once more to earn 3 points. nums = [].
// You earn a total of 9 points.

LEETCODE_SOLUTION_UNITTEST(740, DeleteAndEarn, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 3, 3, 3, 4};
  int         expect   = 9;
  int         actual   = solution->deleteAndEarn(nums);
  LCD_EXPECT_EQ(expect, actual);
}
