// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Pass the Pillow
//
// https://leetcode.com/problems/pass-the-pillow/
//
// Question ID: 2582
// Difficult  : Easy
// Solve Date : 2023/05/31 10:11

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2582. Pass the Pillow|:
//
// There are |n| people standing in a line labeled from |1| to |n|. The first
// person in the line is holding a pillow initially. Every second, the person
// holding the pillow passes it to the next person standing in the line. Once
// the pillow reaches the end of the line, the direction changes, and people
// continue passing the pillow in the opposite direction.
//
//  • For example, once the pillow reaches the |nᵗʰ| person they pass it to the
//  |n - 1ᵗʰ| person, then to the |n - 2ᵗʰ| person and so on.
// Given the two positive integers |n| and |time|, return the index of the
// person holding the pillow after |time| seconds.
//
//

LEETCODE_BEGIN_RESOLVING(2582, PassThePillow, Solution);

class Solution {
public:
  int passThePillow(int n, int time) {
    int x = time / (n - 1);
    time %= (n - 1);
    return x & 1 ? (n - time) : (1 + time);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 1000|
// * |1 <= time <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, time = 5
// Output: 2
//
// People pass the pillow in the following way: 1 -> 2 -> 3 -> 4 -> 3 -> 2.
// Afer five seconds, the pillow is given to the 2ⁿᵈ person.

LEETCODE_SOLUTION_UNITTEST(2582, PassThePillow, example_1) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  time     = 5;
  int  expect   = 2;
  int  actual   = solution->passThePillow(n, time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, time = 2
// Output: 3
//
// People pass the pillow in the following way: 1 -> 2 -> 3.
// Afer two seconds, the pillow is given to the 3ʳᵈ person.

LEETCODE_SOLUTION_UNITTEST(2582, PassThePillow, example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  time     = 2;
  int  expect   = 3;
  int  actual   = solution->passThePillow(n, time);
  LCD_EXPECT_EQ(expect, actual);
}
