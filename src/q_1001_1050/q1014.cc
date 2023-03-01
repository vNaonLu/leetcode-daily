// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Sightseeing Pair
//
// https://leetcode.com/problems/best-sightseeing-pair/
//
// Question ID: 1014
// Difficult  : Medium
// Solve Date : 2021/10/16 13:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1014. Best Sightseeing Pair|:
//
// You are given an integer array |values| where values[i] represents the value
// of the |iᵗʰ| sightseeing spot. Two sightseeing spots |i| and |j| have a
// distance |j - i| between them. The score of a pair ( |i < j|) of sightseeing
// spots is |values[i] + values[j] + i - j|: the sum of the values of the
// sightseeing spots, minus the distance between them. Return the maximum score
// of a pair of sightseeing spots.  
//

LEETCODE_BEGIN_RESOLVING(1014, BestSightseeingPair, Solution);

class Solution {
public:
  int maxScoreSightseeingPair(vector<int> &values) {
    int res = 0;
    int i = 0, dist = 1;
    while (i + dist < values.size()) {
      res = max(res, values[i] + values[i + dist] - dist);
      if (values[i] - dist <= values[i + dist]) {
        i += dist;
        dist = 1;
      } else {
        ++dist;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= values.length <= 5 * 10⁴|
// * |1 <= values[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: values = [8,1,5,2,6]
// Output: 11
//
// i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11

LEETCODE_SOLUTION_UNITTEST(1014, BestSightseeingPair, example_1) {
  auto        solution = MakeSolution();
  vector<int> values   = {8, 1, 5, 2, 6};
  int         expect   = 11;
  int         actual   = solution->maxScoreSightseeingPair(values);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: values = [1,2]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1014, BestSightseeingPair, example_2) {
  auto        solution = MakeSolution();
  vector<int> values   = {1, 2};
  int         expect   = 2;
  int         actual   = solution->maxScoreSightseeingPair(values);
  LCD_EXPECT_EQ(expect, actual);
}
