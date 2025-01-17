// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Neighboring Bitwise XOR
//
// https://leetcode.com/problems/neighboring-bitwise-xor/
//
// Question ID: 2683
// Difficult  : Medium
// Solve Date : 2025/01/17 22:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2683. Neighboring Bitwise XOR|:
//
// A 0-indexed array |derived| with length |n| is derived by computing the
// bitwise XOR (⊕) of adjacent values in a binary array |original| of length
// |n|. Specifically, for each index |i| in the range |[0, n - 1]|:
//
//  • If |i = n - 1|, then |derived[i] = original[i] ⊕ original[0]|.
//
//  • Otherwise, |derived[i] = original[i] ⊕ original[i + 1]|.
// Given an array |derived|, your task is to determine whether there exists a
// valid binary array |original| that could have formed |derived|. Return true
// if such an array exists or false otherwise.
//
//  • A binary array is an array containing only 0's and 1's
//
//

LEETCODE_BEGIN_RESOLVING(2683, NeighboringBitwiseXOR, Solution);

class Solution {
public:
  bool doesValidArrayExist(vector<int> &derived) {
    vector<int> original = {0};
    for (int i = 0; i < derived.size(); ++i) {
      original.emplace_back(derived[i] ^ original[i]);
    }
    bool zero = original[0] == original.back();
    original  = {1};
    for (int i = 0; i < derived.size(); ++i) {
      original.emplace_back(derived[i] ^ original[i]);
    }
    bool one = original[0] == original.back();
    return zero || one;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == derived.length|
// * |1 <= n <= 10⁵|
// * The values in |derived| are either 0's or 1's
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: derived = [1,1,0]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2683, NeighboringBitwiseXOR, example_1) {
  auto        solution = MakeSolution();
  vector<int> derived  = {1, 1, 0};
  bool        expect   = true;
  bool        actual   = solution->doesValidArrayExist(derived);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: derived = [1,1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2683, NeighboringBitwiseXOR, example_2) {
  auto        solution = MakeSolution();
  vector<int> derived  = {1, 1};
  bool        expect   = true;
  bool        actual   = solution->doesValidArrayExist(derived);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: derived = [1,0]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2683, NeighboringBitwiseXOR, example_3) {
  auto        solution = MakeSolution();
  vector<int> derived  = {1, 0};
  bool        expect   = false;
  bool        actual   = solution->doesValidArrayExist(derived);
  LCD_EXPECT_EQ(expect, actual);
}
