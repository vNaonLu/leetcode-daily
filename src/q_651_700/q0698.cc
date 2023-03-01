// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Partition to K Equal Sum Subsets
//
// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
//
// Question ID: 698
// Difficult  : Medium
// Solve Date : 2021/09/30 15:33

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |698. Partition to K Equal Sum Subsets|:
//
// Given an integer array |nums| and an integer |k|, return |true| if it is
// possible to divide this array into |k| non-empty subsets whose sums are all
// equal.  
//

LEETCODE_BEGIN_RESOLVING(698, PartitionToKEqualSumSubsets, Solution);

class Solution {
private:
  vector<bool> mask;
  int          target = 0;
  bool         DFS(const vector<int> &nums, int k, int sum = 0, int beg = 0) {
    if (k == 0)
      return true;
    if (sum > target) {
      return false;
    } else if (sum == target) {
      return DFS(nums, --k);
    }
    for (int i = beg; i < nums.size(); ++i) {
      if (!mask[i]) {
        mask[i] = true;
        if (DFS(nums, k, sum + nums[i], i + 1)) {
          return true;
        }
        mask[i] = false;
      }
    }
    return false;
  }

public:
  bool canPartitionKSubsets(vector<int> &nums, int k) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % k != 0)
      return false;
    target = total / k;
    sort(nums.begin(), nums.end());
    mask.resize(nums.size(), false);
    return DFS(nums, k);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= nums.length <= 16|
// * |1 <= nums[i] <= 10⁴|
// * The frequency of each element is in the range |[1, 4]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,3,2,3,5,2,1], k = 4
// Output: true
//
// It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with
// equal sums.

LEETCODE_SOLUTION_UNITTEST(698, PartitionToKEqualSumSubsets, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 2, 3, 5, 2, 1};
  int         k        = 4;
  bool        expect   = true;
  bool        actual   = solution->canPartitionKSubsets(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4], k = 3
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(698, PartitionToKEqualSumSubsets, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         k        = 3;
  bool        expect   = false;
  bool        actual   = solution->canPartitionKSubsets(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
