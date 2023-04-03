// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reducing Dishes
//
// https://leetcode.com/problems/reducing-dishes/
//
// Question ID: 1402
// Difficult  : Hard
// Solve Date : 2023/03/29 18:37

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1402. Reducing Dishes|:
//
// A chef has collected data on the |satisfaction| level of his |n| dishes. Chef
// can cook any dish in 1 unit of time. Like-time coefficient of a dish is
// defined as the time taken to cook that dish including previous dishes
// multiplied by its satisfaction level i.e. |time[i] * satisfaction[i]|. Return
// the maximum sum of like-time coefficient that the chef can obtain after
// dishes preparation. Dishes can be prepared in any order and the chef can
// discard some dishes to get this maximum value.
//
//

LEETCODE_BEGIN_RESOLVING(1402, ReducingDishes, Solution);

class Solution {
public:
  int maxSatisfaction(vector<int> &satisfaction) {
    int n = satisfaction.size();
    sort(satisfaction.rbegin(), satisfaction.rend());
    vector<int> sum = satisfaction;
    for (int i = 1; i < n; ++i) {
      sum[i] += sum[i - 1];
    }
    int res = 0;
    int cur = 0;
    for (auto x : sum) {
      cur += x;
      res = max(res, cur);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == satisfaction.length|
// * |1 <= n <= 500|
// * |-1000 <= satisfaction[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: satisfaction = [-1,-8,0,5,-9]
// Output: 14
//
// After Removing the second and last dish, the maximum total like-time
// coefficient will be equal to (-1*1 + 0*2 + 5*3 = 14). Each dish is prepared
// in one unit of time.

LEETCODE_SOLUTION_UNITTEST(1402, ReducingDishes, example_1) {
  auto        solution     = MakeSolution();
  vector<int> satisfaction = {-1, -8, 0, 5, -9};
  int         expect       = 14;
  int         actual       = solution->maxSatisfaction(satisfaction);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: satisfaction = [4,3,2]
// Output: 20
//
// Dishes can be prepared in any order, (2*1 + 3*2 + 4*3 = 20)

LEETCODE_SOLUTION_UNITTEST(1402, ReducingDishes, example_2) {
  auto        solution     = MakeSolution();
  vector<int> satisfaction = {4, 3, 2};
  int         expect       = 20;
  int         actual       = solution->maxSatisfaction(satisfaction);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: satisfaction = [-1,-4,-5]
// Output: 0
//
// People do not like the dishes. No dish is prepared.

LEETCODE_SOLUTION_UNITTEST(1402, ReducingDishes, example_3) {
  auto        solution     = MakeSolution();
  vector<int> satisfaction = {-1, -4, -5};
  int         expect       = 0;
  int         actual       = solution->maxSatisfaction(satisfaction);
  LCD_EXPECT_EQ(expect, actual);
}
