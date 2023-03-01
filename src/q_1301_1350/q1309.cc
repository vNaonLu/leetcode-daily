// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Decrypt String from Alphabet to Integer Mapping
//
// https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/
//
// Question ID: 1309
// Difficult  : Easy
// Solve Date : 2022/04/22 08:58

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1309. Decrypt String from Alphabet to Integer Mapping|:
//
// You are given a string |s| formed by digits and |'#'|. We want to map |s| to
// English lowercase characters as follows:
//
//  • Characters ( |'a'| to |'i'|) are represented by ( |'1'| to |'9'|)
//  respectively.
//
//  • Characters ( |'j'| to |'z'|) are represented by ( |'10#'| to |'26#'|)
//  respectively.
// Return the string formed after mapping.
// The test cases are generated so that a unique mapping will always exist.
//  
//

LEETCODE_BEGIN_RESOLVING(1309, DecryptStringFromAlphabetToIntegerMapping,
                         Solution);

class Solution {
public:
  string freqAlphabets(string s) {
    string res;
    for (int i = s.size() - 1; i >= 0; --i) {
      if (s[i] == '#') {
        res.push_back(stoi(s.substr(i - 2, 2)) - 10 + 'j');
        -- --i;
      } else {
        res.push_back(s[i] - '1' + 'a');
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
// * |1 <= s.length <= 1000|
// * |s| consists of digits and the |'#'| letter.
// * |s| will be a valid string such that mapping is always possible.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "10#11#12"
// Output: "jkab"
//
// "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".

LEETCODE_SOLUTION_UNITTEST(1309, DecryptStringFromAlphabetToIntegerMapping,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "10#11#12";
  string expect   = "jkab";
  string actual   = solution->freqAlphabets(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "1326#"
// Output: "acz"
//

LEETCODE_SOLUTION_UNITTEST(1309, DecryptStringFromAlphabetToIntegerMapping,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "1326#";
  string expect   = "acz";
  string actual   = solution->freqAlphabets(s);
  LCD_EXPECT_EQ(expect, actual);
}
