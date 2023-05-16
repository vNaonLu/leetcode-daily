// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Solving Questions With Brainpower
//
// https://leetcode.com/problems/solving-questions-with-brainpower/
//
// Question ID: 2140
// Difficult  : Medium
// Solve Date : 2023/05/12 11:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2140. Solving Questions With Brainpower|:
//
// You are given a 0-indexed 2D integer array |questions| where |questions[i] =
// [pointsᵢ, brainpowerᵢ]|. The array describes the questions of an exam, where
// you have to process the questions in order (i.e., starting from question |0|)
// and make a decision whether to solve or skip each question. Solving question
// |i| will earn you |pointsᵢ| points but you will be unable to solve each of
// the next |brainpowerᵢ| questions. If you skip question |i|, you get to make
// the decision on the next question.
//
//  • For example, given |questions = [[3, 2], [4, 3], [4, 4], [2, 5]]|:
//
//
//    • If question |0| is solved, you will earn |3| points but you will be
//    unable to solve questions |1| and |2|.
//
//    • If instead, question |0| is skipped and question |1| is solved, you will
//    earn |4| points but you will be unable to solve questions |2| and |3|.
//
//
// Return the maximum points you can earn for the exam.
//
//

LEETCODE_BEGIN_RESOLVING(2140, SolvingQuestionsWithBrainpower, Solution);

class Solution {
public:
  long long mostPoints(vector<vector<int>> &questions) {
    vector<int64_t> dp(questions.size() + 1, -1);
    return solve(questions, 0, dp);
  }

private:
  int64_t solve(vector<vector<int>> &q, int i, vector<int64_t> &dp) {
    if (i >= q.size())
      return 0;
    if (dp[i] != -1)
      return dp[i];
    int64_t skip = solve(q, i + 1, dp);
    int64_t take = q[i][0] + solve(q, i + q[i][1] + 1, dp);
    return dp[i] = max(skip, take);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= questions.length <= 10⁵|
// * |questions[i].length == 2|
// * |1 <= pointsᵢ, brainpowerᵢ <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: questions = [[3,2],[4,3],[4,4],[2,5]]
// Output: 5
//
// The maximum points can be earned by solving questions 0 and 3.
// - Solve question 0: Earn 3 points, will be unable to solve the next 2
// questions
// - Unable to solve questions 1 and 2
// - Solve question 3: Earn 2 points
// Total points earned: 3 + 2 = 5. There is no other way to earn 5 or more
// points.

LEETCODE_SOLUTION_UNITTEST(2140, SolvingQuestionsWithBrainpower, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> questions = {
      {3, 2},
      {4, 3},
      {4, 4},
      {2, 5}
  };
  long long expect = 5;
  long long actual = solution->mostPoints(questions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
// Output: 7
//
// The maximum points can be earned by solving questions 1 and 4.
// - Skip question 0
// - Solve question 1: Earn 2 points, will be unable to solve the next 2
// questions
// - Unable to solve questions 2 and 3
// - Solve question 4: Earn 5 points
// Total points earned: 2 + 5 = 7. There is no other way to earn 7 or more
// points.

LEETCODE_SOLUTION_UNITTEST(2140, SolvingQuestionsWithBrainpower, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> questions = {
      {1, 1},
      {2, 2},
      {3, 3},
      {4, 4},
      {5, 5}
  };
  long long expect = 7;
  long long actual = solution->mostPoints(questions);
  LCD_EXPECT_EQ(expect, actual);
}
