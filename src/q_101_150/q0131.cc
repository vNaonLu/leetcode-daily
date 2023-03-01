// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Palindrome Partitioning
//
// https://leetcode.com/problems/palindrome-partitioning/
//
// Question ID: 131
// Difficult  : Medium
// Solve Date : 2022/01/05 18:18

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |131. Palindrome Partitioning|:
//
// Given a string |s|, partition |s| such that every substring of the partition
// is a palindrome. Return all possible palindrome partitioning of |s|.  
//

LEETCODE_BEGIN_RESOLVING(131, PalindromePartitioning, Solution);

class Solution {
private:
  inline bool is_palindrome(const string &s, size_t l, size_t r) {
    while (l < r)
      if (s[l++] != s[r--])
        return false;
    return true;
  }

  inline void dfs(vector<vector<string>> &res, const string &s, size_t beg,
                  vector<string> &current) {
    if (beg >= s.size())
      res.push_back(current);
    for (size_t R = beg; R < s.size(); ++R) {
      if (is_palindrome(s, beg, R)) {
        current.emplace_back(s.substr(beg, R - beg + 1));
        dfs(res, s, R + 1, current);
        current.pop_back();
      }
    }
  }

public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string>         tmp;
    dfs(res, s, 0, tmp);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 16|
// * |s| contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aab"
// Output: [["a","a","b"],["aa","b"]]
//

LEETCODE_SOLUTION_UNITTEST(131, PalindromePartitioning, example_1) {
  auto                   solution = MakeSolution();
  string                 s        = "aab";
  vector<vector<string>> expect   = {
      {"a", "a", "b"},
      {"aa", "b"}
  };
  vector<vector<string>> actual = solution->partition(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "a"
// Output: [["a"]]
//

LEETCODE_SOLUTION_UNITTEST(131, PalindromePartitioning, example_2) {
  auto                   solution = MakeSolution();
  string                 s        = "a";
  vector<vector<string>> expect   = {{"a"}};
  vector<vector<string>> actual   = solution->partition(s);
  LCD_EXPECT_EQ(expect, actual);
}
