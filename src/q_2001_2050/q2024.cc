// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximize the Confusion of an Exam
//
// https://leetcode.com/problems/maximize-the-confusion-of-an-exam/
//
// Question ID: 2024
// Difficult  : Medium
// Solve Date : 2023/07/07 11:56

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2024. Maximize the Confusion of an Exam|:
//
// A teacher is writing a test with |n| true/false questions, with |'T'|
// denoting true and |'F'| denoting false. He wants to confuse the students by
// maximizing the number of consecutive questions with the same answer (multiple
// trues or multiple falses in a row). You are given a string |answerKey|, where
// |answerKey[i]| is the original answer to the |iᵗʰ| question. In addition, you
// are given an integer |k|, the maximum number of times you may perform the
// following operation:
//
//  • Change the answer key for any question to |'T'| or |'F'| (i.e., set
//  |answerKey[i]| to |'T'| or |'F'|).
// Return the maximum number of consecutive |'T'|s or |'F'|s in the answer key
// after performing the operation at most |k| times.
//
//

LEETCODE_BEGIN_RESOLVING(2024, MaximizeTheConfusionOfAnExam, Solution);

class Solution {
public:
  int maxConsecutiveAnswers(string answerKey, int k) {
    return max(solve(answerKey, k, 'T'), solve(answerKey, k, 'F'));
  }

private:
  int solve(string &s, int k, char repl) {
    auto lo       = s.begin();
    auto hi       = s.begin();
    int  res      = 0;
    int  repl_cnt = 0;
    while (hi != s.end()) {
      if (*hi++ != repl) {
        ++repl_cnt;
      }

      while (lo != s.end() && repl_cnt > k) {
        if (*lo++ != repl) {
          --repl_cnt;
        }
      }

      res = max<int>(res, distance(lo, hi));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == answerKey.length|
// * |1 <= n <= 5 * 10⁴|
// * |answerKey[i]| is either |'T'| or |'F'|
// * |1 <= k <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: answerKey = "TTFF", k = 2
// Output: 4
//
// We can replace both the 'F's with 'T's to make answerKey = "TTTT".
// There are four consecutive 'T's.

LEETCODE_SOLUTION_UNITTEST(2024, MaximizeTheConfusionOfAnExam, example_1) {
  auto   solution  = MakeSolution();
  string answerKey = "TTFF";
  int    k         = 2;
  int    expect    = 4;
  int    actual    = solution->maxConsecutiveAnswers(answerKey, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: answerKey = "TFFT", k = 1
// Output: 3
//
// We can replace the first 'T' with an 'F' to make answerKey = "FFFT".
// Alternatively, we can replace the second 'T' with an 'F' to make answerKey =
// "TFFF". In both cases, there are three consecutive 'F's.

LEETCODE_SOLUTION_UNITTEST(2024, MaximizeTheConfusionOfAnExam, example_2) {
  auto   solution  = MakeSolution();
  string answerKey = "TFFT";
  int    k         = 1;
  int    expect    = 3;
  int    actual    = solution->maxConsecutiveAnswers(answerKey, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: answerKey = "TTFTTFTT", k = 1
// Output: 5
//
// We can replace the first 'F' to make answerKey = "TTTTTFTT"
// Alternatively, we can replace the second 'F' to make answerKey = "TTFTTTTT".
// In both cases, there are five consecutive 'T's.

LEETCODE_SOLUTION_UNITTEST(2024, MaximizeTheConfusionOfAnExam, example_3) {
  auto   solution  = MakeSolution();
  string answerKey = "TTFTTFTT";
  int    k         = 1;
  int    expect    = 5;
  int    actual    = solution->maxConsecutiveAnswers(answerKey, k);
  LCD_EXPECT_EQ(expect, actual);
}
