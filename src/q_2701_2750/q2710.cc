// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Trailing Zeros From a String
//
// https://leetcode.com/problems/remove-trailing-zeros-from-a-string/
//
// Question ID: 2710
// Difficult  : Easy
// Solve Date : 2023/12/15 18:46

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2710. Remove Trailing Zeros From a String|:
//
// Given a positive integer |num| represented as a string, return the integer
// |num| without trailing zeros as a string.
//
//

LEETCODE_BEGIN_RESOLVING(2710, RemoveTrailingZerosFromAString, Solution);

class Solution {
public:
  string removeTrailingZeros(string num) {
    string res;
    for (auto it = num.rbegin(); num.rend() != it; ++it) {
      if (!res.empty() || *it != '0') {
        res.push_back(*it);
      }
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= num.length <= 1000|
// * |num| consists of only digits.
// * |num| doesn't have any leading zeros.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = "51230100"
// Output: "512301"
//
// Integer "51230100" has 2 trailing zeros, we remove them and return integer
// "512301".

LEETCODE_SOLUTION_UNITTEST(2710, RemoveTrailingZerosFromAString, example_1) {
  auto   solution = MakeSolution();
  string num      = "51230100";
  string expect   = "512301";
  string actual   = solution->removeTrailingZeros(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = "123"
// Output: "123"
//
// Integer "123" has no trailing zeros, we return integer "123".

LEETCODE_SOLUTION_UNITTEST(2710, RemoveTrailingZerosFromAString, example_2) {
  auto   solution = MakeSolution();
  string num      = "123";
  string expect   = "123";
  string actual   = solution->removeTrailingZeros(num);
  LCD_EXPECT_EQ(expect, actual);
}
