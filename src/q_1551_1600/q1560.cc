// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Most Visited Sector in  a Circular Track
//
// https://leetcode.com/problems/most-visited-sector-in-a-circular-track/
//
// Question ID: 1560
// Difficult  : Easy
// Solve Date : 2023/08/25 20:09

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1560. Most Visited Sector in  a Circular Track|:
//
// Given an integer |n| and an integer array |rounds|. We have a circular track
// which consists of |n| sectors labeled from |1| to |n|. A marathon will be
// held on this track, the marathon consists of |m| rounds. The |iᵗʰ| round
// starts at sector |rounds[i - 1]| and ends at sector |rounds[i]|. For example,
// round 1 starts at sector |rounds[0]| and ends at sector |rounds[1]| Return an
// array of the most visited sectors sorted in ascending order. Notice that you
// circulate the track in ascending order of sector numbers in the
// counter-clockwise direction (See the first example).
//
//

LEETCODE_BEGIN_RESOLVING(1560, MostVisitedSectorInACircularTrack, Solution);

class Solution {
public:
  vector<int> mostVisited(int n, vector<int> &rounds) {
    vector<int> res;
    if (rounds.front() <= rounds.back()) {
      for (int i = rounds.front(); i <= rounds.back(); ++i) {
        res.emplace_back(i);
      }
    } else {
      for (int i = 1; i <= rounds.back(); ++i) {
        res.emplace_back(i);
      }
      for (int i = rounds.front(); i <= n; ++i) {
        res.emplace_back(i);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 100|
// * |1 <= m <= 100|
// * |rounds.length == m + 1|
// * |1 <= rounds[i] <= n|
// * |rounds[i] != rounds[i + 1]| for |0 <= i < m|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, rounds = [1,3,1,2]
// Output: [1,2]
//
// The marathon starts at sector 1. The order of the visited sectors is as
// follows: 1 --> 2 --> 3 (end of round 1) --> 4 --> 1 (end of round 2) --> 2
// (end of round 3 and the marathon) We can see that both sectors 1 and 2 are
// visited twice and they are the most visited sectors. Sectors 3 and 4 are
// visited only once.

LEETCODE_SOLUTION_UNITTEST(1560, MostVisitedSectorInACircularTrack, example_1) {
  auto        solution = MakeSolution();
  int         n        = 4;
  vector<int> rounds   = {1, 3, 1, 2};
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->mostVisited(n, rounds);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, rounds = [2,1,2,1,2,1,2,1,2]
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(1560, MostVisitedSectorInACircularTrack, example_2) {
  auto        solution = MakeSolution();
  int         n        = 2;
  vector<int> rounds   = {2, 1, 2, 1, 2, 1, 2, 1, 2};
  vector<int> expect   = {2};
  vector<int> actual   = solution->mostVisited(n, rounds);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 7, rounds = [1,3,5,7]
// Output: [1,2,3,4,5,6,7]
//

LEETCODE_SOLUTION_UNITTEST(1560, MostVisitedSectorInACircularTrack, example_3) {
  auto        solution = MakeSolution();
  int         n        = 7;
  vector<int> rounds   = {1, 3, 5, 7};
  vector<int> expect   = {1, 2, 3, 4, 5, 6, 7};
  vector<int> actual   = solution->mostVisited(n, rounds);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 3
// [3,2,1,2,1,3,2,1,2,1,3,2,3,1]
// Output: [1,3]
//

LEETCODE_SOLUTION_UNITTEST(1560, MostVisitedSectorInACircularTrack,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  int         n        = 3;
  vector<int> rounds   = {3, 2, 1, 2, 1, 3, 2, 1, 2, 1, 3, 2, 3, 1};
  vector<int> expect   = {1, 3};
  vector<int> actual   = solution->mostVisited(n, rounds);
  LCD_EXPECT_EQ(expect, actual);
}
