// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Number of Atoms
//
// https://leetcode.com/problems/number-of-atoms/
//
// Question ID: 726
// Difficult  : Hard
// Solve Date : 2024/07/14 14:30

#include <algorithm>
#include <cctype>
#include <iosfwd>
#include <map>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |726. Number of Atoms|:
//
// Given a string |formula| representing a chemical formula, return the count of
// each atom. The atomic element always starts with an uppercase character, then
// zero or more lowercase letters, representing the name. One or more digits
// representing that element's count may follow if the count is greater than
// |1|. If the count is |1|, no digits will follow.
//
//  • For example, |"H2O"| and |"H2O2"| are possible, but |"H1O2"| is
//  impossible.
// Two formulas are concatenated together to produce another formula.
//
//  • For example, |"H2O2He3Mg4"| is also a formula.
// A formula placed in parentheses, and a count (optionally added) is also a
// formula.
//
//  • For example, |"(H2O2)"| and |"(H2O2)3"| are formulas.
// Return the count of all elements as a string in the following form: the first
// name (in sorted order), followed by its count (if that count is more than
// |1|), followed by the second name (in sorted order), followed by its count
// (if that count is more than |1|), and so on. The test cases are generated so
// that all the values in the output fit in a 32-bit integer.
//
//

LEETCODE_BEGIN_RESOLVING(726, NumberOfAtoms, Solution);

class Solution {
public:
  string countOfAtoms(string formula) {
    stack<map<string, int>> stk;
    stk.push(map<string, int>());
    int n = formula.size();
    for (int i = 0; i < n;) {
      if (formula[i] == '(') {
        stk.push(map<string, int>());
        i++;
      } else if (formula[i] == ')') {
        auto top = stk.top();
        stk.pop();
        i++;
        int i_start = i;
        while (i < n && isdigit(formula[i])) {
          i++;
        }
        int multiplier =
            i > i_start ? stoi(formula.substr(i_start, i - i_start)) : 1;
        for (auto &p : top) {
          stk.top()[p.first] += p.second * multiplier;
        }
      } else {
        int i_start = i;
        i++;
        while (i < n && islower(formula[i])) {
          i++;
        }
        string element = formula.substr(i_start, i - i_start);
        i_start        = i;
        while (i < n && isdigit(formula[i])) {
          i++;
        }
        int count =
            i > i_start ? stoi(formula.substr(i_start, i - i_start)) : 1;
        stk.top()[element] += count;
      }
    }
    auto                     &counts = stk.top();
    vector<pair<string, int>> elements(counts.begin(), counts.end());
    sort(elements.begin(), elements.end());
    string result;
    for (auto &p : elements) {
      result += p.first;
      if (p.second > 1) {
        result += to_string(p.second);
      }
    }
    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= formula.length <= 1000|
// * |formula| consists of English letters, digits, |'('|, and |')'|.
// * |formula| is always valid.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: formula = "H2O"
// Output: "H2O"
//

LEETCODE_SOLUTION_UNITTEST(726, NumberOfAtoms, example_1) {
  auto   solution = MakeSolution();
  string formula  = "H2O";
  string expect   = "H2O";
  string actual   = solution->countOfAtoms(formula);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: formula = "Mg(OH)2"
// Output: "H2MgO2"
//

LEETCODE_SOLUTION_UNITTEST(726, NumberOfAtoms, example_2) {
  auto   solution = MakeSolution();
  string formula  = "Mg(OH)2";
  string expect   = "H2MgO2";
  string actual   = solution->countOfAtoms(formula);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: formula = "K4(ON(SO3)2)2"
// Output: "K4N2O14S4"
//

LEETCODE_SOLUTION_UNITTEST(726, NumberOfAtoms, example_3) {
  auto   solution = MakeSolution();
  string formula  = "K4(ON(SO3)2)2";
  string expect   = "K4N2O14S4";
  string actual   = solution->countOfAtoms(formula);
  LCD_EXPECT_EQ(expect, actual);
}
