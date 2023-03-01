// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Teemo Attacking
//
// https://leetcode.com/problems/teemo-attacking/
//
// Question ID: 495
// Difficult  : Easy
// Solve Date : 2022/09/08 01:18

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |495. Teemo Attacking|:
//
// Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo
// attacks Ashe, Ashe gets poisoned for a exactly |duration| seconds. More
// formally, an attack at second |t| will mean Ashe is poisoned during the
// inclusive time interval |[t, t + duration - 1]|. If Teemo attacks again
// before the poison effect ends, the timer for it is reset, and the poison
// effect will end |duration| seconds after the new attack. You are given a
// non-decreasing integer array |timeSeries|, where |timeSeries[i]| denotes that
// Teemo attacks Ashe at second |timeSeries[i]|, and an integer |duration|.
// Return the total number of seconds that Ashe is poisoned.
//

LEETCODE_BEGIN_RESOLVING(495, TeemoAttacking, Solution);

class Solution {
public:
  int findPoisonedDuration(vector<int> &timeSeries, int duration) {
    auto res = (int)0;
    for (auto it = timeSeries.begin() + 1; it != timeSeries.end(); ++it) {
      res += min(duration, *it - *(it - 1));
    }
    return res + duration;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= timeSeries.length <= 10⁴|
// * |0 <= timeSeries[i], duration <= 10⁷|
// * |timeSeries| is sorted in non-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: timeSeries = [1,4], duration = 2
// Output: 4
//
// Teemo's attacks on Ashe go as follows:
// - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
// - At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
// Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.

LEETCODE_SOLUTION_UNITTEST(495, TeemoAttacking, example_1) {
  auto        solution   = MakeSolution();
  vector<int> timeSeries = {1, 4};
  int         duration   = 2;
  int         expect     = 4;
  int         actual     = solution->findPoisonedDuration(timeSeries, duration);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: timeSeries = [1,2], duration = 2
// Output: 3
//
// Teemo's attacks on Ashe go as follows:
// - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
// - At second 2 however, Teemo attacks again and resets the poison timer. Ashe
// is poisoned for seconds 2 and 3. Ashe is poisoned for seconds 1, 2, and 3,
// which is 3 seconds in total.

LEETCODE_SOLUTION_UNITTEST(495, TeemoAttacking, example_2) {
  auto        solution   = MakeSolution();
  vector<int> timeSeries = {1, 2};
  int         duration   = 2;
  int         expect     = 3;
  int         actual     = solution->findPoisonedDuration(timeSeries, duration);
  LCD_EXPECT_EQ(expect, actual);
}
