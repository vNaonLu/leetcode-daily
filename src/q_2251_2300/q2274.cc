// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Consecutive Floors Without Special Floors
//
// https://leetcode.com/problems/maximum-consecutive-floors-without-special-floors/
//
// Question ID: 2274
// Difficult  : Medium
// Solve Date : 2022/07/11 18:21

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2274. Maximum Consecutive Floors Without Special Floors|:
//
// Alice manages a company and has rented some floors of a building as office
// space. Alice has decided some of these floors should be special floors, used
// for relaxation only. You are given two integers |bottom| and |top|, which
// denote that Alice has rented all the floors from |bottom| to |top|
// (inclusive). You are also given the integer array |special|, where
// |special[i]| denotes a special floor that Alice has designated for
// relaxation. Return the maximum number of consecutive floors without a special
// floor.
//

LEETCODE_BEGIN_RESOLVING(2274, MaximumConsecutiveFloorsWithoutSpecialFloors,
                         Solution);

class Solution {
public:
  int maxConsecutive(int bottom, int top, vector<int> &special) {
    sort(special.begin(), special.end());
    int res = 0;
    res     = max(res, special.front() - bottom);
    res     = max(res, top - special.back());
    for (int i = 1; i < special.size(); ++i) {
      res = max(special[i] - special[i - 1] - 1, res);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= special.length <= 10⁵|
// * |1 <= bottom <= special[i] <= top <= 10⁹|
// * All the values of |special| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: bottom = 2, top = 9, special = [4,6]
// Output: 3
//
// The following are the ranges (inclusive) of consecutive floors without a
// special floor:
// - (2, 3) with a total amount of 2 floors.
// - (5, 5) with a total amount of 1 floor.
// - (7, 9) with a total amount of 3 floors.
// Therefore, we return the maximum number which is 3 floors.

LEETCODE_SOLUTION_UNITTEST(2274, MaximumConsecutiveFloorsWithoutSpecialFloors,
                           example_1) {
  auto        solution = MakeSolution();
  int         bottom   = 2;
  int         top      = 9;
  vector<int> special  = {4, 6};
  int         expect   = 3;
  int         actual   = solution->maxConsecutive(bottom, top, special);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: bottom = 6, top = 8, special = [7,6,8]
// Output: 0
//
// Every floor rented is a special floor, so we return 0.

LEETCODE_SOLUTION_UNITTEST(2274, MaximumConsecutiveFloorsWithoutSpecialFloors,
                           example_2) {
  auto        solution = MakeSolution();
  int         bottom   = 6;
  int         top      = 8;
  vector<int> special  = {7, 6, 8};
  int         expect   = 0;
  int         actual   = solution->maxConsecutive(bottom, top, special);
  LCD_EXPECT_EQ(expect, actual);
}
