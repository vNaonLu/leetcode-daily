// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Number of Bad Pairs
//
// https://leetcode.com/problems/count-number-of-bad-pairs/
//
// Question ID: 2364
// Difficult  : Medium
// Solve Date : 2025/02/09 14:31

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2364. Count Number of Bad Pairs|:
//
// You are given a 0-indexed integer array |nums|. A pair of indices |(i, j)| is
// a bad pair if |i < j| and |j - i != nums[j] - nums[i]|. Return the total
// number of bad pairs in |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(2364, CountNumberOfBadPairs, Solution);

class Solution {
public:
  long long countBadPairs(vector<int> &nums) {
    int64_t                 res = 0;
    unordered_map<int, int> diff;
    for (int i = 0; i < nums.size(); ++i) {
      int d    = i - nums[i];
      int good = diff[d];
      res += i - good;
      diff[d] = good + 1;
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
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,1,3,3]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2364, CountNumberOfBadPairs, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 1, 3, 3};
  long long   expect   = 5;
  long long   actual   = solution->countBadPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2364, CountNumberOfBadPairs, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  long long   expect   = 0;
  long long   actual   = solution->countBadPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}
