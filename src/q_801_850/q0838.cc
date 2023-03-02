// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Push Dominoes
//
// https://leetcode.com/problems/push-dominoes/
//
// Question ID: 838
// Difficult  : Medium
// Solve Date : 2022/09/27 18:43

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |838. Push Dominoes|:
//
// There are |n| dominoes in a line, and we place each domino vertically
// upright. In the beginning, we simultaneously push some of the dominoes either
// to the left or to the right. After each second, each domino that is falling
// to the left pushes the adjacent domino on the left. Similarly, the dominoes
// falling to the right push their adjacent dominoes standing on the right. When
// a vertical domino has dominoes falling on it from both sides, it stays still
// due to the balance of the forces. For the purposes of this question, we will
// consider that a falling domino expends no additional force to a falling or
// already fallen domino. You are given a string |dominoes| representing the
// initial state where:
//
//  • |dominoes[i] = 'L'|, if the |iᵗʰ| domino has been pushed to the left,
//
//  • |dominoes[i] = 'R'|, if the |iᵗʰ| domino has been pushed to the right, and
//
//  • |dominoes[i] = '.'|, if the |iᵗʰ| domino has not been pushed.
// Return a string representing the final state.
//

LEETCODE_BEGIN_RESOLVING(838, PushDominoes, Solution);

class Solution {
public:
  string pushDominoes(string dominoes) {
    auto res = string("");
    auto f   = vector<int>(dominoes.size(), 0);
    auto fs  = (int)0;
    for (int i = 0; i < f.size(); ++i) {
      if (dominoes[i] == 'R') {
        fs = dominoes.size();
      } else if (dominoes[i] == 'L') {
        fs = 0;
      } else {
        --fs;
        fs = max(0, fs);
      }
      f[i] += fs;
    }
    fs = 0;
    for (int i = f.size() - 1; i >= 0; --i) {
      if (dominoes[i] == 'L') {
        fs = dominoes.size();
      } else if (dominoes[i] == 'R') {
        fs = 0;
      } else {
        --fs;
        fs = max(0, fs);
      }
      f[i] -= fs;
    }
    for (auto c : f) {
      res.push_back(c == 0 ? '.' : c > 0 ? 'R' : 'L');
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == dominoes.length|
// * |1 <= n <= 10⁵|
// * |dominoes[i]| is either |'L'|, |'R'|, or |'.'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: dominoes = "RR.L"
// Output: "RR.L"
//
// The first domino expends no additional force on the second domino.

LEETCODE_SOLUTION_UNITTEST(838, PushDominoes, example_1) {
  auto   solution = MakeSolution();
  string dominoes = "RR.L";
  string expect   = "RR.L";
  string actual   = solution->pushDominoes(dominoes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: dominoes = ".L.R...LR..L.."
// Output: "LL.RR.LLRRLL.."
//

LEETCODE_SOLUTION_UNITTEST(838, PushDominoes, example_2) {
  auto   solution = MakeSolution();
  string dominoes = ".L.R...LR..L..";
  string expect   = "LL.RR.LLRRLL..";
  string actual   = solution->pushDominoes(dominoes);
  LCD_EXPECT_EQ(expect, actual);
}
