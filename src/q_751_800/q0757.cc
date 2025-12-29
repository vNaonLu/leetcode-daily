// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Set Intersection Size At Least Two
//
// https://leetcode.com/problems/set-intersection-size-at-least-two/
//
// Question ID: 757
// Difficult  : Hard
// Solve Date : 2025/11/20 21:40

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |757. Set Intersection Size At Least Two|:
//
// You are given a 2D integer array |intervals| where |intervals[i] = [startᵢ,
// endᵢ]| represents all the integers from |startᵢ| to |endᵢ| inclusively. A
// containing set is an array |nums| where each interval from |intervals| has at
// least two integers in |nums|.
//
//  • For example, if |intervals = [[1,3], [3,7], [8,9]]|, then |[1,2,4,7,8,9]|
//  and |[2,3,4,8,9]| are containing sets.
// Return the minimum possible size of a containing set.
//
//

LEETCODE_BEGIN_RESOLVING(757, SetIntersectionSizeAtLeastTwo, Solution);

class Solution {
public:
  static int intersectionSizeTwo(vector<vector<int>> &I) {
    sort(I.begin(), I.end(), [](vector<int> &X, vector<int> &Y) {
      const int x0 = X[0], x1 = X[1], y0 = Y[0], y1 = Y[1];
      return (x1 == y1) ? x0 > y0 : x1 < y1;
    });

    int cnt = 2, n = I.size();
    int b = I[0][1], a = b - 1;
    for (int i = 1; i < n; i++) {
      const int L = I[i][0], R = I[i][1];
      if (a >= L)
        continue;
      const bool NO = L > b;
      cnt += 1 + NO;
      a = (NO) ? R - 1 : b;
      b = R;
    }
    return cnt;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= intervals.length <= 3000|
// * |intervals[i].length == 2|
// * |0 <= startᵢ < endᵢ <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: intervals = [[1,3],[3,7],[8,9]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(757, SetIntersectionSizeAtLeastTwo, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 3},
      {3, 7},
      {8, 9}
  };
  int expect = 5;
  int actual = solution->intersectionSizeTwo(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: intervals = [[1,3],[1,4],[2,5],[3,5]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(757, SetIntersectionSizeAtLeastTwo, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 3},
      {1, 4},
      {2, 5},
      {3, 5}
  };
  int expect = 3;
  int actual = solution->intersectionSizeTwo(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: intervals = [[1,2],[2,3],[2,4],[4,5]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(757, SetIntersectionSizeAtLeastTwo, example_3) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 2},
      {2, 3},
      {2, 4},
      {4, 5}
  };
  int expect = 5;
  int actual = solution->intersectionSizeTwo(intervals);
  LCD_EXPECT_EQ(expect, actual);
}
