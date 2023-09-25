// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Moves to Seat Everyone
//
// https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/
//
// Question ID: 2037
// Difficult  : Easy
// Solve Date : 2023/09/23 11:19

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2037. Minimum Number of Moves to Seat Everyone|:
//
// There are |n| seats and |n| students in a room. You are given an array
// |seats| of length |n|, where |seats[i]| is the position of the |iᵗʰ| seat.
// You are also given the array |students| of length |n|, where |students[j]| is
// the position of the |jᵗʰ| student. You may perform the following move any
// number of times:
//
//  • Increase or decrease the position of the |iᵗʰ| student by |1| (i.e.,
//  moving the |iᵗʰ| student from position |x| to |x + 1| or |x - 1|)
// Return the minimum number of moves required to move each student to a seat
// such that no two students are in the same seat. Note that there may be
// multiple seats or students in the same position at the beginning.
//
//

LEETCODE_BEGIN_RESOLVING(2037, MinimumNumberOfMovesToSeatEveryone, Solution);

class Solution {
public:
  int minMovesToSeat(vector<int> &seats, vector<int> &students) {
    sort(seats.begin(), seats.end());
    sort(students.begin(), students.end());
    int res = 0;
    for (int i = 0; i < students.size(); ++i) {
      res += abs(students[i] - seats[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == seats.length == students.length|
// * |1 <= n <= 100|
// * |1 <= seats[i], students[j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: seats = [3,1,5], students = [2,7,4]
// Output: 4
//
// The students are moved as follows:
// - The first student is moved from from position 2 to position 1 using 1 move.
// - The second student is moved from from position 7 to position 5 using 2
// moves.
// - The third student is moved from from position 4 to position 3 using 1 move.
// In total, 1 + 2 + 1 = 4 moves were used.

LEETCODE_SOLUTION_UNITTEST(2037, MinimumNumberOfMovesToSeatEveryone,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> seats    = {3, 1, 5};
  vector<int> students = {2, 7, 4};
  int         expect   = 4;
  int         actual   = solution->minMovesToSeat(seats, students);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: seats = [4,1,5,9], students = [1,3,2,6]
// Output: 7
//
// The students are moved as follows:
// - The first student is not moved.
// - The second student is moved from from position 3 to position 4 using 1
// move.
// - The third student is moved from from position 2 to position 5 using 3
// moves.
// - The fourth student is moved from from position 6 to position 9 using 3
// moves. In total, 0 + 1 + 3 + 3 = 7 moves were used.

LEETCODE_SOLUTION_UNITTEST(2037, MinimumNumberOfMovesToSeatEveryone,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> seats    = {4, 1, 5, 9};
  vector<int> students = {1, 3, 2, 6};
  int         expect   = 7;
  int         actual   = solution->minMovesToSeat(seats, students);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: seats = [2,2,6,6], students = [1,3,2,6]
// Output: 4
//
// Note that there are two seats at position 2 and two seats at position 6.
// The students are moved as follows:
// - The first student is moved from from position 1 to position 2 using 1 move.
// - The second student is moved from from position 3 to position 6 using 3
// moves.
// - The third student is not moved.
// - The fourth student is not moved.
// In total, 1 + 3 + 0 + 0 = 4 moves were used.

LEETCODE_SOLUTION_UNITTEST(2037, MinimumNumberOfMovesToSeatEveryone,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> seats    = {2, 2, 6, 6};
  vector<int> students = {1, 3, 2, 6};
  int         expect   = 4;
  int         actual   = solution->minMovesToSeat(seats, students);
  LCD_EXPECT_EQ(expect, actual);
}
