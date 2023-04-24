// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Value of a String in an Array
//
// https://leetcode.com/problems/maximum-value-of-a-string-in-an-array/
//
// Question ID: 2496
// Difficult  : Easy
// Solve Date : 2023/04/20 18:55

#include <algorithm>
#include <cctype>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2496. Maximum Value of a String in an Array|:
//
// The value of an alphanumeric string can be defined as:
//
//  • The numeric representation of the string in base |10|, if it comprises of
//  digits only.
//
//  • The length of the string, otherwise.
// Given an array |strs| of alphanumeric strings, return the maximum value of
// any string in |strs|.
//
//

LEETCODE_BEGIN_RESOLVING(2496, MaximumValueOfAStringInAnArray, Solution);

class Solution {
public:
  int maximumValue(vector<string> &strs) {
    int res = 0;
    for (auto const &s : strs) {
      res = max(res, getNumber(s.begin(), s.end()));
    }
    return res;
  }

private:
  template <typename It>
  int getNumber(It beg, It end) {

    if (!all_of(beg, end, [](char x) { return isdigit(x); })) {
      return distance(beg, end);
    }

    int x = 0;
    while (beg != end) {
      x = x * 10 + (*beg++ - '0');
    }
    return x;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= strs.length <= 100|
// * |1 <= strs[i].length <= 9|
// * |strs[i]| consists of only lowercase English letters and digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: strs = ["alic3","bob","3","4","00000"]
// Output: 5
//
// - "alic3" consists of both letters and digits, so its value is its length,
// i.e. 5.
// - "bob" consists only of letters, so its value is also its length, i.e. 3.
// - "3" consists only of digits, so its value is its numeric equivalent,
// i.e. 3.
// - "4" also consists only of digits, so its value is 4.
// - "00000" consists only of digits, so its value is 0.
// Hence, the maximum value is 5, of "alic3".

LEETCODE_SOLUTION_UNITTEST(2496, MaximumValueOfAStringInAnArray, example_1) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"alic3", "bob", "3", "4", "00000"};
  int            expect   = 5;
  int            actual   = solution->maximumValue(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: strs = ["1","01","001","0001"]
// Output: 1
//
// Each string in the array has value 1. Hence, we return 1.

LEETCODE_SOLUTION_UNITTEST(2496, MaximumValueOfAStringInAnArray, example_2) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"1", "01", "001", "0001"};
  int            expect   = 1;
  int            actual   = solution->maximumValue(strs);
  LCD_EXPECT_EQ(expect, actual);
}
