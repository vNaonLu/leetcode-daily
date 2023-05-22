// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Defanging an IP Address
//
// https://leetcode.com/problems/defanging-an-ip-address/
//
// Question ID: 1108
// Difficult  : Easy
// Solve Date : 2023/05/21 13:42

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1108. Defanging an IP Address|:
//
// Given a valid (IPv4) IP |address|, return a defanged version of that IP
// address.
//
// A defanged IP address replaces every period |"."| with |"[.]"|.
//
//
//

LEETCODE_BEGIN_RESOLVING(1108, DefangingAnIPAddress, Solution);

class Solution {
public:
  string defangIPaddr(string address) {
    string res;
    for (auto c : address) {
      if (c == '.') {
        res += "[.]";
      } else {
        res += c;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The given |address| is a valid IPv4 address.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: address = "1.1.1.1"
// Output: "1[.]1[.]1[.]1"
//

LEETCODE_SOLUTION_UNITTEST(1108, DefangingAnIPAddress, example_1) {
  auto   solution = MakeSolution();
  string address  = "1.1.1.1";
  string expect   = "1[.]1[.]1[.]1";
  string actual   = solution->defangIPaddr(address);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: address = "255.100.50.0"
// Output: "255[.]100[.]50[.]0"
//

LEETCODE_SOLUTION_UNITTEST(1108, DefangingAnIPAddress, example_2) {
  auto   solution = MakeSolution();
  string address  = "255.100.50.0";
  string expect   = "255[.]100[.]50[.]0";
  string actual   = solution->defangIPaddr(address);
  LCD_EXPECT_EQ(expect, actual);
}
