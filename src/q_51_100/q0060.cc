// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Permutation Sequence
//
// https://leetcode.com/problems/permutation-sequence/
//
// Question ID: 60
// Difficult  : Hard
// Solve Date : 2022/01/26 00:27

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |60. Permutation Sequence|:
//
// The set |[1, 2, 3, ..., n]| contains a total of |n!| unique permutations.
// By listing and labeling all of the permutations in order, we get the
// following sequence for |n = 3|:
//
//  1. |"123"|
//
//  2. |"132"|
//
//  3. |"213"|
//
//  4. |"231"|
//
//  5. |"312"|
//
//  6. |"321"|
// Given |n| and |k|, return the |kᵗʰ| permutation sequence.
//  
//

LEETCODE_BEGIN_RESOLVING(60, PermutationSequence, Solution);

class Solution {
public:
  string getPermutation(int n, int k) {
    string      raw = "123456789";
    string      res;
    vector<int> step_table(n, 1);
    for (int i = 1; i < n; ++i)
      step_table[i] = step_table[i - 1] * i;
    --k;
    for (int i = n - 1; i >= 0; --i) {
      int idx = k / step_table[i];
      k %= step_table[i];
      res.push_back(raw[idx]);
      raw.erase(raw.begin() + idx);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 9|
// * |1 <= k <= n!|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 3
// Output: "213"
//

LEETCODE_SOLUTION_UNITTEST(60, PermutationSequence, example_1) {
  auto   solution = MakeSolution();
  int    n        = 3;
  int    k        = 3;
  string expect   = "213";
  string actual   = solution->getPermutation(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, k = 9
// Output: "2314"
//

LEETCODE_SOLUTION_UNITTEST(60, PermutationSequence, example_2) {
  auto   solution = MakeSolution();
  int    n        = 4;
  int    k        = 9;
  string expect   = "2314";
  string actual   = solution->getPermutation(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3, k = 1
// Output: "123"
//

LEETCODE_SOLUTION_UNITTEST(60, PermutationSequence, example_3) {
  auto   solution = MakeSolution();
  int    n        = 3;
  int    k        = 1;
  string expect   = "123";
  string actual   = solution->getPermutation(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
