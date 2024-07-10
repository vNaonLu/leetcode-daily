// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Rabbits in Forest
//
// https://leetcode.com/problems/rabbits-in-forest/
//
// Question ID: 781
// Difficult  : Medium
// Solve Date : 2024/07/02 19:56

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |781. Rabbits in Forest|:
//
// There is a forest with an unknown number of rabbits. We asked n rabbits "How
// many rabbits have the same color as you?" and collected the answers in an
// integer array |answers| where |answers[i]| is the answer of the |iᵗʰ| rabbit.
// Given the array |answers|, return the minimum number of rabbits that could be
// in the forest.
//
//

LEETCODE_BEGIN_RESOLVING(781, RabbitsInForest, Solution);

class Solution {
public:
  int numRabbits(vector<int> &answers) {
    sort(answers.begin(), answers.end());
    int cnt = 1;
    int ext = 0;
    for (int i = 0; i < answers.size(); ++i) {
      if (i == answers.size() - 1 || answers[i] != answers[i + 1]) {
        int mod = cnt % (answers[i] + 1);
        if (mod) {
          ext += (answers[i] + 1 - mod);
        }
        cnt = 1;
      } else {
        ++cnt;
      }
    }
    return answers.size() + ext;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= answers.length <= 1000|
// * |0 <= answers[i] < 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: answers = [1,1,2]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(781, RabbitsInForest, example_1) {
  auto        solution = MakeSolution();
  vector<int> answers  = {1, 1, 2};
  int         expect   = 5;
  int         actual   = solution->numRabbits(answers);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: answers = [10,10,10]
// Output: 11
//

LEETCODE_SOLUTION_UNITTEST(781, RabbitsInForest, example_2) {
  auto        solution = MakeSolution();
  vector<int> answers  = {10, 10, 10};
  int         expect   = 11;
  int         actual   = solution->numRabbits(answers);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [0,0,1,1,1]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(781, RabbitsInForest, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> answers  = {0, 0, 1, 1, 1};
  int         expect   = 6;
  int         actual   = solution->numRabbits(answers);
  LCD_EXPECT_EQ(expect, actual);
}
