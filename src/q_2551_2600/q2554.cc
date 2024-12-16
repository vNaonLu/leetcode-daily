// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Number of Integers to Choose From a Range I
//
// https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/
//
// Question ID: 2554
// Difficult  : Medium
// Solve Date : 2024/12/07 13:38

#include <bitset>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2554. Maximum Number of Integers to Choose From a Range I|:
//
// You are given an integer array |banned| and two integers |n| and |maxSum|.
// You are choosing some number of integers following the below rules:
//
//  • The chosen integers have to be in the range |[1, n]|.
//
//  • Each integer can be chosen at most once.
//
//  • The chosen integers should not be in the array |banned|.
//
//  • The sum of the chosen integers should not exceed |maxSum|.
// Return the maximum number of integers you can choose following the mentioned
// rules.
//
//

LEETCODE_BEGIN_RESOLVING(2554, MaximumNumberOfIntegersToChooseFromARangeI,
                         Solution);

class Solution {
public:
  int maxCount(vector<int> &banned, int n, int maxSum) {
    bitset<10001> xnot = 0;
    for (auto x : banned) {
      xnot[x] = 1;
    }
    int sum = 0;
    int cnt = 0;
    for (int i = 1; i <= n && sum <= maxSum; ++i) {
      if (!xnot[i]) {
        sum += i;
        ++cnt;
      }
    }
    return (sum < maxSum) ? cnt : cnt - 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= banned.length <= 10⁴|
// * |1 <= banned[i], n <= 10⁴|
// * |1 <= maxSum <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: banned = [1,6,5], n = 5, maxSum = 6
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2554, MaximumNumberOfIntegersToChooseFromARangeI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> banned   = {1, 6, 5};
  int         n        = 5;
  int         maxSum   = 6;
  int         expect   = 2;
  int         actual   = solution->maxCount(banned, n, maxSum);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: banned = [1,2,3,4,5,6,7], n = 8, maxSum = 1
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2554, MaximumNumberOfIntegersToChooseFromARangeI,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> banned   = {1, 2, 3, 4, 5, 6, 7};
  int         n        = 8;
  int         maxSum   = 1;
  int         expect   = 0;
  int         actual   = solution->maxCount(banned, n, maxSum);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: banned = [11], n = 7, maxSum = 50
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(2554, MaximumNumberOfIntegersToChooseFromARangeI,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> banned   = {11};
  int         n        = 7;
  int         maxSum   = 50;
  int         expect   = 7;
  int         actual   = solution->maxCount(banned, n, maxSum);
  LCD_EXPECT_EQ(expect, actual);
}
