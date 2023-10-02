// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rings and Rods
//
// https://leetcode.com/problems/rings-and-rods/
//
// Question ID: 2103
// Difficult  : Easy
// Solve Date : 2023/10/01 11:51

#include <iosfwd>
#include <set>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2103. Rings and Rods|:
//
// There are |n| rings and each ring is either red, green, or blue. The rings
// are distributed across ten rods labeled from |0| to |9|. You are given a
// string |rings| of length |2n| that describes the |n| rings that are placed
// onto the rods. Every two characters in |rings| forms a color-position pair
// that is used to describe each ring where:
//
//  • The first character of the |iᵗʰ| pair denotes the |iᵗʰ| ring's color (
//  |'R'|, |'G'|, |'B'|).
//
//  • The second character of the |iᵗʰ| pair denotes the rod that the |iᵗʰ| ring
//  is placed on ( |'0'| to |'9'|).
// For example, |"R3G2B1"| describes |n == 3| rings: a red ring placed onto the
// rod labeled 3, a green ring placed onto the rod labeled 2, and a blue ring
// placed onto the rod labeled 1. Return the number of rods that have all three
// colors of rings on them.
//
//

LEETCODE_BEGIN_RESOLVING(2103, RingsAndRods, Solution);

class Solution {
public:
  int countPoints(string rings) {
    vector<set<int>> rods(10);
    auto             beg = rings.begin();
    while (beg != rings.end()) {
      rods[*(beg + 1) - '0'].emplace(*beg);
      beg += 2;
    }
    return count_if(rods.begin(), rods.end(),
                    [](const set<int> &c) { return c.size() == 3; });
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |rings.length == 2 * n|
// * |1 <= n <= 100|
// * |rings[i]| where |i| is even is either |'R'|, |'G'|, or |'B'| (0-indexed).
// * |rings[i]| where |i| is odd is a digit from |'0'| to |'9'| (0-indexed).
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rings = "B0B6G0R6R0R6G9"
// Output: 1
//
// - The rod labeled 0 holds 3 rings with all colors: red, green, and blue.
// - The rod labeled 6 holds 3 rings, but it only has red and blue.
// - The rod labeled 9 holds only a green ring.
// Thus, the number of rods with all three colors is 1.

LEETCODE_SOLUTION_UNITTEST(2103, RingsAndRods, example_1) {
  auto   solution = MakeSolution();
  string rings    = "B0B6G0R6R0R6G9";
  int    expect   = 1;
  int    actual   = solution->countPoints(rings);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rings = "B0R0G0R9R0B0G0"
// Output: 1
//
// - The rod labeled 0 holds 6 rings with all colors: red, green, and blue.
// - The rod labeled 9 holds only a red ring.
// Thus, the number of rods with all three colors is 1.

LEETCODE_SOLUTION_UNITTEST(2103, RingsAndRods, example_2) {
  auto   solution = MakeSolution();
  string rings    = "B0R0G0R9R0B0G0";
  int    expect   = 1;
  int    actual   = solution->countPoints(rings);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: rings = "G4"
// Output: 0
//
// Only one ring is given. Thus, no rods have all three colors.

LEETCODE_SOLUTION_UNITTEST(2103, RingsAndRods, example_3) {
  auto   solution = MakeSolution();
  string rings    = "G4";
  int    expect   = 0;
  int    actual   = solution->countPoints(rings);
  LCD_EXPECT_EQ(expect, actual);
}
