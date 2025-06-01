// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Distribute Candies Among Children II
//
// https://leetcode.com/problems/distribute-candies-among-children-ii/
//
// Question ID: 2929
// Difficult  : Medium
// Solve Date : 2025/06/01 13:04

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2929. Distribute Candies Among Children II|:
//
// You are given two positive integers |n| and |limit|.
// Return the total number of ways to distribute |n| candies among |3| children
// such that no child gets more than |limit| candies.
//
//

LEETCODE_BEGIN_RESOLVING(2929, DistributeCandiesAmongChildrenII, Solution);

class Solution {
public:
  long long distributeCandies(int n, int limit) {
    int64_t res = 0;
    for (int i = 0; i <= min(limit, n); ++i) {
      if (n - i <= 2 * limit) {
        res += min(n - i, limit) - max(0, n - i - limit) + 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁶|
// * |1 <= limit <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, limit = 2
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2929, DistributeCandiesAmongChildrenII, example_1) {
  auto      solution = MakeSolution();
  int       n        = 5;
  int       limit    = 2;
  long long expect   = 3;
  long long actual   = solution->distributeCandies(n, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, limit = 3
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(2929, DistributeCandiesAmongChildrenII, example_2) {
  auto      solution = MakeSolution();
  int       n        = 3;
  int       limit    = 3;
  long long expect   = 10;
  long long actual   = solution->distributeCandies(n, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 6
// 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2929, DistributeCandiesAmongChildrenII,
                           extra_testcase_1) {
  auto      solution = MakeSolution();
  int       n        = 6;
  int       limit    = 2;
  long long expect   = 1;
  long long actual   = solution->distributeCandies(n, limit);
  LCD_EXPECT_EQ(expect, actual);
}
