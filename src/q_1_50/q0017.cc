// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Letter Combinations of a Phone Number
//
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
//
// Question ID: 17
// Difficult  : Medium
// Solve Date : 2021/09/29 13:05

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |17. Letter Combinations of a Phone Number|:
//
// Given a string containing digits from |2-9| inclusive, return all possible
// letter combinations that the number could represent. Return the answer in any
// order. A mapping of digits to letters (just like on the telephone buttons) is
// given below. Note that 1 does not map to any letters.
// ![img](https://assets.leetcode.com/uploads/2022/03/15/1200px-telephone-keypad2svg.png)
//  
//

LEETCODE_BEGIN_RESOLVING(17, LetterCombinationsOfAPhoneNumber, Solution);

class Solution {
private:
  unordered_map<char, string> phone = {
      {'2',  "abc"},
      {'3',  "def"},
      {'4',  "ghi"},
      {'5',  "jkl"},
      {'6',  "mno"},
      {'7', "pqrs"},
      {'8',  "tuv"},
      {'9', "wxyz"}
  };
  void helper(vector<string> &r, string &s, string &cur, int beg = 0) {
    if (s.empty())
      return;
    if (beg == s.size()) {
      r.push_back(cur);
    } else {
      auto characters = phone[s[beg]];
      for (const auto &c : characters) {
        cur.push_back(c);
        helper(r, s, cur, beg + 1);
        cur.pop_back();
      }
    }
  }

public:
  vector<string> letterCombinations(string digits) {
    vector<string> res;
    string         tmp = "";
    helper(res, digits, tmp);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= digits.length <= 4|
// * |digits[i]| is a digit in the range |['2', '9']|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: digits = "23"
// Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
//

LEETCODE_SOLUTION_UNITTEST(17, LetterCombinationsOfAPhoneNumber, example_1) {
  auto           solution = MakeSolution();
  string         digits   = "23";
  vector<string> expect   = {"ad", "ae", "af", "bd", "be",
                             "bf", "cd", "ce", "cf"};
  vector<string> actual   = solution->letterCombinations(digits);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: digits = ""
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(17, LetterCombinationsOfAPhoneNumber, example_2) {
  auto           solution = MakeSolution();
  string         digits   = "";
  vector<string> expect   = {};
  vector<string> actual   = solution->letterCombinations(digits);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: digits = "2"
// Output: ["a","b","c"]
//

LEETCODE_SOLUTION_UNITTEST(17, LetterCombinationsOfAPhoneNumber, example_3) {
  auto           solution = MakeSolution();
  string         digits   = "2";
  vector<string> expect   = {"a", "b", "c"};
  vector<string> actual   = solution->letterCombinations(digits);
  EXPECT_ANYORDER_EQ(expect, actual);
}
