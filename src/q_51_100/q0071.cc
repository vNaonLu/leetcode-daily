// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Simplify Path
//
// https://leetcode.com/problems/simplify-path/
//
// Question ID: 71
// Difficult  : Medium
// Solve Date : 2022/03/14 18:29

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |71. Simplify Path|:
//
// Given a string |path|, which is an absolute path (starting with a slash
// |'/'|) to a file or directory in a Unix-style file system, convert it to the
// simplified canonical path. In a Unix-style file system, a period |'.'| refers
// to the current directory, a double period |'..'| refers to the directory up a
// level, and any multiple consecutive slashes (i.e. |'//'|) are treated as a
// single slash |'/'|. For this problem, any other format of periods such as
// |'...'| are treated as file/directory names. The canonical path should have
// the following format:
//
//  • The path starts with a single slash |'/'|.
//
//  • Any two directories are separated by a single slash |'/'|.
//
//  • The path does not end with a trailing |'/'|.
//
//  • The path only contains the directories on the path from the root directory
//  to the target file or directory (i.e., no period |'.'| or double period
//  |'..'|)
// Return the simplified canonical path.
//  
//

LEETCODE_BEGIN_RESOLVING(71, SimplifyPath, Solution);

class Solution {
private:
  string join(stack<string> &stk) {
    stack<string> p;
    while (!stk.empty()) {
      p.emplace(move(stk.top()));
      stk.pop();
    }

    string res;
    while (!p.empty()) {
      res += "/";
      res += p.top();
      p.pop();
    }

    return res.empty() ? "/" : res;
  }

  void push(stack<string> &s, string &curr) {
    if (curr == "..") {
      if (!s.empty()) {
        s.pop();
      }
    } else if (curr != "." && !curr.empty()) {
      s.emplace(move(curr));
    }
    curr.clear();
  }

public:
  string simplifyPath(string path) {
    stack<string> pathes;
    string        curr;

    for (auto it = path.begin(); it != path.end(); ++it) {
      if (*it == '/') {
        push(pathes, curr);
      } else {
        curr.push_back(*it);
      }
    }
    push(pathes, curr);

    return join(pathes);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= path.length <= 3000|
// * |path| consists of English letters, digits, period |'.'|, slash |'/'| or
// |'_'|.
// * |path| is a valid absolute Unix path.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: path = "/home/"
// Output: "/home"
//
// Note that there is no trailing slash after the last directory name.

LEETCODE_SOLUTION_UNITTEST(71, SimplifyPath, example_1) {
  auto   solution = MakeSolution();
  string path     = "/home/";
  string expect   = "/home";
  string actual   = solution->simplifyPath(path);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: path = "/../"
// Output: "/"
//
// Going one level up from the root directory is a no-op, as the root level is
// the highest level you can go.

LEETCODE_SOLUTION_UNITTEST(71, SimplifyPath, example_2) {
  auto   solution = MakeSolution();
  string path     = "/../";
  string expect   = "/";
  string actual   = solution->simplifyPath(path);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: path = "/home//foo/"
// Output: "/home/foo"
//
// In the canonical path, multiple consecutive slashes are replaced by a single
// one.

LEETCODE_SOLUTION_UNITTEST(71, SimplifyPath, example_3) {
  auto   solution = MakeSolution();
  string path     = "/home//foo/";
  string expect   = "/home/foo";
  string actual   = solution->simplifyPath(path);
  LCD_EXPECT_EQ(expect, actual);
}
