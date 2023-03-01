// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Daily Temperatures
//
// https://leetcode.com/problems/daily-temperatures/
//
// Question ID: 739
// Difficult  : Medium
// Solve Date : 2021/11/13 11:51

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |739. Daily Temperatures|:
//
// Given an array of integers |temperatures| represents the daily temperatures,
// return an array |answer| such that |answer[i]| is the number of days you have
// to wait after the |iᵗʰ| day to get a warmer temperature. If there is no
// future day for which this is possible, keep |answer[i] == 0| instead.  
//

LEETCODE_BEGIN_RESOLVING(739, DailyTemperatures, Solution);

class Solution {
public:
  vector<int> dailyTemperatures(vector<int> &temperatures) {
    vector<int> res(temperatures.size(), 0);
    stack<int>  stack;
    int         wait = 1;
    for (int i = 0; i < temperatures.size(); ++i) {
      int cur = temperatures[i];
      while (!stack.empty() && temperatures[stack.top()] < cur) {
        res[stack.top()] = i - stack.top();
        stack.pop();
      }
      stack.push(i);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= temperatures.length <= 10⁵|
// * |30 <= temperatures[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: temperatures = [73,74,75,71,69,72,76,73]
// Output: [1,1,4,2,1,1,0,0]
//

LEETCODE_SOLUTION_UNITTEST(739, DailyTemperatures, example_1) {
  auto        solution     = MakeSolution();
  vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
  vector<int> expect       = {1, 1, 4, 2, 1, 1, 0, 0};
  vector<int> actual       = solution->dailyTemperatures(temperatures);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: temperatures = [30,40,50,60]
// Output: [1,1,1,0]
//

LEETCODE_SOLUTION_UNITTEST(739, DailyTemperatures, example_2) {
  auto        solution     = MakeSolution();
  vector<int> temperatures = {30, 40, 50, 60};
  vector<int> expect       = {1, 1, 1, 0};
  vector<int> actual       = solution->dailyTemperatures(temperatures);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: temperatures = [30,60,90]
// Output: [1,1,0]
//

LEETCODE_SOLUTION_UNITTEST(739, DailyTemperatures, example_3) {
  auto        solution     = MakeSolution();
  vector<int> temperatures = {30, 60, 90};
  vector<int> expect       = {1, 1, 0};
  vector<int> actual       = solution->dailyTemperatures(temperatures);
  LCD_EXPECT_EQ(expect, actual);
}
