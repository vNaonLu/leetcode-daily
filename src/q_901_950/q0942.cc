// Copyright 2023 Naon Lu
//
// This file describes the solution of
// DI String Match
//
// https://leetcode.com/problems/di-string-match/
//
// Question ID: 942
// Difficult  : Easy
// Solve Date : 2023/07/19 20:05

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |942. DI String Match|:
//
// A permutation |perm| of |n + 1| integers of all the integers in the range
// |[0, n]| can be represented as a string |s| of length |n| where:
//
//  • |s[i] == 'I'| if |perm[i] < perm[i + 1]|, and
//
//  • |s[i] == 'D'| if |perm[i] > perm[i + 1]|.
// Given a string |s|, reconstruct the permutation |perm| and return it. If
// there are multiple valid permutations perm, return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(942, DIStringMatch, Solution);

class Solution {
public:
  vector<int> diStringMatch(string s) {
    vector<int> res;
    int         lo = 0;
    int         hi = s.size();
    for (auto c : s) {
      if (c == 'I') {
        res.emplace_back(lo++);
      } else {
        res.emplace_back(hi--);
      }
    }
    res.emplace_back(hi);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

namespace {

bool correct(const string &s, const vector<int> &ans) {
  if (ans.size() != s.size() + 1) {
    return false;
  }
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'I' && ans[i] >= ans[i + 1]) {
      return false;
    } else if (s[i] == 'D' && ans[i] <= ans[i + 1]) {
      return false;
    }
  }
  return true;
}

} // namespace

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s[i]| is either |'I'| or |'D'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "IDID"
// Output: [0,4,1,3,2]
//

LEETCODE_SOLUTION_UNITTEST(942, DIStringMatch, example_1) {
  auto   solution = MakeSolution();
  string s        = "IDID";
  // vector<int> expect   = {0, 4, 1, 3, 2};
  vector<int> actual = solution->diStringMatch(s);
  // LCD_EXPECT_EQ(expect, actual);
  EXPECT_TRUE(correct(s, actual));
}

// [Example #2]
//  Input: s = "III"
// Output: [0,1,2,3]
//

LEETCODE_SOLUTION_UNITTEST(942, DIStringMatch, example_2) {
  auto   solution = MakeSolution();
  string s        = "III";
  // vector<int> expect   = {0, 1, 2, 3};
  vector<int> actual = solution->diStringMatch(s);
  // LCD_EXPECT_EQ(expect, actual);
  EXPECT_TRUE(correct(s, actual));
}

// [Example #3]
//  Input: s = "DDI"
// Output: [3,2,0,1]
//

LEETCODE_SOLUTION_UNITTEST(942, DIStringMatch, example_3) {
  auto   solution = MakeSolution();
  string s        = "DDI";
  // vector<int> expect   = {3, 2, 0, 1};
  vector<int> actual = solution->diStringMatch(s);
  // LCD_EXPECT_EQ(expect, actual);
  EXPECT_TRUE(correct(s, actual));
}
