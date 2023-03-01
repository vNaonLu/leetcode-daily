// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Letter Case Permutation
//
// https://leetcode.com/problems/letter-case-permutation/
//
// Question ID: 784
// Difficult  : Medium
// Solve Date : 2021/09/15 08:00

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |784. Letter Case Permutation|:
//
// Given a string |s|, you can transform every letter individually to be
// lowercase or uppercase to create another string. Return a list of all
// possible strings we could create. Return the output in any order.  
//

LEETCODE_BEGIN_RESOLVING(784, LetterCasePermutation, Solution);

class Solution {
private:
  bool isLetter(const char &c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }
  string helper(string s, vector<int> &l, int c) {
    for (int i = 0; i < l.size(); ++i) {
      auto bit = 1 << i;
      s[l[i]]  = bit & c ? toupper(s[l[i]]) : tolower(s[l[i]]);
    }
    return s;
  }

public:
  vector<string> letterCasePermutation(string s) {
    vector<string> res;
    vector<int>    letters;
    for (int i = 0; i < s.size(); ++i)
      if (isLetter(s[i]))
        letters.push_back(i);
    for (int i = 0; i < (1 << letters.size()); ++i) {
      res.emplace_back(helper(s, letters, i));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 12|
// * |s| consists of lowercase English letters, uppercase English letters, and
// digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "a1b2"
// Output: ["a1b2","a1B2","A1b2","A1B2"]
//

LEETCODE_SOLUTION_UNITTEST(784, LetterCasePermutation, example_1) {
  auto           solution = MakeSolution();
  string         s        = "a1b2";
  vector<string> expect   = {"a1b2", "a1B2", "A1b2", "A1B2"};
  vector<string> actual   = solution->letterCasePermutation(s);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "3z4"
// Output: ["3z4","3Z4"]
//

LEETCODE_SOLUTION_UNITTEST(784, LetterCasePermutation, example_2) {
  auto           solution = MakeSolution();
  string         s        = "3z4";
  vector<string> expect   = {"3z4", "3Z4"};
  vector<string> actual   = solution->letterCasePermutation(s);
  EXPECT_ANYORDER_EQ(expect, actual);
}
