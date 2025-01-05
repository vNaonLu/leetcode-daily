// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Shifting Letters II
//
// https://leetcode.com/problems/shifting-letters-ii/
//
// Question ID: 2381
// Difficult  : Medium
// Solve Date : 2025/01/05 14:23

#include <iosfwd>
#include <numeric>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2381. Shifting Letters II|:
//
// You are given a string |s| of lowercase English letters and a 2D integer
// array |shifts| where |shifts[i] = [startᵢ, endᵢ, directionᵢ]|. For every |i|,
// shift the characters in |s| from the index |startᵢ| to the index |endᵢ|
// (inclusive) forward if |directionᵢ = 1|, or shift the characters backward if
// |directionᵢ = 0|. Shifting a character forward means replacing it with the
// next letter in the alphabet (wrapping around so that |'z'| becomes |'a'|).
// Similarly, shifting a character backward means replacing it with the previous
// letter in the alphabet (wrapping around so that |'a'| becomes |'z'|). Return
// the final string after all such shifts to |s| are applied.
//
//

LEETCODE_BEGIN_RESOLVING(2381, ShiftingLettersII, Solution);

class Solution {
public:
  string shiftingLetters(string s, vector<vector<int>> &shifts) {
    int         n = s.size();
    vector<int> apply(n + 1, 0);
    for (auto &v : shifts) {
      int s = v[0];
      int e = v[1] + 1;
      int d = v[2] == 1 ? 1 : -1;
      apply[s] += d;
      apply[e] -= d;
    }
    partial_sum(apply.begin(), apply.end(), apply.begin());
    for (int i = 0; i < n; ++i) {
      auto &c = s[i];
      c       = (apply[i] + c - 'a') % 26 + 'a';
      if (c < 'a') {
        c += 26;
      }
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length, shifts.length <= 5 * 10⁴|
// * |shifts[i].length == 3|
// * |0 <= startᵢ <= endᵢ < s.length|
// * |0 <= directionᵢ <= 1|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
// Output: "ace"
//

LEETCODE_SOLUTION_UNITTEST(2381, ShiftingLettersII, example_1) {
  auto                solution = MakeSolution();
  string              s        = "abc";
  vector<vector<int>> shifts   = {
      {0, 1, 0},
      {1, 2, 1},
      {0, 2, 1}
  };
  string expect = "ace";
  string actual = solution->shiftingLetters(s, shifts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
// Output: "catz"
//

LEETCODE_SOLUTION_UNITTEST(2381, ShiftingLettersII, example_2) {
  auto                solution = MakeSolution();
  string              s        = "dztz";
  vector<vector<int>> shifts   = {
      {0, 0, 0},
      {1, 1, 1}
  };
  string expect = "catz";
  string actual = solution->shiftingLetters(s, shifts);
  LCD_EXPECT_EQ(expect, actual);
}
