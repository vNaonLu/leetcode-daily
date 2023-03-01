// Copyright 2023 Naon Lu
//
// This file describes the solution of
// String Matching in an Array
//
// https://leetcode.com/problems/string-matching-in-an-array/
//
// Question ID: 1408
// Difficult  : Easy
// Solve Date : 2022/02/18 19:51

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1408. String Matching in an Array|:
//
// Given an array of string |words|, return all strings in |words| that is a
// substring of another word. You can return the answer in any order. A
// substring is a contiguous sequence of characters within a string  
//

LEETCODE_BEGIN_RESOLVING(1408, StringMatchingInAnArray, Solution);

class Solution {
public:
  vector<string> stringMatching(vector<string> &words) {
    sort(words.begin(), words.end(), [](auto &x, auto &y) {
      return x.size() == y.size() ? (x < y) : (x.size() < y.size());
    });
    vector<string> res;
    for (int i = 0; i < words.size(); ++i) {
      for (int j = i + 1; j < words.size(); ++j) {
        if (words[j].find(words[i]) != string::npos) {
          res.emplace_back(words[i]);
          break;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 30|
// * |words[i]| contains only lowercase English letters.
// * All the strings of |words| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["mass","as","hero","superhero"]
// Output: ["as","hero"]
//
// "as" is substring of "mass" and "hero" is substring of "superhero".
// ["hero","as"] is also a valid answer.

LEETCODE_SOLUTION_UNITTEST(1408, StringMatchingInAnArray, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"mass", "as", "hero", "superhero"};
  vector<string> expect   = {"as", "hero"};
  vector<string> actual   = solution->stringMatching(words);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["leetcode","et","code"]
// Output: ["et","code"]
//
// "et", "code" are substring of "leetcode".

LEETCODE_SOLUTION_UNITTEST(1408, StringMatchingInAnArray, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"leetcode", "et", "code"};
  vector<string> expect   = {"et", "code"};
  vector<string> actual   = solution->stringMatching(words);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["blue","green","bu"]
// Output: []
//
// No string of words is substring of another string.

LEETCODE_SOLUTION_UNITTEST(1408, StringMatchingInAnArray, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"blue", "green", "bu"};
  vector<string> expect   = {};
  vector<string> actual   = solution->stringMatching(words);
  EXPECT_ANYORDER_EQ(expect, actual);
}
