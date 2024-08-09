// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Expressive Words
//
// https://leetcode.com/problems/expressive-words/
//
// Question ID: 809
// Difficult  : Medium
// Solve Date : 2024/08/03 15:34

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |809. Expressive Words|:
//
// Sometimes people repeat letters to represent extra feeling. For example:
//
//  • |"hello" -> "heeellooo"|
//
//  • |"hi" -> "hiiii"|
// In these strings like |"heeellooo"|, we have groups of adjacent letters that
// are all the same: |"h"|, |"eee"|, |"ll"|, |"ooo"|. You are given a string |s|
// and an array of query strings |words|. A query word is stretchy if it can be
// made to be equal to |s| by any number of applications of the following
// extension operation: choose a group consisting of characters |c|, and add
// some number of characters |c| to the group so that the size of the group is
// three or more.
//
//  • For example, starting with |"hello"|, we could do an extension on the
//  group |"o"| to get |"hellooo"|, but we cannot get |"helloo"| since the group
//  |"oo"| has a size less than three. Also, we could do another extension like
//  |"ll" -> "lllll"| to get |"helllllooo"|. If |s = "helllllooo"|, then the
//  query word |"hello"| would be stretchy because of these two extension
//  operations: |query = "hello" -> "hellooo" -> "helllllooo" = s|.
// Return the number of query strings that are stretchy.
//
//

LEETCODE_BEGIN_RESOLVING(809, ExpressiveWords, Solution);

class Solution {
public:
  int expressiveWords(string s, vector<string> &words) {
    int res = 0;
    for (auto &w : words) {
      if (check(s, w)) {
        ++res;
      }
    }
    return res;
  }

private:
  bool check(string const &s, string const &w) {
    int n = s.size();
    int m = w.size();
    int j = 0;
    for (int i = 0; i < n; i++) {
      if (j < m && s[i] == w[j])
        j++;
      else if (i > 1 && s[i - 2] == s[i - 1] && s[i - 1] == s[i])
        ;
      else if (0 < i && i < n - 1 && s[i - 1] == s[i] && s[i] == s[i + 1])
        ;
      else
        return false;
    }
    return j == m;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length, words.length <= 100|
// * |1 <= words[i].length <= 100|
// * |s| and |words[i]| consist of lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "heeellooo", words = ["hello", "hi", "helo"]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(809, ExpressiveWords, example_1) {
  auto           solution = MakeSolution();
  string         s        = "heeellooo";
  vector<string> words    = {"hello", "hi", "helo"};
  int            expect   = 1;
  int            actual   = solution->expressiveWords(s, words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "zzzzzyyyyy", words = ["zzyy","zy","zyy"]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(809, ExpressiveWords, example_2) {
  auto           solution = MakeSolution();
  string         s        = "zzzzzyyyyy";
  vector<string> words    = {"zzyy", "zy", "zyy"};
  int            expect   = 3;
  int            actual   = solution->expressiveWords(s, words);
  LCD_EXPECT_EQ(expect, actual);
}
