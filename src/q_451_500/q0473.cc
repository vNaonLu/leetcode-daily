// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Matchsticks to Square
//
// https://leetcode.com/problems/matchsticks-to-square/
//
// Question ID: 473
// Difficult  : Medium
// Solve Date : 2022/07/12 13:10

#include <iosfwd>
#include <map>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |473. Matchsticks to Square|:
//
// You are given an integer array |matchsticks| where |matchsticks[i]| is the
// length of the |iᵗʰ| matchstick. You want to use all the matchsticks to make
// one square. You should not break any stick, but you can link them up, and
// each matchstick must be used exactly one time. Return |true| if you can make
// this square and |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(473, MatchsticksToSquare, Solution);

class Solution {
private:
  map<pair<int, int>, bool> memo;
  vector<int>               nums;
  int                       possible;

  bool helper(int mask, int side) {
    int total = 0, n = nums.size();

    auto k = make_pair(mask, side);
    for (int i = n - 1; i >= 0; --i) {
      if ((mask & (1 << i)) == 0) {
        total += nums[n - 1 - i];
      }
    }

    if (total > 0 && total % possible == 0) {
      ++side;
    }

    if (side == 3) {
      return true;
    }

    if (memo.count(k)) {
      return memo[k];
    }

    bool res = false;
    int  c = total / possible, rem = possible * (c + 1) - total;

    for (int i = n - 1; i >= 0; --i) {
      if (nums[n - 1 - i] <= rem && (mask & (1 << i)) > 0) {
        if (helper(mask ^ (1 << i), side)) {
          res = true;
          break;
        }
      }
    }

    return memo[k] = res;
  }

public:
  bool makesquare(vector<int> &matchsticks) {
    possible = accumulate(matchsticks.begin(), matchsticks.end(), 0);
    nums     = move(matchsticks);

    if (possible == 0 || possible % 4 != 0) {

      return false;
    }
    possible /= 4;

    return helper((1 << nums.size()) - 1, 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= matchsticks.length <= 15|
// * |1 <= matchsticks[i] <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matchsticks = [1,1,2,2,2]
// Output: true
//
// You can form a square with length 2, one side of the square came two sticks
// with length 1.

LEETCODE_SOLUTION_UNITTEST(473, MatchsticksToSquare, example_1) {
  auto        solution    = MakeSolution();
  vector<int> matchsticks = {1, 1, 2, 2, 2};
  bool        expect      = true;
  bool        actual      = solution->makesquare(matchsticks);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matchsticks = [3,3,3,3,4]
// Output: false
//
// You cannot find a way to form a square with all the matchsticks.

LEETCODE_SOLUTION_UNITTEST(473, MatchsticksToSquare, example_2) {
  auto        solution    = MakeSolution();
  vector<int> matchsticks = {3, 3, 3, 3, 4};
  bool        expect      = false;
  bool        actual      = solution->makesquare(matchsticks);
  LCD_EXPECT_EQ(expect, actual);
}
