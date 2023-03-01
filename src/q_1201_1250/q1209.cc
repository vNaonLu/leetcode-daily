// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove All Adjacent Duplicates in String II
//
// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
//
// Question ID: 1209
// Difficult  : Medium
// Solve Date : 2022/05/06 18:29

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1209. Remove All Adjacent Duplicates in String II|:
//
// You are given a string |s| and an integer |k|, a |k| duplicate removal
// consists of choosing |k| adjacent and equal letters from |s| and removing
// them, causing the left and the right side of the deleted substring to
// concatenate together. We repeatedly make |k| duplicate removals on |s| until
// we no longer can. Return the final string after all such duplicate removals
// have been made. It is guaranteed that the answer is unique.  
//

LEETCODE_BEGIN_RESOLVING(1209, RemoveAllAdjacentDuplicatesInStringII, Solution);

class Solution {
public:
  string removeDuplicates(string s, int k) {
    int n = s.size();
    if (n < k)
      return s;

    stack<pair<char, int>> stk;
    for (int i = 0; i < n; ++i) {
      if (stk.empty() || stk.top().first != s[i])
        stk.push({s[i], 1});
      else {
        auto prev = stk.top();
        stk.pop();
        stk.push({s[i], prev.second + 1});
      }
      if (stk.top().second == k)
        stk.pop();
    }

    string res = "";
    while (!stk.empty()) {
      auto cur = stk.top();
      stk.pop();
      while (cur.second--) {
        res.push_back(cur.first);
      }
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |2 <= k <= 10⁴|
// * |s| only contains lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcd", k = 2
// Output: "abcd"
//
// There's nothing to delete.

LEETCODE_SOLUTION_UNITTEST(1209, RemoveAllAdjacentDuplicatesInStringII,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  int    k        = 2;
  string expect   = "abcd";
  string actual   = solution->removeDuplicates(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "deeedbbcccbdaa", k = 3
// Output: "aa"
// Explanation:
// First delete "eee" and "ccc", get "ddbbbdaa"
// Then delete "bbb", get "dddaa"
// Finally delete "ddd", get "aa"
//

LEETCODE_SOLUTION_UNITTEST(1209, RemoveAllAdjacentDuplicatesInStringII,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "deeedbbcccbdaa";
  int    k        = 3;
  string expect   = "aa";
  string actual   = solution->removeDuplicates(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "pbbcggttciiippooaais", k = 2
// Output: "ps"
//

LEETCODE_SOLUTION_UNITTEST(1209, RemoveAllAdjacentDuplicatesInStringII,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "pbbcggttciiippooaais";
  int    k        = 2;
  string expect   = "ps";
  string actual   = solution->removeDuplicates(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
