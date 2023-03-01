// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Interval List Intersections
//
// https://leetcode.com/problems/interval-list-intersections/
//
// Question ID: 986
// Difficult  : Medium
// Solve Date : 2021/09/22 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |986. Interval List Intersections|:
//
// You are given two lists of closed intervals, |firstList| and |secondList|,
// where |firstList[i] = [startᵢ, endᵢ]| and |secondList[j] = [startⱼ, endⱼ]|.
// Each list of intervals is pairwise disjoint and in sorted order. Return the
// intersection of these two interval lists. A closed interval |[a, b]| (with |a
// <= b|) denotes the set of real numbers |x| with |a <= x <= b|. The
// intersection of two closed intervals is a set of real numbers that are either
// empty or represented as a closed interval. For example, the intersection of
// |[1, 3]| and |[2, 4]| is |[2, 3]|.  
//

LEETCODE_BEGIN_RESOLVING(986, IntervalListIntersections, Solution);

class Solution {
public:
  vector<vector<int>> intervalIntersection(vector<vector<int>> &firstList,
                                           vector<vector<int>> &secondList) {
    vector<vector<int>> res;
    auto                fit = firstList.begin();
    auto                sit = secondList.begin();
    int                 lo, hi;
    while (fit != firstList.end() && sit != secondList.end()) {
      lo = max((*fit)[0], (*sit)[0]);
      hi = min((*fit)[1], (*sit)[1]);
      if (lo <= hi) {
        res.push_back({lo, hi});
      }
      if ((*fit)[1] < (*sit)[1]) {
        ++fit;
      } else {
        ++sit;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= firstList.length, secondList.length <= 1000|
// * |firstList.length + secondList.length >= 1|
// * |0 <= startᵢ < endᵢ <= 10⁹|
// * |endᵢ < startᵢ₊₁|
// * |0 <= startⱼ < endⱼ <= 10⁹ |
// * |endⱼ < startⱼ₊₁|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: firstList = [[0,2],[5,10],[13,23],[24,25]], secondList =
//  [[1,5],[8,12],[15,24],[25,26]]
// Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
//

LEETCODE_SOLUTION_UNITTEST(986, IntervalListIntersections, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> firstList = {
      { 0,  2},
      { 5, 10},
      {13, 23},
      {24, 25}
  };
  vector<vector<int>> secondList = {
      { 1,  5},
      { 8, 12},
      {15, 24},
      {25, 26}
  };
  vector<vector<int>> expect = {
      { 1,  2},
      { 5,  5},
      { 8, 10},
      {15, 23},
      {24, 24},
      {25, 25}
  };
  vector<vector<int>> actual =
      solution->intervalIntersection(firstList, secondList);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: firstList = [[1,3],[5,9]], secondList = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(986, IntervalListIntersections, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> firstList = {
      {1, 3},
      {5, 9}
  };
  vector<vector<int>> secondList = {};
  vector<vector<int>> expect     = {};
  vector<vector<int>> actual =
      solution->intervalIntersection(firstList, secondList);
  LCD_EXPECT_EQ(expect, actual);
}
