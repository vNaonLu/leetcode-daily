// Copyright 2024 Naon Lu
//
// This file describes the solution of
// HTML Entity Parser
//
// https://leetcode.com/problems/html-entity-parser/
//
// Question ID: 1410
// Difficult  : Medium
// Solve Date : 2024/11/03 13:14

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1410. HTML Entity Parser|:
//
// HTML entity parser is the parser that takes HTML code as input and replace
// all the entities of the special characters by the characters itself. The
// special characters and their entities for HTML are:
//
//  • Quotation Mark: the entity is |&quot;| and symbol character is |"|.
//
//  • Single Quote Mark: the entity is |&apos;| and symbol character is |'|.
//
//  • Ampersand: the entity is |&amp;| and symbol character is |&|.
//
//  • Greater Than Sign: the entity is |&gt;| and symbol character is |>|.
//
//  • Less Than Sign: the entity is |&lt;| and symbol character is |<|.
//
//  • Slash: the entity is |&frasl;| and symbol character is |/|.
// Given the input |text| string to the HTML parser, you have to implement the
// entity parser. Return the text after replacing the entities by the special
// characters.
//
//

LEETCODE_BEGIN_RESOLVING(1410, HTMLEntityParser, Solution);

class Solution {
public:
  string entityParser(string text) {
    unordered_map<string, char> mp{
        { "&quot;",  '"'},
        { "&apos;", '\''},
        {   "&gt;",  '>'},
        {   "&lt;",  '<'},
        {"&frasl;",  '/'},
        {  "&amp;",  '&'}
    };
    string res;
    int    i = 0;
    int    n = text.size();
    while (i < n) {
      if (text[i] == '&') {
        string t = "&";
        ++i;
        while (i < n) {
          if (text[i] == ';') {
            t += ';';
            auto find = mp.find(t);
            if (find != mp.end()) {
              res += find->second;
            } else {
              res += std::move(t);
            }
            break;
          } else if (text[i] == '&') {
            res += t;
            t = "&";
          } else {
            t += text[i];
          }
          ++i;
        }
        if (t.back() != ';') {
          res += std::move(t);
        }
      } else {
        res += text[i];
      }
      ++i;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= text.length <= 10⁵|
// * The string may contain any possible characters out of all the 256 ASCII
// characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: text = "&amp; is an HTML entity but &ambassador; is not."
// Output: "& is an HTML entity but &ambassador; is not."
//

LEETCODE_SOLUTION_UNITTEST(1410, HTMLEntityParser, example_1) {
  auto   solution = MakeSolution();
  string text     = "&amp; is an HTML entity but &ambassador; is not.";
  string expect   = "& is an HTML entity but &ambassador; is not.";
  string actual   = solution->entityParser(text);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: text = "and I quote: &quot;...&quot;"
// Output: "and I quote: \"...\""
//

LEETCODE_SOLUTION_UNITTEST(1410, HTMLEntityParser, example_2) {
  auto   solution = MakeSolution();
  string text     = "and I quote: &quot;...&quot;";
  string expect   = "and I quote: \"...\"";
  string actual   = solution->entityParser(text);
  LCD_EXPECT_EQ(expect, actual);
}
