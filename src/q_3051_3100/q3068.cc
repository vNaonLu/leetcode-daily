// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Maximum Sum of Node Values
//
// https://leetcode.com/problems/find-the-maximum-sum-of-node-values/
//
// Question ID: 3068
// Difficult  : Hard
// Solve Date : 2024/05/19 15:27

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3068. Find the Maximum Sum of Node Values|:
//
// There exists an undirected tree with |n| nodes numbered |0| to |n - 1|. You
// are given a 0-indexed 2D integer array |edges| of length |n - 1|, where
// |edges[i] = [uᵢ, vᵢ]| indicates that there is an edge between nodes |uᵢ| and
// |vᵢ| in the tree. You are also given a positive integer |k|, and a 0-indexed
// array of non-negative integers |nums| of length |n|, where |nums[i]|
// represents the value of the node numbered |i|. Alice wants the sum of values
// of tree nodes to be maximum, for which Alice can perform the following
// operation any number of times (including zero) on the tree:
//
//  • Choose any edge |[u, v]| connecting the nodes |u| and |v|, and update
//  their values as follows:
//
//
//    • |nums[u] = nums[u] XOR k|
//
//    • |nums[v] = nums[v] XOR k|
//
//
// Return the maximum possible sum of the values Alice can achieve by performing
// the operation any number of times.
//
//

LEETCODE_BEGIN_RESOLVING(3068, FindTheMaximumSumOfNodeValues, Solution);

class Solution {
public:
  long long maximumValueSum(vector<int> &nums, int k,
                            vector<vector<int>> &edges) {
    int         n = nums.size();
    vector<int> diff(n);
    uint64_t    res = 0;
    for (int i = 0; i < n; ++i) {
      diff[i] = (nums[i] ^ k) - nums[i];
      res += nums[i];
    }
    sort(diff.rbegin(), diff.rend());
    for (int i = 0; i < n; i += 2) {
      if (i + 1 == n) {
        return res;
      }

      int pair = diff[i] + diff[i + 1];
      if (pair > 0) {
        res += pair;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n == nums.length <= 2 * 10⁴|
// * |1 <= k <= 10⁹|
// * |0 <= nums[i] <= 10⁹|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= edges[i][0], edges[i][1] <= n - 1|
// * The input is generated such that |edges| represent a valid tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1], k = 3, edges = [[0,1],[0,2]]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3068, FindTheMaximumSumOfNodeValues, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 2, 1};
  int                 k        = 3;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2}
  };
  long long expect = 6;
  long long actual = solution->maximumValueSum(nums, k, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3], k = 7, edges = [[0,1]]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(3068, FindTheMaximumSumOfNodeValues, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {2, 3};
  int                 k        = 7;
  vector<vector<int>> edges    = {
      {0, 1}
  };
  long long expect = 9;
  long long actual = solution->maximumValueSum(nums, k, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [7,7,7,7,7,7], k = 3, edges = [[0,1],[0,2],[0,3],[0,4],[0,5]]
// Output: 42
//

LEETCODE_SOLUTION_UNITTEST(3068, FindTheMaximumSumOfNodeValues, example_3) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {7, 7, 7, 7, 7, 7};
  int                 k        = 3;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {0, 3},
      {0, 4},
      {0, 5}
  };
  long long expect = 42;
  long long actual = solution->maximumValueSum(nums, k, edges);
  LCD_EXPECT_EQ(expect, actual);
}
