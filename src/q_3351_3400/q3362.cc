// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Zero Array Transformation III
//
// https://leetcode.com/problems/zero-array-transformation-iii/
//
// Question ID: 3362
// Difficult  : Medium
// Solve Date : 2025/05/22 22:43

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3362. Zero Array Transformation III|:
//
// You are given an integer array |nums| of length |n| and a 2D array |queries|
// where |queries[i] = [lᵢ, rᵢ]|. Each |queries[i]| represents the following
// action on |nums|:
//
//  • Decrement the value at each index in the range |[lᵢ, rᵢ]| in |nums| by at
//  most 1.
//
//  • The amount by which the value is decremented can be chosen independently
//  for each index.
// A Zero Array is an array with all its elements equal to 0.
// Return the maximum number of elements that can be removed from |queries|,
// such that |nums| can still be converted to a zero array using the remaining
// queries. If it is not possible to convert |nums| to a zero array, return -1.
//
//

LEETCODE_BEGIN_RESOLVING(3362, ZeroArrayTransformationIII, Solution);

class Solution {
public:
  int maxRemoval(vector<int> &nums, vector<vector<int>> &queries) {
    sort(queries.begin(), queries.end());
    priority_queue<int>                            available;
    priority_queue<int, vector<int>, greater<int>> assigned;
    int                                            count = 0;

    for (int time = 0, k = 0; time < nums.size(); time++) {
      while (!assigned.empty() && assigned.top() < time)
        assigned.pop();
      while (k < queries.size() && queries[k][0] <= time)
        available.push(queries[k++][1]);
      while (assigned.size() < nums[time] && !available.empty() &&
             available.top() >= time) {
        assigned.push(available.top());
        available.pop();
        count++;
      }
      if (assigned.size() < nums[time])
        return -1;
    }
    return queries.size() - count;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
// * |1 <= queries.length <= 10⁵|
// * |queries[i].length == 2|
// * |0 <= lᵢ <= rᵢ < nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3362, ZeroArrayTransformationIII, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {2, 0, 2};
  vector<vector<int>> queries  = {
      {0, 2},
      {0, 2},
      {1, 1}
  };
  int expect = 1;
  int actual = solution->maxRemoval(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3362, ZeroArrayTransformationIII, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 1, 1, 1};
  vector<vector<int>> queries  = {
      {1, 3},
      {0, 2},
      {1, 3},
      {1, 2}
  };
  int expect = 2;
  int actual = solution->maxRemoval(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4], queries = [[0,3]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3362, ZeroArrayTransformationIII, example_3) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 2, 3, 4};
  vector<vector<int>> queries  = {
      {0, 3}
  };
  int expect = -1;
  int actual = solution->maxRemoval(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}
