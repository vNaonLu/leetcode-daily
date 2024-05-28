// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Fraction Addition and Subtraction
//
// https://leetcode.com/problems/fraction-addition-and-subtraction/
//
// Question ID: 592
// Difficult  : Medium
// Solve Date : 2024/05/25 14:19

#include <iosfwd>
#include <istream>
#include <numeric>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |592. Fraction Addition and Subtraction|:
//
// Given a string |expression| representing an expression of fraction addition
// and subtraction, return the calculation result in string format. The final
// result should be an [irreducible fraction]. If your final result is an
// integer, change it to the format of a fraction that has a denominator |1|. So
// in this case, |2| should be converted to |2/1|.
//
//

LEETCODE_BEGIN_RESOLVING(592, FractionAdditionAndSubtraction, Solution);

class Solution {
public:
  string fractionAddition(string expression) {
    istringstream ss(expression);
    int           x;
    int           y;
    char          c;
    int           de = 0;
    int           nu = 1;
    while (ss >> x >> c >> y) {
      de = de * y + x * nu;
      nu *= y;
    }
    auto g = gcd(de, nu);
    de /= g;
    nu /= g;
    return to_string(de) + "/" + to_string(nu);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The input string only contains |'0'| to |'9'|, |'/'|, |'+'| and |'-'|. So
// does the output.
// * Each fraction (input and output) has the format |±numerator/denominator|.
// If the first input fraction or the output is positive, then |'+'| will be
// omitted.
// * The input only contains valid irreducible fractions, where the numerator
// and denominator of each fraction will always be in the range |[1, 10]|. If
// the denominator is |1|, it means this fraction is actually an integer in a
// fraction format defined above.
// * The number of given fractions will be in the range |[1, 10]|.
// * The numerator and denominator of the final result are guaranteed to be
// valid and in the range of 32-bit int.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: expression = "-1/2+1/2"
// Output: "0/1"
//

LEETCODE_SOLUTION_UNITTEST(592, FractionAdditionAndSubtraction, example_1) {
  auto   solution   = MakeSolution();
  string expression = "-1/2+1/2";
  string expect     = "0/1";
  string actual     = solution->fractionAddition(expression);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: expression = "-1/2+1/2+1/3"
// Output: "1/3"
//

LEETCODE_SOLUTION_UNITTEST(592, FractionAdditionAndSubtraction, example_2) {
  auto   solution   = MakeSolution();
  string expression = "-1/2+1/2+1/3";
  string expect     = "1/3";
  string actual     = solution->fractionAddition(expression);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: expression = "1/3-1/2"
// Output: "-1/6"
//

LEETCODE_SOLUTION_UNITTEST(592, FractionAdditionAndSubtraction, example_3) {
  auto   solution   = MakeSolution();
  string expression = "1/3-1/2";
  string expect     = "-1/6";
  string actual     = solution->fractionAddition(expression);
  LCD_EXPECT_EQ(expect, actual);
}
