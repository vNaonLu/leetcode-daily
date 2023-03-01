// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Baseball Game
//
// https://leetcode.com/problems/baseball-game/
//
// Question ID: 682
// Difficult  : Easy
// Solve Date : 2022/04/10 13:59

#include <iosfwd>
#include <stack>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |682. Baseball Game|:
//
// You are keeping the scores for a baseball game with strange rules. At the
// beginning of the game, you start with an empty record. You are given a list
// of strings |operations|, where |operations[i]| is the |iᵗʰ| operation you
// must apply to the record and is one of the following:
//
//  • An integer |x|.
//
//
//    • Record a new score of |x|.
//
//
//
//  • |'+'|.
//
//
//    • Record a new score that is the sum of the previous two scores.
//
//
//
//  • |'D'|.
//
//
//    • Record a new score that is the double of the previous score.
//
//
//
//  • |'C'|.
//
//
//    • Invalidate the previous score, removing it from the record.
//
//
// Return the sum of all the scores on the record after applying all the
// operations. The test cases are generated such that the answer and all
// intermediate calculations fit in a 32-bit integer and that all operations are
// valid.  
//

LEETCODE_BEGIN_RESOLVING(682, BaseballGame, Solution);

class Solution {
public:
  int calPoints(vector<string> &ops) {
    int        sum = 0;
    stack<int> scores;

    for (auto &s : ops) {
      if (s == "D") {
        sum += scores.top() * 2;
        scores.emplace(scores.top() * 2);
      } else if (s == "C") {
        sum -= scores.top();
        scores.pop();
      } else if (s == "+") {
        auto x = scores.top();
        scores.pop();
        auto y = scores.top();
        scores.emplace(x);
        scores.emplace(x + y);
        sum += x + y;
      } else {
        auto x = stoi(s);
        sum += x;
        scores.emplace(x);
      }
    }

    return sum;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= operations.length <= 1000|
// * |operations[i]| is |"C"|, |"D"|, |"+"|, or a string representing an integer
// in the range |[-3 * 10⁴, 3 * 10⁴]|.
// * For operation |"+"|, there will always be at least two previous scores on
// the record.
// * For operations |"C"| and |"D"|, there will always be at least one previous
// score on the record.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ops = ["5","2","C","D","+"]
// Output: 30
//
// "5" - Add 5 to the record, record is now [5].
// "2" - Add 2 to the record, record is now [5, 2].
// "C" - Invalidate and remove the previous score, record is now [5].
// "D" - Add 2 * 5 = 10 to the record, record is now [5, 10].
// "+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
// The total sum is 5 + 10 + 15 = 30.

LEETCODE_SOLUTION_UNITTEST(682, BaseballGame, example_1) {
  auto           solution = MakeSolution();
  vector<string> ops      = {"5", "2", "C", "D", "+"};
  int            expect   = 30;
  int            actual   = solution->calPoints(ops);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ops = ["5","-2","4","C","D","9","+","+"]
// Output: 27
//
// "5" - Add 5 to the record, record is now [5].
// "-2" - Add -2 to the record, record is now [5, -2].
// "4" - Add 4 to the record, record is now [5, -2, 4].
// "C" - Invalidate and remove the previous score, record is now [5, -2].
// "D" - Add 2 * -2 = -4 to the record, record is now [5, -2, -4].
// "9" - Add 9 to the record, record is now [5, -2, -4, 9].
// "+" - Add -4 + 9 = 5 to the record, record is now [5, -2, -4, 9, 5].
// "+" - Add 9 + 5 = 14 to the record, record is now [5, -2, -4, 9, 5, 14].
// The total sum is 5 + -2 + -4 + 9 + 5 + 14 = 27.

LEETCODE_SOLUTION_UNITTEST(682, BaseballGame, example_2) {
  auto           solution = MakeSolution();
  vector<string> ops      = {"5", "-2", "4", "C", "D", "9", "+", "+"};
  int            expect   = 27;
  int            actual   = solution->calPoints(ops);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: ops = ["1","C"]
// Output: 0
//
// "1" - Add 1 to the record, record is now [1].
// "C" - Invalidate and remove the previous score, record is now [].
// Since the record is empty, the total sum is 0.

LEETCODE_SOLUTION_UNITTEST(682, BaseballGame, example_3) {
  auto           solution = MakeSolution();
  vector<string> ops      = {"1"};
  int            expect   = 1;
  int            actual   = solution->calPoints(ops);
  LCD_EXPECT_EQ(expect, actual);
}
