// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Validate Stack Sequences
//
// https://leetcode.com/problems/validate-stack-sequences/
//
// Question ID: 946
// Difficult  : Medium
// Solve Date : 2021/10/13 12:55

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |946. Validate Stack Sequences|:
//
// Given two integer arrays |pushed| and |popped| each with distinct values,
// return |true| if this could have been the result of a sequence of push and
// pop operations on an initially empty stack, or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(946, ValidateStackSequences, Solution);

class Solution {
public:
  bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
    stack<int> test;
    int        pui = 0, poi = 0;
    while (pui < pushed.size() && poi < popped.size()) {
      if (!test.empty() && test.top() == popped[poi]) {
        test.pop();
        ++poi;
      } else {
        test.push(pushed[pui++]);
      }
    }
    while (!test.empty() && poi < popped.size()) {
      if (test.top() != popped[poi])
        return false;
      test.pop();
      ++poi;
    }
    return test.empty();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= pushed.length <= 1000|
// * |0 <= pushed[i] <= 1000|
// * All the elements of |pushed| are unique.
// * |popped.length == pushed.length|
// * |popped| is a permutation of |pushed|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
// Output: true
//
// We might do the following sequence:
// push(1), push(2), push(3), push(4),
// pop() -> 4,
// push(5),
// pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

LEETCODE_SOLUTION_UNITTEST(946, ValidateStackSequences, example_1) {
  auto        solution = MakeSolution();
  vector<int> pushed   = {1, 2, 3, 4, 5};
  vector<int> popped   = {4, 5, 3, 2, 1};
  bool        expect   = true;
  bool        actual   = solution->validateStackSequences(pushed, popped);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
// Output: false
//
// 1 cannot be popped before 2.

LEETCODE_SOLUTION_UNITTEST(946, ValidateStackSequences, example_2) {
  auto        solution = MakeSolution();
  vector<int> pushed   = {1, 2, 3, 4, 5};
  vector<int> popped   = {4, 3, 5, 1, 2};
  bool        expect   = false;
  bool        actual   = solution->validateStackSequences(pushed, popped);
  LCD_EXPECT_EQ(expect, actual);
}
