// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Value after Insertion
//
// https://leetcode.com/problems/maximum-value-after-insertion/
//
// Question ID: 1881
// Difficult  : Medium
// Solve Date : 2021/10/17 15:52

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1881. Maximum Value after Insertion|:
//
// You are given a very large integer |n|, represented as a
// string,​​​​​​ and an integer digit |x|. The digits in |n| and the
// digit |x| are in the inclusive range |[1, 9]|, and |n| may represent a
// negative number. You want to maximize |n|'s numerical value by inserting |x|
// anywhere in the decimal representation of |n|​​​​​​. You cannot
// insert |x| to the left of the negative sign.
//
//  • For example, if |n = 73| and |x = 6|, it would be best to insert it
//  between |7| and |3|, making |n = 763|.
//
//  • If |n = -55| and |x = 2|, it would be best to insert it before the first
//  |5|, making |n = -255|.
// Return a string representing the maximum value of |n|​​​​​​ after
// the insertion.  
//

LEETCODE_BEGIN_RESOLVING(1881, MaximumValueAfterInsertion, Solution);

class Solution {
private:
  string maxInsert(const string &s, const int &x) {
    string res = s;
    for (int i = 0; i < s.size(); ++i) {
      char c = x + '0';
      if (res[i] < c) {
        res.insert(i, 1, c);
        return res;
      }
    }
    res.push_back(x + '0');
    return res;
  }
  string minInsert(const string &s, const int &x) {
    string res = s;
    for (int i = 0; i < s.size(); ++i) {
      char c = x + '0';
      if (res[i] > c) {
        res.insert(i, 1, c);
        return res;
      }
    }
    res.push_back(x + '0');
    return res;
  }

public:
  string maxValue(string n, int x) {
    if (n[0] == '-') {
      return "-" + minInsert(n.substr(1), x);
    } else {
      return maxInsert(n, x);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n.length <= 10⁵|
// * |1 <= x <= 9|
// * The digits in |n|​​​ are in the range |[1, 9]|.
// * |n| is a valid representation of an integer.
// * In the case of a negative |n|,​​​​​​ it will begin with |'-'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = "99", x = 9
// Output: "999"
//
// The result is the same regardless of where you insert 9.

LEETCODE_SOLUTION_UNITTEST(1881, MaximumValueAfterInsertion, example_1) {
  auto   solution = MakeSolution();
  string n        = "99";
  int    x        = 9;
  string expect   = "999";
  string actual   = solution->maxValue(n, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = "-13", x = 2
// Output: "-123"
//
// You can make n one of {-213, -123, -132}, and the largest of those three is
// -123.

LEETCODE_SOLUTION_UNITTEST(1881, MaximumValueAfterInsertion, example_2) {
  auto   solution = MakeSolution();
  string n        = "-13";
  int    x        = 2;
  string expect   = "-123";
  string actual   = solution->maxValue(n, x);
  LCD_EXPECT_EQ(expect, actual);
}
