// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Coupon Code Validator
//
// https://leetcode.com/problems/coupon-code-validator/
//
// Question ID: 3606
// Difficult  : Easy
// Solve Date : 2025/12/13 13:52

#include <cctype>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3606. Coupon Code Validator|:
//
// You are given three arrays of length |n| that describe the properties of |n|
// coupons: |code|, |businessLine|, and |isActive|. The |iᵗʰ |coupon has:
//
//  • |code[i]|: a string representing the coupon identifier.
//
//  • |businessLine[i]|: a string denoting the business category of the coupon.
//
//  • |isActive[i]|: a boolean indicating whether the coupon is currently
//  active.
// A coupon is considered valid if all of the following conditions hold:
//
//  1. |code[i]| is non-empty and consists only of alphanumeric characters (a-z,
//  A-Z, 0-9) and underscores ( |_|).
//
//  2. |businessLine[i]| is one of the following four categories:
//  |"electronics"|, |"grocery"|, |"pharmacy"|, |"restaurant"|.
//
//  3. |isActive[i]| is true.
// Return an array of the codes of all valid coupons, sorted first by their
// businessLine in the order: |"electronics"|, |"grocery"|, |"pharmacy",
// "restaurant"|, and then by code in lexicographical (ascending) order within
// each category.
//
//

LEETCODE_BEGIN_RESOLVING(3606, CouponCodeValidator, Solution);

class Solution {
public:
  vector<string> validateCoupons(vector<string> &code,
                                 vector<string> &businessLine,
                                 vector<bool>   &isActive) {

    // Business line priority
    unordered_map<string, int> priority = {
        {"electronics", 0},
        {    "grocery", 1},
        {   "pharmacy", 2},
        { "restaurant", 3}
    };

    vector<pair<int, string>> valid;

    for (int i = 0; i < code.size(); i++) {
      if (isActive[i] && priority.count(businessLine[i]) &&
          isValidCode(code[i])) {

        valid.push_back({priority[businessLine[i]], code[i]});
      }
    }

    // Sort by priority, then by code
    sort(valid.begin(), valid.end());

    vector<string> result;
    for (auto &p : valid) {
      result.push_back(p.second);
    }

    return result;
  }

private:
  bool isValidCode(const string &s) {
    if (s.empty())
      return false;
    for (char c : s) {
      if (!isalnum(c) && c != '_')
        return false;
    }
    return true;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == code.length == businessLine.length == isActive.length|
// * |1 <= n <= 100|
// * |0 <= code[i].length, businessLine[i].length <= 100|
// * |code[i]| and |businessLine[i]| consist of printable ASCII characters.
// * |isActive[i]| is either |true| or |false|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: code = ["SAVE20","","PHARMA5","SAVE@20"], businessLine =
//  ["restaurant","grocery","pharmacy","restaurant"], isActive =
//  [true,true,true,true]
// Output: ["PHARMA5","SAVE20"]
//

LEETCODE_SOLUTION_UNITTEST(3606, CouponCodeValidator, example_1) {
  auto           solution     = MakeSolution();
  vector<string> code         = {"SAVE20", "", "PHARMA5", "SAVE@20"};
  vector<string> businessLine = {"restaurant", "grocery", "pharmacy",
                                 "restaurant"};
  vector<bool>   isActive     = {true, true, true, true};
  vector<string> expect       = {"PHARMA5", "SAVE20"};
  vector<string> actual =
      solution->validateCoupons(code, businessLine, isActive);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"], businessLine =
//  ["grocery","electronics","invalid"], isActive = [false,true,true]
// Output: ["ELECTRONICS_50"]
//

LEETCODE_SOLUTION_UNITTEST(3606, CouponCodeValidator, example_2) {
  auto           solution     = MakeSolution();
  vector<string> code         = {"GROCERY15", "ELECTRONICS_50", "DISCOUNT10"};
  vector<string> businessLine = {"grocery", "electronics", "invalid"};
  vector<bool>   isActive     = {false, true, true};
  vector<string> expect       = {"ELECTRONICS_50"};
  vector<string> actual =
      solution->validateCoupons(code, businessLine, isActive);
  LCD_EXPECT_EQ(expect, actual);
}
