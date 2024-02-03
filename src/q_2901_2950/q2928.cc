// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Distribute Candies Among Children I
//
// https://leetcode.com/problems/distribute-candies-among-children-i/
//
// Question ID: 2928
// Difficult  : Easy
// Solve Date : 2024/02/03 12:19

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2928. Distribute Candies Among Children I|:
//
// You are given two positive integers |n| and |limit|.
// Return the total number of ways to distribute |n| candies among |3| children
// such that no child gets more than |limit| candies.
//
//

LEETCODE_BEGIN_RESOLVING(2928, DistributeCandiesAmongChildrenI, Solution);

class Solution {
public:
  int distributeCandies(int n, int limit) { return helper(n, 3, limit); }

private:
  int helper(int candies, int children, int limit) {
    if (children == 0) {
      return candies == 0 ? 1 : 0;
    }

    int res   = 0;
    int range = min(candies, limit) + 1;
    for (int i = 0; i < range; ++i) {
      res += helper(candies - i, children - 1, limit);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 50|
// * |1 <= limit <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, limit = 2
// Output: 3
//
// There are 3 ways to distribute 5 candies such that no child gets more than 2
// candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).

LEETCODE_SOLUTION_UNITTEST(2928, DistributeCandiesAmongChildrenI, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  limit    = 2;
  int  expect   = 3;
  int  actual   = solution->distributeCandies(n, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, limit = 3
// Output: 10
//
// There are 10 ways to distribute 3 candies such that no child gets more than 3
// candies: (0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2), (1, 1, 1),
// (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).

LEETCODE_SOLUTION_UNITTEST(2928, DistributeCandiesAmongChildrenI, example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  limit    = 3;
  int  expect   = 10;
  int  actual   = solution->distributeCandies(n, limit);
  LCD_EXPECT_EQ(expect, actual);
}
