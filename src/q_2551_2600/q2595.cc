// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Even and Odd Bits
//
// https://leetcode.com/problems/number-of-even-and-odd-bits/
//
// Question ID: 2595
// Difficult  : Easy
// Solve Date : 2023/05/06 14:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2595. Number of Even and Odd Bits|:
//
// You are given a positive integer |n|.
// Let |even| denote the number of even indices in the binary representation of
// |n| (0-indexed) with value |1|. Let |odd| denote the number of odd indices in
// the binary representation of |n| (0-indexed) with value |1|. Return an
// integer array |answer| where |answer = [even, odd]|.
//
//

LEETCODE_BEGIN_RESOLVING(2595, NumberOfEvenAndOddBits, Solution);

class Solution {
public:
  vector<int> evenOddBit(int n) {
    vector<int> res(2, 0);
    int         i = 0;
    while (n != 0) {
      if (n & 1) {
        ++res[i & 1];
      }
      n >>= 1;
      ++i;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 17
// Output: [2,0]
//
// The binary representation of 17 is 10001.
// It contains 1 on the 0ᵗʰ and 4ᵗʰ indices.
// There are 2 even and 0 odd indices.

LEETCODE_SOLUTION_UNITTEST(2595, NumberOfEvenAndOddBits, example_1) {
  auto        solution = MakeSolution();
  int         n        = 17;
  vector<int> expect   = {2, 0};
  vector<int> actual   = solution->evenOddBit(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: [0,1]
//
// The binary representation of 2 is 10.
// It contains 1 on the 1ˢᵗ index.
// There are 0 even and 1 odd indices.

LEETCODE_SOLUTION_UNITTEST(2595, NumberOfEvenAndOddBits, example_2) {
  auto        solution = MakeSolution();
  int         n        = 2;
  vector<int> expect   = {0, 1};
  vector<int> actual   = solution->evenOddBit(n);
  LCD_EXPECT_EQ(expect, actual);
}
