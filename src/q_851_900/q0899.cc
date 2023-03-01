// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Orderly Queue
//
// https://leetcode.com/problems/orderly-queue/
//
// Question ID: 899
// Difficult  : Hard
// Solve Date : 2022/11/06 14:21

#include <algorithm>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |899. Orderly Queue|:
//
// You are given a string |s| and an integer |k|. You can choose one of the
// first |k| letters of |s| and append it at the end of the string.. Return the
// lexicographically smallest string you could have after applying the mentioned
// step any number of moves.
//

LEETCODE_BEGIN_RESOLVING(899, OrderlyQueue, Solution);

class Solution {
public:
  string orderlyQueue(string s, int k) {
    if (k == 1) {
      s.reserve(s.size() * 2);
      auto res = string_view(s);
      s += s;
      auto sv = string_view(s);
      for (int i = 0; i < res.size(); ++i) {
        res = min(res, sv.substr(i, res.size()));
      }
      return string(res);
    }
    sort(s.begin(), s.end());
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= s.length <= 1000|
// * |s| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "cba", k = 1
// Output: "acb"
//
// In the first move, we move the 1ˢᵗ character 'c' to the end, obtaining the
// string "bac". In the second move, we move the 1ˢᵗ character 'b' to the end,
// obtaining the final result "acb".

LEETCODE_SOLUTION_UNITTEST(899, OrderlyQueue, example_1) {
  auto   solution = MakeSolution();
  string s        = "cba";
  int    k        = 1;
  string expect   = "acb";
  string actual   = solution->orderlyQueue(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "baaca", k = 3
// Output: "aaabc"
//
// In the first move, we move the 1ˢᵗ character 'b' to the end, obtaining the
// string "aacab". In the second move, we move the 3ʳᵈ character 'c' to the end,
// obtaining the final result "aaabc".

LEETCODE_SOLUTION_UNITTEST(899, OrderlyQueue, example_2) {
  auto   solution = MakeSolution();
  string s        = "baaca";
  int    k        = 3;
  string expect   = "aaabc";
  string actual   = solution->orderlyQueue(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
