// Copyright 2023 Naon Lu
//
// This file describes the solution of
// K-th Symbol in Grammar
//
// https://leetcode.com/problems/k-th-symbol-in-grammar/
//
// Question ID: 779
// Difficult  : Medium
// Solve Date : 2022/03/09 18:07

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |779. K-th Symbol in Grammar|:
//
// We build a table of |n| rows (1-indexed). We start by writing |0| in the
// |1ˢᵗ| row. Now in every subsequent row, we look at the previous row and
// replace each occurrence of |0| with |01|, and each occurrence of |1| with
// |10|.
//
//  • For example, for |n = 3|, the |1ˢᵗ| row is |0|, the |2ⁿᵈ| row is |01|, and
//  the |3ʳᵈ| row is |0110|.
// Given two integer |n| and |k|, return the |kᵗʰ| (1-indexed) symbol in the
// |nᵗʰ| row of a table of |n| rows.  
//

LEETCODE_BEGIN_RESOLVING(779, KThSymbolInGrammar, Solution);

class Solution {
public:
  int kthGrammar(int n, int k) {
    if (n == 1)
      return 0;
    else if (k == 1)
      return 0;
    int x = kthGrammar(n - 1, (k + 1) / 2);
    return x == 0 ? (k & 1 ? 0 : 1) : (k & 1 ? 1 : 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 30|
// * |1 <= k <= 2^{n - 1}|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1, k = 1
// Output: 0
//
// row 1: 0

LEETCODE_SOLUTION_UNITTEST(779, KThSymbolInGrammar, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  k        = 1;
  int  expect   = 0;
  int  actual   = solution->kthGrammar(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, k = 1
// Output: 0
//
// row 1: 0
// row 2: 01

LEETCODE_SOLUTION_UNITTEST(779, KThSymbolInGrammar, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  k        = 1;
  int  expect   = 0;
  int  actual   = solution->kthGrammar(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2, k = 2
// Output: 1
//
// row 1: 0
// row 2: 01

LEETCODE_SOLUTION_UNITTEST(779, KThSymbolInGrammar, example_3) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  k        = 2;
  int  expect   = 1;
  int  actual   = solution->kthGrammar(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
