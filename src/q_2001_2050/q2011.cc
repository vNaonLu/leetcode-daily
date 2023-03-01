// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Final Value of Variable After Performing Operations
//
// https://leetcode.com/problems/final-value-of-variable-after-performing-operations/
//
// Question ID: 2011
// Difficult  : Easy
// Solve Date : 2021/11/23 18:44

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2011. Final Value of Variable After Performing Operations|:
//
// There is a programming language with only four operations and one variable
// |X|:
//
//  • |++X| and |X++| increments the value of the variable |X| by |1|.
//
//  • |--X| and |X--| decrements the value of the variable |X| by |1|.
// Initially, the value of |X| is |0|.
// Given an array of strings |operations| containing a list of operations,
// return the final value of |X| after performing all the operations.  
//

LEETCODE_BEGIN_RESOLVING(2011, FinalValueOfVariableAfterPerformingOperations,
                         Solution);

class Solution {
public:
  int finalValueAfterOperations(vector<string> &operations) {
    int res = 0;
    for (const string &s : operations) {
      switch (s[1]) {
      case '+':
        ++res;
        break;
      case '-':
        --res;
        break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= operations.length <= 100|
// * |operations[i]| will be either |"++X"|, |"X++"|, |"--X"|, or |"X--"|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: operations = ["--X","X++","X++"]
// Output: 1
//
//  The operations are performed as follows:
// Initially, X = 0.
// --X: X is decremented by 1, X = 0 - 1 = -1.
// X++: X is incremented by 1, X = -1 + 1 = 0.
// X++: X is incremented by 1, X = 0 + 1 = 1.

LEETCODE_SOLUTION_UNITTEST(2011, FinalValueOfVariableAfterPerformingOperations,
                           example_1) {
  auto           solution   = MakeSolution();
  vector<string> operations = {"--X", "X++", "X++"};
  int            expect     = 1;
  int            actual     = solution->finalValueAfterOperations(operations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: operations = ["++X","++X","X++"]
// Output: 3
//
// The operations are performed as follows:
// Initially, X = 0.
// ++X: X is incremented by 1, X = 0 + 1 = 1.
// ++X: X is incremented by 1, X = 1 + 1 = 2.
// X++: X is incremented by 1, X = 2 + 1 = 3.

LEETCODE_SOLUTION_UNITTEST(2011, FinalValueOfVariableAfterPerformingOperations,
                           example_2) {
  auto           solution   = MakeSolution();
  vector<string> operations = {"++X", "++X", "X++"};
  int            expect     = 3;
  int            actual     = solution->finalValueAfterOperations(operations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: operations = ["X++","++X","--X","X--"]
// Output: 0
//
//  The operations are performed as follows:
// Initially, X = 0.
// X++: X is incremented by 1, X = 0 + 1 = 1.
// ++X: X is incremented by 1, X = 1 + 1 = 2.
// --X: X is decremented by 1, X = 2 - 1 = 1.
// X--: X is decremented by 1, X = 1 - 1 = 0.

LEETCODE_SOLUTION_UNITTEST(2011, FinalValueOfVariableAfterPerformingOperations,
                           example_3) {
  auto           solution   = MakeSolution();
  vector<string> operations = {"X++", "++X", "--X", "X--"};
  int            expect     = 0;
  int            actual     = solution->finalValueAfterOperations(operations);
  LCD_EXPECT_EQ(expect, actual);
}
