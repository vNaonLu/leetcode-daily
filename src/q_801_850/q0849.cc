// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximize Distance to Closest Person
//
// https://leetcode.com/problems/maximize-distance-to-closest-person/
//
// Question ID: 849
// Difficult  : Medium
// Solve Date : 2022/01/16 15:14

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |849. Maximize Distance to Closest Person|:
//
// You are given an array representing a row of |seats| where |seats[i] = 1|
// represents a person sitting in the |iᵗʰ| seat, and |seats[i] = 0| represents
// that the |iᵗʰ| seat is empty (0-indexed). There is at least one empty seat,
// and at least one person sitting. Alex wants to sit in the seat such that the
// distance between him and the closest person to him is maximized.  Return that
// maximum distance to the closest person.  
//

LEETCODE_BEGIN_RESOLVING(849, MaximizeDistanceToClosestPerson, Solution);

class Solution {
public:
  int maxDistToClosest(vector<int> &seats) {
    int res  = 0;
    int left = -1, right = 0;
    for (int i = 0; i < seats.size(); ++i) {
      if (seats[i] == 1) {
        left = i;
      } else {
        while (right < seats.size() && seats[right] == 0 || right < i)
          ++right;
        res = max(res,
                  min((left == -1 ? std::numeric_limits<int>::max() : i - left),
                      (right == seats.size() ? std::numeric_limits<int>::max()
                                             : right - i)));
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= seats.length <= 2 * 10⁴|
// * |seats[i]| is |0| or  |1|.
// * At least one seat is empty.
// * At least one seat is occupied.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: seats = [1,0,0,0,1,0,1]
// Output: 2
//
// If Alex sits in the second open seat (i.e. seats[2]), then the closest person
// has distance 2. If Alex sits in any other open seat, the closest person has
// distance 1. Thus, the maximum distance to the closest person is 2.

LEETCODE_SOLUTION_UNITTEST(849, MaximizeDistanceToClosestPerson, example_1) {
  auto        solution = MakeSolution();
  vector<int> seats    = {1, 0, 0, 0, 1, 0, 1};
  int         expect   = 2;
  int         actual   = solution->maxDistToClosest(seats);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: seats = [1,0,0,0]
// Output: 3
//
// If Alex sits in the last seat (i.e. seats[3]), the closest person is 3 seats
// away. This is the maximum distance possible, so the answer is 3.

LEETCODE_SOLUTION_UNITTEST(849, MaximizeDistanceToClosestPerson, example_2) {
  auto        solution = MakeSolution();
  vector<int> seats    = {1, 0, 0, 0};
  int         expect   = 3;
  int         actual   = solution->maxDistToClosest(seats);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: seats = [0,1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(849, MaximizeDistanceToClosestPerson, example_3) {
  auto        solution = MakeSolution();
  vector<int> seats    = {0, 1};
  int         expect   = 1;
  int         actual   = solution->maxDistToClosest(seats);
  LCD_EXPECT_EQ(expect, actual);
}
