// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Solve the Equation
//
// https://leetcode.com/problems/solve-the-equation/
//
// Question ID: 640
// Difficult  : Medium
// Solve Date : 2022/07/06 18:18

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |640. Solve the Equation|:
//
// Solve a given equation and return the value of |'x'| in the form of a string
// |"x=#value"|. The equation contains only |'+'|, |'-'| operation, the variable
// |'x'| and its coefficient. You should return |"No solution"| if there is no
// solution for the equation, or |"Infinite solutions"| if there are infinite
// solutions for the equation. If there is exactly one solution for the
// equation, we ensure that the value of |'x'| is an integer.
//

LEETCODE_BEGIN_RESOLVING(640, SolveTheEquation, Solution);

class Solution {
private:
  struct Coefficient {
    int x, cst;
  };

  template <typename Iterator>
  int toInteger(Iterator beg, Iterator end) {
    if (beg == end) {
      return 0;
    }

    if (beg + 1 == end) {
      switch (*beg) {
      case '+':
        return 1;
      case '-':
        return -1;
      default:
        return *beg - '0';
      }
    }

    int scale = 1, num = 0;
    while (beg != end) {
      auto c = *beg++;
      switch (c) {
      case '+':
        scale = 1;
        break;
      case '-':
        scale = -1;
        break;
      default:
        num = num * 10 + (c - '0');
      }
    }

    return scale * num;
  }

  template <typename Iterator>
  Coefficient solveCoefficient(Iterator beg, Iterator end) {
    Coefficient res{0, 0};

    auto prev = beg;
    while (beg != end) {
      auto c = *beg;
      if (c < '0' || c > '9') {
        if (c == 'x') {
          if (prev == beg) {
            ++res.x;
          } else {
            res.x += toInteger(prev, beg);
          }

          prev = ++beg;
        } else {
          res.cst += toInteger(prev, beg);
          prev = beg++;
        }
      } else {
        ++beg;
      }
    }
    res.cst += toInteger(prev, beg);

    return res;
  }

public:
  string solveEquation(string equation) {
    auto find  = equation.begin() + equation.find('=');
    auto left  = solveCoefficient(equation.begin(), find),
         right = solveCoefficient(find + 1, equation.end());

    if (left.x == right.x) {

      return left.cst == right.cst ? "Infinite solutions" : "No solution";
    } else {

      return string("x=") +
             to_string((right.cst - left.cst) / (left.x - right.x));
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= equation.length <= 1000|
// * |equation| has exactly one |'='|.
// * |equation| consists of integers with an absolute value in the range |[0,
// 100]| without any leading zeros, and the variable |'x'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: equation = "x+5-3+x=6+x-2"
// Output: "x=2"
//

LEETCODE_SOLUTION_UNITTEST(640, SolveTheEquation, example_1) {
  auto   solution = MakeSolution();
  string equation = "x+5-3+x=6+x-2";
  string expect   = "x=2";
  string actual   = solution->solveEquation(equation);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: equation = "x=x"
// Output: "Infinite solutions"
//

LEETCODE_SOLUTION_UNITTEST(640, SolveTheEquation, example_2) {
  auto   solution = MakeSolution();
  string equation = "x=x";
  string expect   = "Infinite solutions";
  string actual   = solution->solveEquation(equation);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: equation = "2x=x"
// Output: "x=0"
//

LEETCODE_SOLUTION_UNITTEST(640, SolveTheEquation, example_3) {
  auto   solution = MakeSolution();
  string equation = "2x=x";
  string expect   = "x=0";
  string actual   = solution->solveEquation(equation);
  LCD_EXPECT_EQ(expect, actual);
}
