// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Ways to Reorder Array to Get Same BST
//
// https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/
//
// Question ID: 1569
// Difficult  : Hard
// Solve Date : 2023/06/16 10:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1569. Number of Ways to Reorder Array to Get Same BST|:
//
// Given an array |nums| that represents a permutation of integers from |1| to
// |n|. We are going to construct a binary search tree (BST) by inserting the
// elements of |nums| in order into an initially empty BST. Find the number of
// different ways to reorder |nums| so that the constructed BST is identical to
// that formed from the original array |nums|.
//
//  • For example, given |nums = [2,1,3]|, we will have 2 as the root, 1 as a
//  left child, and 3 as a right child. The array |[2,3,1]| also yields the same
//  BST but |[3,2,1]| yields a different BST.
// Return the number of ways to reorder |nums| such that the BST formed is
// identical to the original BST formed from |nums|. Since the answer may be
// very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1569, NumberOfWaysToReorderArrayToGetSameBST,
                         Solution);

class Solution {
public:
  int numOfWays(vector<int> &nums) { return (dfs(nums) - 1 + kMod) % kMod; }

private:
  constexpr static int kMod = 1e9 + 7;
  int64_t              combine(int k, int n) {
    if (k > n - k) {
      k = n - k;
    }
    vector<int> dp(k + 1, 0);
    dp.front() = 1;
    for (int i = 1; i <= n; ++i) {
      for (int j = min(i, k); j > 0; --j) {
        dp[j] = (dp[j] + dp[j - 1]) % kMod;
      }
    }
    return dp[k];
  }
  int64_t dfs(vector<int> &nums) {
    if (nums.size() <= 1) {
      return 1;
    }
    int         root = nums.front();
    vector<int> left;
    vector<int> right;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] < root)
        left.emplace_back(nums[i]);
      else
        right.emplace_back(nums[i]);
    }
    return combine(left.size(), nums.size() - 1) * dfs(left) % kMod *
           dfs(right) % kMod;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= nums.length|
// * All integers in |nums| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,3]
// Output: 1
//
// We can reorder nums to be [2,3,1] which will yield the same BST. There are no
// other ways to reorder nums which will yield the same BST.

LEETCODE_SOLUTION_UNITTEST(1569, NumberOfWaysToReorderArrayToGetSameBST,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3};
  int         expect   = 1;
  int         actual   = solution->numOfWays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,4,5,1,2]
// Output: 5
//
// The following 5 arrays will yield the same BST:
// [3,1,2,4,5]
// [3,1,4,2,5]
// [3,1,4,5,2]
// [3,4,1,2,5]
// [3,4,1,5,2]

LEETCODE_SOLUTION_UNITTEST(1569, NumberOfWaysToReorderArrayToGetSameBST,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 5, 1, 2};
  int         expect   = 5;
  int         actual   = solution->numOfWays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3]
// Output: 0
//
// There are no other orderings of nums that will yield the same BST.

LEETCODE_SOLUTION_UNITTEST(1569, NumberOfWaysToReorderArrayToGetSameBST,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = 0;
  int         actual   = solution->numOfWays(nums);
  LCD_EXPECT_EQ(expect, actual);
}
