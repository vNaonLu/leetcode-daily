// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Crawler Log Folder
//
// https://leetcode.com/problems/crawler-log-folder/
//
// Question ID: 1598
// Difficult  : Easy
// Solve Date : 2023/03/23 23:23

#include <iosfwd>
#include <stack>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1598. Crawler Log Folder|:
//
// The Leetcode file system keeps a log each time some user performs a change
// folder operation. The operations are described below:
//
//  • |"../"| : Move to the parent folder of the current folder. (If you are
//  already in the main folder, remain in the same folder).
//
//  • |"./"| : Remain in the same folder.
//
//  • |"x/"| : Move to the child folder named |x| (This folder is guaranteed to
//  always exist).
// You are given a list of strings |logs| where |logs[i]| is the operation
// performed by the user at the |iᵗʰ| step. The file system starts in the main
// folder, then the operations in |logs| are performed. Return the minimum
// number of operations needed to go back to the main folder after the change
// folder operations.
//
//

LEETCODE_BEGIN_RESOLVING(1598, CrawlerLogFolder, Solution);

class Solution {
public:
  int minOperations(vector<string> &logs) {
    stack<string> path;
    for (auto &s : logs) {
      if (s[0] == '.' && s[1] == '.') {
        if (!path.empty()) {
          path.pop();
        }
      } else if (s.size() > 2 || s[0] != '.') {
        path.emplace(std::move(s));
      }
    }
    return path.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= logs.length <= 10³|
// * |2 <= logs[i].length <= 10|
// * |logs[i]| contains lowercase English letters, digits, |'.'|, and |'/'|.
// * |logs[i]| follows the format described in the statement.
// * Folder names consist of lowercase English letters and digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: logs = ["d1/","d2/","../","d21/","./"]
// Output: 2
//
// Use this change folder operation "../" 2 times and go back to the main
// folder.

LEETCODE_SOLUTION_UNITTEST(1598, CrawlerLogFolder, example_1) {
  auto           solution = MakeSolution();
  vector<string> logs     = {"d1/", "d2/", "../", "d21/", "./"};
  int            expect   = 2;
  int            actual   = solution->minOperations(logs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: logs = ["d1/","d2/","./","d3/","../","d31/"]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1598, CrawlerLogFolder, example_2) {
  auto           solution = MakeSolution();
  vector<string> logs     = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
  int            expect   = 3;
  int            actual   = solution->minOperations(logs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: logs = ["d1/","../","../","../"]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1598, CrawlerLogFolder, example_3) {
  auto           solution = MakeSolution();
  vector<string> logs     = {"d1/", "../", "../", "../"};
  int            expect   = 0;
  int            actual   = solution->minOperations(logs);
  LCD_EXPECT_EQ(expect, actual);
}
