// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Reorder Data in Log Files
//
// https://leetcode.com/problems/reorder-data-in-log-files/
//
// Question ID: 937
// Difficult  : Medium
// Solve Date : 2024/09/21 16:33

#include <algorithm>
#include <cctype>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |937. Reorder Data in Log Files|:
//
// You are given an array of |logs|. Each log is a space-delimited string of
// words, where the first word is the identifier. There are two types of logs:
//
//  • Letter-logs: All words (except the identifier) consist of lowercase
//  English letters.
//
//  • Digit-logs: All words (except the identifier) consist of digits.
// Reorder these logs so that:
//
//  1. The letter-logs come before all digit-logs.
//
//  2. The letter-logs are sorted lexicographically by their contents. If their
//  contents are the same, then sort them lexicographically by their
//  identifiers.
//
//  3. The digit-logs maintain their relative ordering.
// Return the final order of the logs.
//
//

LEETCODE_BEGIN_RESOLVING(937, ReorderDataInLogFiles, Solution);

class Solution {
public:
  vector<string> reorderLogFiles(vector<string> &logs) {
    vector<string>               dig;
    vector<pair<string, string>> let;
    vector<string>               res;
    dig.reserve(logs.size());
    let.reserve(logs.size());
    res.reserve(logs.size());
    for (auto &s : logs) {
      auto fst = s.begin() + s.find(' ');
      if (isalpha(*(fst + 1))) {
        let.emplace_back(string(s.begin(), fst), string(fst + 1, s.end()));
      } else {
        dig.emplace_back(s);
      }
    }
    sort(let.begin(), let.end(), [](auto const &a, auto const &b) {
      return a.second == b.second ? a.first < b.first : a.second < b.second;
    });

    for (auto &[x, y] : let) {
      res.emplace_back(std::move(x) + " " + std::move(y));
    }
    for (auto &s : dig) {
      res.emplace_back(std::move(s));
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= logs.length <= 100|
// * |3 <= logs[i].length <= 100|
// * All the tokens of |logs[i]| are separated by a single space.
// * |logs[i]| is guaranteed to have an identifier and at least one word after
// the identifier.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit
//  dig","let3 art zero"]
// Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5
// 1","dig2 3 6"]
//

LEETCODE_SOLUTION_UNITTEST(937, ReorderDataInLogFiles, example_1) {
  auto           solution = MakeSolution();
  vector<string> logs     = {"dig1 8 1 5 1", "let1 art can", "dig2 3 6",
                             "let2 own kit dig", "let3 art zero"};
  vector<string> expect = {"let1 art can", "let3 art zero", "let2 own kit dig",
                           "dig1 8 1 5 1", "dig2 3 6"};
  vector<string> actual = solution->reorderLogFiles(logs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: logs = ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act
//  zoo"]
// Output: ["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]
//

LEETCODE_SOLUTION_UNITTEST(937, ReorderDataInLogFiles, example_2) {
  auto           solution = MakeSolution();
  vector<string> logs     = {"a1 9 2 3 1", "g1 act car", "zo4 4 7",
                             "ab1 off key dog", "a8 act zoo"};
  vector<string> expect   = {"g1 act car", "a8 act zoo", "ab1 off key dog",
                             "a1 9 2 3 1", "zo4 4 7"};
  vector<string> actual   = solution->reorderLogFiles(logs);
  LCD_EXPECT_EQ(expect, actual);
}
