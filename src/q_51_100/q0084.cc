// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Rectangle in Histogram
//
// https://leetcode.com/problems/largest-rectangle-in-histogram/
//
// Question ID: 84
// Difficult  : Hard
// Solve Date : 2022/01/29 13:17

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |84. Largest Rectangle in Histogram|:
//
// Given an array of integers |heights| representing the histogram's bar height
// where the width of each bar is |1|, return the area of the largest rectangle
// in the histogram.  
//

LEETCODE_BEGIN_RESOLVING(84, LargestRectangleInHistogram, Solution);

class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    stack<int> stk;
    int        res = 0;
    int        i   = 0;
    while (i < heights.size()) {
      if (stk.empty() || heights[i] >= heights[stk.top()]) {
        stk.push(i++);
      } else {
        int curr = stk.top();
        stk.pop();
        int area = heights[curr] * (stk.empty() ? i : i - 1 - stk.top());
        res      = max(res, area);
      }
    }
    while (!stk.empty()) {
      int curr = stk.top();
      stk.pop();
      int area = heights[curr] * (stk.empty() ? i : i - 1 - stk.top());
      res      = max(res, area);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= heights.length <= 10⁵|
// * |0 <= heights[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: heights = [2,1,5,6,2,3]
// Output: 10
//
// The above is a histogram where width of each bar is 1.
// The largest rectangle is shown in the red area, which has an area = 10 units.

LEETCODE_SOLUTION_UNITTEST(84, LargestRectangleInHistogram, example_1) {
  auto        solution = MakeSolution();
  vector<int> heights  = {2, 1, 5, 6, 2, 3};
  int         expect   = 10;
  int         actual   = solution->largestRectangleArea(heights);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: heights = [2,4]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(84, LargestRectangleInHistogram, example_2) {
  auto        solution = MakeSolution();
  vector<int> heights  = {2, 4};
  int         expect   = 4;
  int         actual   = solution->largestRectangleArea(heights);
  LCD_EXPECT_EQ(expect, actual);
}
