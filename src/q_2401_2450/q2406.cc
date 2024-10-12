// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Divide Intervals Into Minimum Number of Groups
//
// https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/
//
// Question ID: 2406
// Difficult  : Medium
// Solve Date : 2024/10/12 14:47

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2406. Divide Intervals Into Minimum Number of Groups|:
//
// You are given a 2D integer array |intervals| where |intervals[i] = [leftᵢ,
// rightᵢ]| represents the inclusive interval |[leftᵢ, rightᵢ]|. You have to
// divide the intervals into one or more groups such that each interval is in
// exactly one group, and no two intervals that are in the same group intersect
// each other. Return the minimum number of groups you need to make. Two
// intervals intersect if there is at least one common number between them. For
// example, the intervals |[1, 5]| and |[5, 8]| intersect.
//
//

LEETCODE_BEGIN_RESOLVING(2406, DivideIntervalsIntoMinimumNumberOfGroups,
                         Solution);

class Solution {
public:
  int minGroups(vector<vector<int>> &intervals) {
    vector<int> beg;
    vector<int> end;
    for (auto &v : intervals) {
      beg.emplace_back(v[0]);
      end.emplace_back(v[1]);
    }

    sort(beg.begin(), beg.end());
    sort(end.begin(), end.end());

    int  res = 0;
    auto it  = end.begin();
    for (auto x : beg) {
      if (x > *it) {
        ++it;
      } else {
        ++res;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= intervals.length <= 10⁵|
// * |intervals[i].length == 2|
// * |1 <= leftᵢ <= rightᵢ <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2406, DivideIntervalsIntoMinimumNumberOfGroups,
                           example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {5, 10},
      {6,  8},
      {1,  5},
      {2,  3},
      {1, 10}
  };
  int expect = 3;
  int actual = solution->minGroups(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: intervals = [[1,3],[5,6],[8,10],[11,13]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2406, DivideIntervalsIntoMinimumNumberOfGroups,
                           example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      { 1,  3},
      { 5,  6},
      { 8, 10},
      {11, 13}
  };
  int expect = 1;
  int actual = solution->minGroups(intervals);
  LCD_EXPECT_EQ(expect, actual);
}
