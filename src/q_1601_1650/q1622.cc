// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Fancy Sequence
//
// https://leetcode.com/problems/fancy-sequence/
//
// Question ID: 1622
// Difficult  : Hard
// Solve Date : 2026/03/15 15:57

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1622. Fancy Sequence|:
//
// Write an API that generates fancy sequences using the |append|, |addAll|, and
// |multAll| operations. Implement the |Fancy| class:
//
//  • |Fancy()| Initializes the object with an empty sequence.
//
//  • |void append(val)| Appends an integer |val| to the end of the sequence.
//
//  • |void addAll(inc)| Increments all existing values in the sequence by an
//  integer |inc|.
//
//  • |void multAll(m)| Multiplies all existing values in the sequence by an
//  integer |m|.
//
//  • |int getIndex(idx)| Gets the current value at index |idx| (0-indexed) of
//  the sequence modulo |10⁹ + 7|. If the index is greater or equal than the
//  length of the sequence, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(1622, FancySequence, Fancy);

class Fancy {
public:
  Fancy() : a(1), b(0) {}

  void append(int val) {
    long long x = (val - b + mod) % mod;
    this->val.push_back((x * modPow(a, mod - 2, mod)) % mod);
  }

  void addAll(int inc) { b = (b + inc) % mod; }

  void multAll(int m) {
    a = (a * m) % mod;
    b = (b * m) % mod;
  }

  int getIndex(int idx) {
    if (idx >= val.size())
      return -1;
    return (a * val[idx] + b) % mod;
  }

private:
  const int         mod = 1e9 + 7;
  vector<long long> val;
  long long         a, b;
  long long         modPow(long long x, long long y, long long mod) {
    long long res = 1;
    x             = x % mod;
    while (y > 0) {
      if (y % 2 == 1) {
        res = (res * x) % mod;
      }
      y = y / 2;
      x = (x * x) % mod;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Fancy);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= val, inc, m <= 100|
// * |0 <= idx <= 10⁵|
// * At most |10⁵| calls total will be made to |append|, |addAll|, |multAll|,
// and |getIndex|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Fancy", "append", "addAll", "append", "multAll", "getIndex",
//  "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
// [[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
// Output: [null, null, null, null, null, 10, null, null, null, 26, 34, 20]
//

LEETCODE_SOLUTION_UNITTEST(1622, FancySequence, example_1) {
  auto fancy  = MakeFancy();
  int  s1_val = 2;
  fancy->append(s1_val);
  int s2_inc = 3;
  fancy->addAll(s2_inc);
  int s3_val = 7;
  fancy->append(s3_val);
  int s4_m = 2;
  fancy->multAll(s4_m);
  int s5_idx    = 0;
  int s5_expect = 10;
  int s5_actual = fancy->getIndex(s5_idx);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_inc = 3;
  fancy->addAll(s6_inc);
  int s7_val = 10;
  fancy->append(s7_val);
  int s8_m = 2;
  fancy->multAll(s8_m);
  int s9_idx    = 0;
  int s9_expect = 26;
  int s9_actual = fancy->getIndex(s9_idx);
  LCD_EXPECT_EQ(s9_expect, s9_actual);
  int s10_idx    = 1;
  int s10_expect = 34;
  int s10_actual = fancy->getIndex(s10_idx);
  LCD_EXPECT_EQ(s10_expect, s10_actual);
  int s11_idx    = 2;
  int s11_expect = 20;
  int s11_actual = fancy->getIndex(s11_idx);
  LCD_EXPECT_EQ(s11_expect, s11_actual);
}
