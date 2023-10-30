// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Enemy Forts That Can Be Captured
//
// https://leetcode.com/problems/maximum-enemy-forts-that-can-be-captured/
//
// Question ID: 2511
// Difficult  : Easy
// Solve Date : 2023/10/30 19:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2511. Maximum Enemy Forts That Can Be Captured|:
//
// You are given a 0-indexed integer array |forts| of length |n| representing
// the positions of several forts. |forts[i]| can be |-1|, |0|, or |1| where:
//
//  • |-1| represents there is no fort at the |iᵗʰ| position.
//
//  • |0| indicates there is an enemy fort at the |iᵗʰ| position.
//
//  • |1| indicates the fort at the |iᵗʰ| the position is under your command.
// Now you have decided to move your army from one of your forts at position |i|
// to an empty position |j| such that:
//
//  • |0 <= i, j <= n - 1|
//
//  • The army travels over enemy forts only. Formally, for all |k| where
//  |min(i,j) < k < max(i,j)|, |forts[k] == 0.|
// While moving the army, all the enemy forts that come in the way are captured.
// Return the maximum number of enemy forts that can be captured. In case it is
// impossible to move your army, or you do not have any fort under your command,
// return |0|.
//
//

LEETCODE_BEGIN_RESOLVING(2511, MaximumEnemyFortsThatCanBeCaptured, Solution);

class Solution {
public:
  int captureForts(vector<int> &forts) {
    int res = 0;
    {
      auto beg = forts.begin();
      while (beg != forts.end()) {
        beg = capture(beg, forts.end(), &res);
      }
    }
    {
      auto beg = forts.rbegin();
      while (beg != forts.rend()) {
        beg = capture(beg, forts.rend(), &res);
      }
    }
    return res;
  }

private:
  template <typename It>
  It capture(It beg, It end, int *res) {
    while (beg != end && *beg != 1) {
      ++beg;
    }

    if (beg == end) {
      return beg;
    }

    auto it = ++beg;
    while (it != end && *it == 0) {
      ++it;
    }

    if (it != end && *it == -1) {
      *res = max<int>(*res, distance(beg, it));
    }

    return it;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= forts.length <= 1000|
// * |-1 <= forts[i] <= 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: forts = [1,0,0,-1,0,0,0,0,1]
// Output: 4
//
// - Moving the army from position 0 to position 3 captures 2 enemy forts, at 1
// and 2.
// - Moving the army from position 8 to position 3 captures 4 enemy forts.
// Since 4 is the maximum number of enemy forts that can be captured, we
// return 4.

LEETCODE_SOLUTION_UNITTEST(2511, MaximumEnemyFortsThatCanBeCaptured,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> forts    = {1, 0, 0, -1, 0, 0, 0, 0, 1};
  int         expect   = 4;
  int         actual   = solution->captureForts(forts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: forts = [0,0,1,-1]
// Output: 0
//
// Since no enemy fort can be captured, 0 is returned.

LEETCODE_SOLUTION_UNITTEST(2511, MaximumEnemyFortsThatCanBeCaptured,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> forts    = {0, 0, 1, -1};
  int         expect   = 0;
  int         actual   = solution->captureForts(forts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [-1,-1,0,1,0,0,1,-1,1,0]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2511, MaximumEnemyFortsThatCanBeCaptured,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> forts    = {-1, -1, 0, 1, 0, 0, 1, -1, 1, 0};
  int         expect   = 1;
  int         actual   = solution->captureForts(forts);
  LCD_EXPECT_EQ(expect, actual);
}
