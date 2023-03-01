// Copyright 2023 Naon Lu
//
// This file describes the solution of
// IPO
//
// https://leetcode.com/problems/ipo/
//
// Question ID: 502
// Difficult  : Hard
// Solve Date : 2023/02/23 20:02

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |502. IPO|:
//
// Suppose LeetCode will start its IPO soon. In order to sell a good price of
// its shares to Venture Capital, LeetCode would like to work on some projects
// to increase its capital before the IPO. Since it has limited resources, it
// can only finish at most |k| distinct projects before the IPO. Help LeetCode
// design the best way to maximize its total capital after finishing at most |k|
// distinct projects. You are given |n| projects where the |iᵗʰ| project has a
// pure profit |profits[i]| and a minimum capital of |capital[i]| is needed to
// start it. Initially, you have |w| capital. When you finish a project, you
// will obtain its pure profit and the profit will be added to your total
// capital. Pick a list of at most |k| distinct projects from given projects to
// maximize your final capital, and return the final maximized capital. The
// answer is guaranteed to fit in a 32-bit signed integer.
//

LEETCODE_BEGIN_RESOLVING(502, IPO, Solution);

class Solution {
public:
  int findMaximizedCapital(int k, int w, vector<int> &profits,
                           vector<int> &capital) {
    priority_queue<pair<int, int>> max_heap;
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        min_heap;
    for (int i = 0; i < profits.size(); ++i) {
      min_heap.emplace(capital[i], profits[i]);
    }

    while (k > 0) {
      while (!min_heap.empty() && min_heap.top().first <= w) {
        auto p = min_heap.top();
        min_heap.pop();
        max_heap.emplace(p.second, p.first);
      }
      if (!max_heap.empty()) {
        w += max_heap.top().first;
        max_heap.pop();
        --k;
      } else {
        break;
      }
    }
    return w;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= 10⁵|
// * |0 <= w <= 10⁹|
// * |n == profits.length|
// * |n == capital.length|
// * |1 <= n <= 10⁵|
// * |0 <= profits[i] <= 10⁴|
// * |0 <= capital[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
// Output: 4
//
// Since your initial capital is 0, you can only start the project indexed 0.
// After finishing it you will obtain profit 1 and your capital becomes 1.
// With capital 1, you can either start the project indexed 1 or the project
// indexed 2. Since you can choose at most 2 projects, you need to finish the
// project indexed 2 to get the maximum capital. Therefore, output the final
// maximized capital, which is 0 + 1 + 3 = 4.

LEETCODE_SOLUTION_UNITTEST(502, IPO, example_1) {
  auto        solution = MakeSolution();
  int         k        = 2;
  int         w        = 0;
  vector<int> profits  = {1, 2, 3};
  vector<int> capital  = {0, 1, 1};
  int         expect   = 4;
  int         actual   = solution->findMaximizedCapital(k, w, profits, capital);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(502, IPO, example_2) {
  auto        solution = MakeSolution();
  int         k        = 3;
  int         w        = 0;
  vector<int> profits  = {1, 2, 3};
  vector<int> capital  = {0, 1, 2};
  int         expect   = 6;
  int         actual   = solution->findMaximizedCapital(k, w, profits, capital);
  LCD_EXPECT_EQ(expect, actual);
}
