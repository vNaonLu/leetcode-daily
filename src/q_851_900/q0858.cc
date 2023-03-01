// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Mirror Reflection
//
// https://leetcode.com/problems/mirror-reflection/
//
// Question ID: 858
// Difficult  : Medium
// Solve Date : 2022/08/04 18:31

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |858. Mirror Reflection|:
//
// There is a special square room with mirrors on each of the four walls. Except
// for the southwest corner, there are receptors on each of the remaining
// corners, numbered |0|, |1|, and |2|. The square room has walls of length
// |p|and a laser ray from the southwest corner first meets the east wall at a
// distance |q| from the |0ᵗʰ| receptor. Given the two integers |p| and |q|,
// return the number of the receptor that the ray meets first. The test cases
// are guaranteed so that the ray will meet a receptor eventually.
//

LEETCODE_BEGIN_RESOLVING(858, MirrorReflection, Solution);

class Solution {
private:
  template <typename type>
  type gcd(type x, type y) {
    return y == 0 ? x : gcd(y, x % y);
  }
  template <typename type>
  type lcm(type x, type y) {
    return x * y / gcd(x, y);
  }

public:
  int mirrorReflection(int p, int q) {
    auto lcm_pq = lcm(p, q);
    auto fac_p  = lcm_pq / p;
    auto fac_q  = lcm_pq / q;

    return fac_p & 1 ? (fac_q & 1 ? 1 : 2) : (fac_q & 1 ? 0 : -1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= q <= p <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: p = 2, q = 1
// Output: 2
//
// The ray meets receptor 2 the first time it gets reflected back to the left
// wall.

LEETCODE_SOLUTION_UNITTEST(858, MirrorReflection, example_1) {
  auto solution = MakeSolution();
  int  p        = 2;
  int  q        = 1;
  int  expect   = 2;
  int  actual   = solution->mirrorReflection(p, q);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: p = 3, q = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(858, MirrorReflection, example_2) {
  auto solution = MakeSolution();
  int  p        = 3;
  int  q        = 1;
  int  expect   = 1;
  int  actual   = solution->mirrorReflection(p, q);
  LCD_EXPECT_EQ(expect, actual);
}
