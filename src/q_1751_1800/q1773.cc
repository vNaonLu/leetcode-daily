// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Items Matching a Rule
//
// https://leetcode.com/problems/count-items-matching-a-rule/
//
// Question ID: 1773
// Difficult  : Easy
// Solve Date : 2023/04/05 12:36

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1773. Count Items Matching a Rule|:
//
// You are given an array |items|, where each |items[i] = [typeᵢ, colorᵢ,
// nameᵢ]| describes the type, color, and name of the |iᵗʰ| item. You are also
// given a rule represented by two strings, |ruleKey| and |ruleValue|. The |iᵗʰ|
// item is said to match the rule if one of the following is true:
//
//  • |ruleKey == "type"| and |ruleValue == typeᵢ|.
//
//  • |ruleKey == "color"| and |ruleValue == colorᵢ|.
//
//  • |ruleKey == "name"| and |ruleValue == nameᵢ|.
// Return the number of items that match the given rule.
//
//

LEETCODE_BEGIN_RESOLVING(1773, CountItemsMatchingARule, Solution);

class Solution {
public:
  int countMatches(vector<vector<string>> &items, string ruleKey,
                   string ruleValue) {
    int res     = 0;
    int gen_idx = 0;
    if (ruleKey == "type") {
      gen_idx = 0;
    } else if (ruleKey == "color") {
      gen_idx = 1;
    } else if (ruleKey == "name") {
      gen_idx = 2;
    } else {
      return -1;
    }
    for (auto &v : items) {
      if (v[gen_idx] == ruleValue) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= items.length <= 10⁴|
// * |1 <= typeᵢ.length, colorᵢ.length, nameᵢ.length, ruleValue.length <= 10|
// * |ruleKey| is equal to either |"type"|, |"color"|, or |"name"|.
// * All strings consist only of lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: items =
//  [["phone","blue","pixel"],["computer","silver","lenovo"],["phone","gold","iphone"]],
//  ruleKey = "color", ruleValue = "silver"
// Output: 1
//
// There is only one item matching the given rule, which is
// ["computer","silver","lenovo"].

LEETCODE_SOLUTION_UNITTEST(1773, CountItemsMatchingARule, example_1) {
  auto                   solution = MakeSolution();
  vector<vector<string>> items    = {
      {   "phone",   "blue",  "pixel"},
      {"computer", "silver", "lenovo"},
      {   "phone",   "gold", "iphone"}
  };
  string ruleKey   = "color";
  string ruleValue = "silver";
  int    expect    = 1;
  int    actual    = solution->countMatches(items, ruleKey, ruleValue);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: items =
//  [["phone","blue","pixel"],["computer","silver","phone"],["phone","gold","iphone"]],
//  ruleKey = "type", ruleValue = "phone"
// Output: 2
//
// There are only two items matching the given rule, which are
// ["phone","blue","pixel"] and ["phone","gold","iphone"]. Note that the item
// ["computer","silver","phone"] does not match.

LEETCODE_SOLUTION_UNITTEST(1773, CountItemsMatchingARule, example_2) {
  auto                   solution = MakeSolution();
  vector<vector<string>> items    = {
      {   "phone",   "blue",  "pixel"},
      {"computer", "silver",  "phone"},
      {   "phone",   "gold", "iphone"}
  };
  string ruleKey   = "type";
  string ruleValue = "phone";
  int    expect    = 2;
  int    actual    = solution->countMatches(items, ruleKey, ruleValue);
  LCD_EXPECT_EQ(expect, actual);
}
