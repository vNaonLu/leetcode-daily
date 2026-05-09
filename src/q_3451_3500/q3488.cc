// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Closest Equal Element Queries
//
// https://leetcode.com/problems/closest-equal-element-queries/
//
// Question ID: 3488
// Difficult  : Medium
// Solve Date : 2026/04/17 14:12

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3488. Closest Equal Element Queries|:
//
// You are given a circular array |nums| and an array |queries|.
// For each query |i|, you have to find the following:
//
//  • The minimum distance between the element at index |queries[i]| and any
//  other index |j| in the circular array, where |nums[j] == nums[queries[i]]|.
//  If no such index exists, the answer for that query should be -1.
// Return an array |answer| of the same size as |queries|, where |answer[i]|
// represents the result for query |i|.
//
//

LEETCODE_BEGIN_RESOLVING(3488, ClosestEqualElementQueries, Solution);

class Solution {
public:
  vector<int> solveQueries(vector<int> &nums, vector<int> &queries) {
    int                             n = nums.size();
    unordered_map<int, vector<int>> numsPos;
    for (int i = 0; i < n; i++) {
      numsPos[nums[i]].push_back(i);
    }
    for (auto &[_, pos] : numsPos) {
      int x = pos[0];
      pos.insert(pos.begin(), pos.back() - n);
      pos.push_back(x + n);
    }
    int m = queries.size();
    for (int i = 0; i < m; i++) {
      int x = nums[queries[i]];
      if (numsPos[x].size() == 3) {
        queries[i] = -1;
        continue;
      }
      int pos = lower_bound(numsPos[x].begin(), numsPos[x].end(), queries[i]) -
                numsPos[x].begin();
      queries[i] = min(numsPos[x][pos + 1] - numsPos[x][pos],
                       numsPos[x][pos] - numsPos[x][pos - 1]);
    }
    return queries;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= queries.length <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁶|
// * |0 <= queries[i] < nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
// Output: [2,-1,3]
//

LEETCODE_SOLUTION_UNITTEST(3488, ClosestEqualElementQueries, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 1, 4, 1, 3, 2};
  vector<int> queries  = {0, 3, 5};
  vector<int> expect   = {2, -1, 3};
  vector<int> actual   = solution->solveQueries(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4], queries = [0,1,2,3]
// Output: [-1,-1,-1,-1]
//

LEETCODE_SOLUTION_UNITTEST(3488, ClosestEqualElementQueries, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  vector<int> queries  = {0, 1, 2, 3};
  vector<int> expect   = {-1, -1, -1, -1};
  vector<int> actual   = solution->solveQueries(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}
