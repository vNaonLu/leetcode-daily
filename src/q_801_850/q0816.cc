// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Ambiguous Coordinates
//
// https://leetcode.com/problems/ambiguous-coordinates/
//
// Question ID: 816
// Difficult  : Medium
// Solve Date : 2024/08/09 22:50

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |816. Ambiguous Coordinates|:
//
// We had some 2-dimensional coordinates, like |"(1, 3)"| or |"(2, 0.5)"|. Then,
// we removed all commas, decimal points, and spaces and ended up with the
// string s.
//
//  • For example, |"(1, 3)"| becomes |s = "(13)"| and |"(2, 0.5)"| becomes |s =
//  "(205)"|.
// Return a list of strings representing all possibilities for what our original
// coordinates could have been. Our original representation never had extraneous
// zeroes, so we never started with numbers like |"00"|, |"0.0"|, |"0.00"|,
// |"1.0"|, |"001"|, |"00.01"|, or any other number that can be represented with
// fewer digits. Also, a decimal point within a number never occurs without at
// least one digit occurring before it, so we never started with numbers like
// |".1"|. The final answer list can be returned in any order. All coordinates
// in the final answer have exactly one space between them (occurring after the
// comma.)
//
//

LEETCODE_BEGIN_RESOLVING(816, AmbiguousCoordinates, Solution);

class Solution {
public:
  vector<string> ambiguousCoordinates(string s) {
    int            n = s.size();
    vector<string> res;
    for (int i = 1; i < n; ++i) {
      auto a = helper(s.substr(1, i));
      auto b = helper(s.substr(i + 1, n - 2 - i));
      for (auto &v : a) {
        for (auto &u : b) {
          res.push_back("(" + v + ", " + u + ")");
        }
      }
    }
    return res;
  }

private:
  vector<string> helper(string const &s) {
    int n = s.size();
    if (n == 0 || (n > 1 && s[0] == '0' && s[n - 1] == '0')) {
      return {};
    }
    if (n > 1 && s[0] == '0') {
      return {"0." + s.substr(1)};
    }
    if (n == 1 || s[n - 1] == '0') {
      return {s};
    }
    vector<string> res = {s};
    for (int i = 1; i < n; ++i) {
      res.push_back(s.substr(0, i) + "." + s.substr(i));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |4 <= s.length <= 12|
// * |s[0] == '('| and |s[s.length - 1] == ')'|.
// * The rest of |s| are digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "(123)"
// Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
//

LEETCODE_SOLUTION_UNITTEST(816, AmbiguousCoordinates, example_1) {
  auto           solution = MakeSolution();
  string         s        = "(123)";
  vector<string> expect   = {"(1, 2.3)", "(1, 23)", "(1.2, 3)", "(12, 3)"};
  vector<string> actual   = solution->ambiguousCoordinates(s);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "(0123)"
// Output: ["(0, 1.23)","(0, 12.3)","(0, 123)","(0.1, 2.3)","(0.1, 23)","(0.12,
// 3)"]
//

LEETCODE_SOLUTION_UNITTEST(816, AmbiguousCoordinates, example_2) {
  auto           solution = MakeSolution();
  string         s        = "(0123)";
  vector<string> expect   = {"(0, 1.23)",  "(0, 12.3)", "(0, 123)",
                             "(0.1, 2.3)", "(0.1, 23)", "(0.12, 3)"};
  vector<string> actual   = solution->ambiguousCoordinates(s);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "(00011)"
// Output: ["(0, 0.011)","(0.001, 1)"]
//

LEETCODE_SOLUTION_UNITTEST(816, AmbiguousCoordinates, example_3) {
  auto           solution = MakeSolution();
  string         s        = "(00011)";
  vector<string> expect   = {"(0, 0.011)", "(0.001, 1)"};
  vector<string> actual   = solution->ambiguousCoordinates(s);
  EXPECT_ANYORDER_EQ(expect, actual);
}
