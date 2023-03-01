// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert the Temperature
//
// https://leetcode.com/problems/convert-the-temperature/
//
// Question ID: 2469
// Difficult  : Easy
// Solve Date : 2023/02/17 18:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2469. Convert the Temperature|:
//
// You are given a non-negative floating point number rounded to two decimal
// places |celsius|, that denotes the temperature in Celsius. You should convert
// Celsius into Kelvin and Fahrenheit and return it as an array |ans = [kelvin,
// fahrenheit]|. Return the array |ans|. Answers within |10⁻⁵| of the actual
// answer will be accepted. Note that:
//
//  • |Kelvin = Celsius + 273.15|
//
//  • |Fahrenheit = Celsius * 1.80 + 32.00|
//

LEETCODE_BEGIN_RESOLVING(2469, ConvertTheTemperature, Solution);

class Solution {
public:
  vector<double> convertTemperature(double celsius) {
    return vector<double>{celsius + 273.15, celsius * 1.8 + 32.};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= celsius <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: celsius = 36.50
// Output: [309.65000,97.70000]
//
// Temperature at 36.50 Celsius converted in Kelvin is 309.65 and converted in
// Fahrenheit is 97.70.

LEETCODE_SOLUTION_UNITTEST(2469, ConvertTheTemperature, example_1) {
  auto           solution = MakeSolution();
  double         celsius  = 36.50;
  vector<double> expect   = {309.65000, 97.70000};
  vector<double> actual   = solution->convertTemperature(celsius);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: celsius = 122.11
// Output: [395.26000,251.79800]
//
// Temperature at 122.11 Celsius converted in Kelvin is 395.26 and converted in
// Fahrenheit is 251.798.

LEETCODE_SOLUTION_UNITTEST(2469, ConvertTheTemperature, example_2) {
  auto           solution = MakeSolution();
  double         celsius  = 122.11;
  vector<double> expect   = {395.26000, 251.79800};
  vector<double> actual   = solution->convertTemperature(celsius);
  LCD_EXPECT_EQ(expect, actual);
}
