// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Parsing A Boolean Expression
//
// https://leetcode.com/problems/parsing-a-boolean-expression/
//
// Question ID: 1106
// Difficult  : Hard
// Solve Date : 2024/10/20 13:37

#include <iosfwd>
#include <optional>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1106. Parsing A Boolean Expression|:
//
// A boolean expression is an expression that evaluates to either |true| or
// |false|. It can be in one of the following shapes:
//
//  • |'t'| that evaluates to |true|.
//
//  • |'f'| that evaluates to |false|.
//
//  • |'!(subExpr)'| that evaluates to the logical NOT of the inner expression
//  |subExpr|.
//
//  • |'&(subExpr₁, subExpr₂, ..., subExprₙ)'| that evaluates to the logical AND
//  of the inner expressions |subExpr₁, subExpr₂, ..., subExprₙ| where |n >= 1|.
//
//  • |'|(subExpr₁, subExpr₂, ..., subExprₙ)'| that evaluates to the logical OR
//  of the inner expressions |subExpr₁, subExpr₂, ..., subExprₙ| where |n >= 1|.
// Given a string |expression| that represents a boolean expression, return the
// evaluation of that expression. It is guaranteed that the given expression is
// valid and follows the given rules.
//
//

LEETCODE_BEGIN_RESOLVING(1106, ParsingABooleanExpression, Solution);

class Solution {
public:
  bool parseBoolExpr(string expression) {
    return parse(expression.begin(), expression.end());
  }

private:
  enum Op { kNone, kOr, kAnd };
  bool parse(auto beg, auto end, Op op = kNone) {
    if (beg == end) {
      return true;
    }
    optional<bool> res;
    auto           func = op == kOr ? [](optional<bool> *res, bool b) -> bool {
      return *(*res = res->value_or(false) | b);
    }
    : [](optional<bool> *res, bool b) -> bool {
        return !*(*res = res->value_or(true) & b);
      };
    while (beg != end) {
      auto next  = beg + 1;
      bool solve = false;
      switch (*beg) {
      case '!':
        next  = findClose(beg + 1, end);
        solve = !parse(beg + 2, next, op);
        beg   = ++next;
        break;
      case '&':
        next  = findClose(beg + 1, end);
        solve = parse(beg + 2, next, kAnd);
        beg   = ++next;
        break;
      case '|':
        next  = findClose(beg + 1, end);
        solve = parse(beg + 2, next, kOr);
        beg   = ++next;
        break;
      case 't':
        solve = true;
        ++beg;
        break;
      case 'f':
        solve = false;
        ++beg;
        break;
      default:
        ++beg;
        continue;
      }
      if (func(&res, solve)) {
        return *res;
      }
    }
    return *res;
  }

  auto findClose(auto beg, auto end) {
    int depth = 0;
    while (beg != end) {
      if (*beg == '(') {
        ++depth;
      } else if (*beg == ')') {
        --depth;
      }

      if (depth == 0) {
        break;
      }

      ++beg;
    }
    return beg;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= expression.length <= 2 * 10⁴|
// * expression[i] is one following characters: |'('|, |')'|, |'&'|, |'|'|,
// |'!'|, |'t'|, |'f'|, and |','|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: expression = "&(|(f))"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1106, ParsingABooleanExpression, example_1) {
  auto   solution   = MakeSolution();
  string expression = "&(|(f))";
  bool   expect     = false;
  bool   actual     = solution->parseBoolExpr(expression);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: expression = "|(f,f,f,t)"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1106, ParsingABooleanExpression, example_2) {
  auto   solution   = MakeSolution();
  string expression = "|(f,f,f,t)";
  bool   expect     = true;
  bool   actual     = solution->parseBoolExpr(expression);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: expression = "!(&(f,t))"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1106, ParsingABooleanExpression, example_3) {
  auto   solution   = MakeSolution();
  string expression = "!(&(f,t))";
  bool   expect     = true;
  bool   actual     = solution->parseBoolExpr(expression);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "|(&(t,f,t),!(t))"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1106, ParsingABooleanExpression, extra_testcase_1) {
  auto   solution   = MakeSolution();
  string expression = "|(&(t,f,t),!(t))";
  bool   expect     = false;
  bool   actual     = solution->parseBoolExpr(expression);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: "|(&(t,f,t),t)"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1106, ParsingABooleanExpression, extra_testcase_2) {
  auto   solution   = MakeSolution();
  string expression = "|(&(t,f,t),t)";
  bool   expect     = true;
  bool   actual     = solution->parseBoolExpr(expression);
  LCD_EXPECT_EQ(expect, actual);
}
