// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Building Where Alice and Bob Can Meet
//
// https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/
//
// Question ID: 2940
// Difficult  : Hard
// Solve Date : 2024/12/22 20:08

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2940. Find Building Where Alice and Bob Can Meet|:
//
// You are given a 0-indexed array |heights| of positive integers, where
// |heights[i]| represents the height of the |iᵗʰ| building. If a person is in
// building |i|, they can move to any other building |j| if and only if |i < j|
// and |heights[i] < heights[j]|. You are also given another array |queries|
// where |queries[i] = [aᵢ, bᵢ]|. On the |iᵗʰ| query, Alice is in building |aᵢ|
// while Bob is in building |bᵢ|. Return an array |ans| where |ans[i]| is the
// index of the leftmost building where Alice and Bob can meet on the |iᵗʰ|
// query. If Alice and Bob cannot move to a common building on query |i|, set
// |ans[i]| to |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2940, FindBuildingWhereAliceAndBobCanMeet, Solution);

class Solution {
public:
  vector<int> leftmostBuildingQueries(vector<int>         &heights,
                                      vector<vector<int>> &queries) {
    vector<vector<vector<int>>> storeQueries(heights.size());
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>
                maxIndex;
    vector<int> result(queries.size(), -1);

    // Store the mappings for all queries in storeQueries.
    for (int currQuery = 0; currQuery < queries.size(); currQuery++) {
      int a = queries[currQuery][0], b = queries[currQuery][1];
      if (a < b && heights[a] < heights[b]) {
        result[currQuery] = b;
      } else if (a > b && heights[a] > heights[b]) {
        result[currQuery] = a;
      } else if (a == b) {
        result[currQuery] = a;
      } else {
        storeQueries[max(a, b)].push_back(
            {max(heights[a], heights[b]), currQuery});
      }
    }

    for (int index = 0; index < heights.size(); index++) {
      // If the priority queue's minimum pair value is less than the
      // current index of height, it is an answer to the query.
      while (!maxIndex.empty() && maxIndex.top()[0] < heights[index]) {
        result[maxIndex.top()[1]] = index;
        maxIndex.pop();
      }
      // Push the with their maximum index as the current index in the
      // priority queue.
      for (auto &element : storeQueries[index]) {
        maxIndex.push(element);
      }
    }
    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= heights.length <= 5 * 10⁴|
// * |1 <= heights[i] <= 10⁹|
// * |1 <= queries.length <= 5 * 10⁴|
// * |queries[i] = [aᵢ, bᵢ]|
// * |0 <= aᵢ, bᵢ <= heights.length - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
// Output: [2,5,-1,5,2]
//

LEETCODE_SOLUTION_UNITTEST(2940, FindBuildingWhereAliceAndBobCanMeet,
                           example_1) {
  auto                solution = MakeSolution();
  vector<int>         heights  = {6, 4, 8, 5, 2, 7};
  vector<vector<int>> queries  = {
      {0, 1},
      {0, 3},
      {2, 4},
      {3, 4},
      {2, 2}
  };
  vector<int> expect = {2, 5, -1, 5, 2};
  vector<int> actual = solution->leftmostBuildingQueries(heights, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: heights = [5,3,8,2,6,1,4,6], queries =
//  [[0,7],[3,5],[5,2],[3,0],[1,6]]
// Output: [7,6,-1,4,6]
//

LEETCODE_SOLUTION_UNITTEST(2940, FindBuildingWhereAliceAndBobCanMeet,
                           example_2) {
  auto                solution = MakeSolution();
  vector<int>         heights  = {5, 3, 8, 2, 6, 1, 4, 6};
  vector<vector<int>> queries  = {
      {0, 7},
      {3, 5},
      {5, 2},
      {3, 0},
      {1, 6}
  };
  vector<int> expect = {7, 6, -1, 4, 6};
  vector<int> actual = solution->leftmostBuildingQueries(heights, queries);
  LCD_EXPECT_EQ(expect, actual);
}
