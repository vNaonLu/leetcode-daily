// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximize Happiness of Selected Children
//
// https://leetcode.com/problems/maximize-happiness-of-selected-children/
//
// Question ID: 3075
// Difficult  : Medium
// Solve Date : 2024/05/09 20:43

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3075. Maximize Happiness of Selected Children|:
//
// You are given an array |happiness| of length |n|, and a positive integer |k|.
// There are |n| children standing in a queue, where the |iᵗʰ| child has
// happiness value |happiness[i]|. You want to select |k| children from these
// |n| children in |k| turns. In each turn, when you select a child, the
// happiness value of all the children that have not been selected till now
// decreases by |1|. Note that the happiness value cannot become negative and
// gets decremented only if it is positive. Return the maximum sum of the
// happiness values of the selected children you can achieve by selecting |k|
// children.
//
//

LEETCODE_BEGIN_RESOLVING(3075, MaximizeHappinessOfSelectedChildren, Solution);

class Solution {
public:
  long long maximumHappinessSum(vector<int> &happiness, int k) {
    int64_t res = 0;
    sort(happiness.begin(), happiness.end(), greater<int>{});
    for (int i = 0; i < k; ++i) {
      res += max(0, happiness[i] - i);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == happiness.length <= 2 * 10⁵|
// * |1 <= happiness[i] <= 10⁸|
// * |1 <= k <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: happiness = [1,2,3], k = 2
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3075, MaximizeHappinessOfSelectedChildren,
                           example_1) {
  auto        solution  = MakeSolution();
  vector<int> happiness = {1, 2, 3};
  int         k         = 2;
  long long   expect    = 4;
  long long   actual    = solution->maximumHappinessSum(happiness, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: happiness = [1,1,1,1], k = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3075, MaximizeHappinessOfSelectedChildren,
                           example_2) {
  auto        solution  = MakeSolution();
  vector<int> happiness = {1, 1, 1, 1};
  int         k         = 2;
  long long   expect    = 1;
  long long   actual    = solution->maximumHappinessSum(happiness, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: happiness = [2,3,4,5], k = 1
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3075, MaximizeHappinessOfSelectedChildren,
                           example_3) {
  auto        solution  = MakeSolution();
  vector<int> happiness = {2, 3, 4, 5};
  int         k         = 1;
  long long   expect    = 5;
  long long   actual    = solution->maximumHappinessSum(happiness, k);
  LCD_EXPECT_EQ(expect, actual);
}
