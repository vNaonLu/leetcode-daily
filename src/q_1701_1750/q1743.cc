// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Restore the Array From Adjacent Pairs
//
// https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/
//
// Question ID: 1743
// Difficult  : Medium
// Solve Date : 2023/11/10 23:16

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1743. Restore the Array From Adjacent Pairs|:
//
// There is an integer array |nums| that consists of |n| unique elements, but
// you have forgotten it. However, you do remember every pair of adjacent
// elements in |nums|. You are given a 2D integer array |adjacentPairs| of size
// |n - 1| where each |adjacentPairs[i] = [uᵢ, vᵢ]| indicates that the elements
// |uᵢ| and |vᵢ| are adjacent in |nums|. It is guaranteed that every adjacent
// pair of elements |nums[i]| and |nums[i+1]| will exist in |adjacentPairs|,
// either as |[nums[i], nums[i+1]]| or |[nums[i+1], nums[i]]|. The pairs can
// appear in any order. Return the original array |nums|. If there are multiple
// solutions, return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(1743, RestoreTheArrayFromAdjacentPairs, Solution);

class Solution {
public:
  vector<int> restoreArray(vector<vector<int>> &adjacentPairs) {
    unordered_map<int, vector<int>> pairs;
    for (auto &v : adjacentPairs) {
      pairs[v[0]].emplace_back(v[1]);
      pairs[v[1]].emplace_back(v[0]);
    }
    vector<int> res;
    int         start = -1e6;

    for (auto &entry : pairs) {
      if (entry.second.size() == 1) {
        start = entry.first;
        break;
      }
    }

    int left = -1e6;
    res.emplace_back(start);
    for (int i = 1; i < adjacentPairs.size() + 1; ++i) {
      auto &v      = pairs[start];
      int   newval = (v[0] == left) ? v[1] : v[0];
      res.emplace_back(newval);
      left  = start;
      start = newval;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |nums.length == n|
// * |adjacentPairs.length == n - 1|
// * |adjacentPairs[i].length == 2|
// * |2 <= n <= 10⁵|
// * |-10⁵ <= nums[i], uᵢ, vᵢ <= 10⁵|
// * There exists some |nums| that has |adjacentPairs| as its pairs.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: adjacentPairs = [[2,1],[3,4],[3,2]]
// Output: [1,2,3,4]
//
// This array has all its adjacent pairs in adjacentPairs.
// Notice that adjacentPairs[i] may not be in left-to-right order.

LEETCODE_SOLUTION_UNITTEST(1743, RestoreTheArrayFromAdjacentPairs, example_1) {
  auto                solution      = MakeSolution();
  vector<vector<int>> adjacentPairs = {
      {2, 1},
      {3, 4},
      {3, 2}
  };
  vector<int> expect = {1, 2, 3, 4};
  vector<int> actual = solution->restoreArray(adjacentPairs);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
// Output: [-2,4,1,-3]
//
// There can be negative numbers.
// Another solution is [-3,1,4,-2], which would also be accepted.

LEETCODE_SOLUTION_UNITTEST(1743, RestoreTheArrayFromAdjacentPairs, example_2) {
  auto                solution      = MakeSolution();
  vector<vector<int>> adjacentPairs = {
      { 4, -2},
      { 1,  4},
      {-3,  1}
  };
  vector<int> expect = {-2, 4, 1, -3};
  vector<int> actual = solution->restoreArray(adjacentPairs);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: adjacentPairs = [[100000,-100000]]
// Output: [100000,-100000]
//

LEETCODE_SOLUTION_UNITTEST(1743, RestoreTheArrayFromAdjacentPairs, example_3) {
  auto                solution      = MakeSolution();
  vector<vector<int>> adjacentPairs = {
      {100000, -100000}
  };
  vector<int> expect = {100000, -100000};
  vector<int> actual = solution->restoreArray(adjacentPairs);
  EXPECT_ANYORDER_EQ(expect, actual);
}
