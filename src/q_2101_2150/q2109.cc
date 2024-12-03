// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Adding Spaces to a String
//
// https://leetcode.com/problems/adding-spaces-to-a-string/
//
// Question ID: 2109
// Difficult  : Medium
// Solve Date : 2024/12/03 18:44

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2109. Adding Spaces to a String|:
//
// You are given a 0-indexed string |s| and a 0-indexed integer array |spaces|
// that describes the indices in the original string where spaces will be added.
// Each space should be inserted before the character at the given index.
//
//  • For example, given |s = "EnjoyYourCoffee"| and |spaces = [5, 9]|, we place
//  spaces before |'Y'| and |'C'|, which are at indices |5| and |9|
//  respectively. Thus, we obtain |"Enjoy Your Coffee"|.
// Return the modified string after the spaces have been added.
//
//

LEETCODE_BEGIN_RESOLVING(2109, AddingSpacesToAString, Solution);

class Solution {
public:
  string addSpaces(string s, vector<int> &spaces) {
    string res;
    int    prev = 0;
    for (auto x : spaces) {
      res += s.substr(prev, x - prev);
      res += ' ';
      prev = x;
    }
    res += s.substr(prev);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 3 * 10⁵|
// * |s| consists only of lowercase and uppercase English letters.
// * |1 <= spaces.length <= 3 * 10⁵|
// * |0 <= spaces[i] <= s.length - 1|
// * All the values of |spaces| are strictly increasing.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
// Output: "Leetcode Helps Me Learn"
//

LEETCODE_SOLUTION_UNITTEST(2109, AddingSpacesToAString, example_1) {
  auto        solution = MakeSolution();
  string      s        = "LeetcodeHelpsMeLearn";
  vector<int> spaces   = {8, 13, 15};
  string      expect   = "Leetcode Helps Me Learn";
  string      actual   = solution->addSpaces(s, spaces);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "icodeinpython", spaces = [1,5,7,9]
// Output: "i code in py thon"
//

LEETCODE_SOLUTION_UNITTEST(2109, AddingSpacesToAString, example_2) {
  auto        solution = MakeSolution();
  string      s        = "icodeinpython";
  vector<int> spaces   = {1, 5, 7, 9};
  string      expect   = "i code in py thon";
  string      actual   = solution->addSpaces(s, spaces);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "spacing", spaces = [0,1,2,3,4,5,6]
// Output: " s p a c i n g"
//

LEETCODE_SOLUTION_UNITTEST(2109, AddingSpacesToAString, example_3) {
  auto        solution = MakeSolution();
  string      s        = "spacing";
  vector<int> spaces   = {0, 1, 2, 3, 4, 5, 6};
  string      expect   = " s p a c i n g";
  string      actual   = solution->addSpaces(s, spaces);
  LCD_EXPECT_EQ(expect, actual);
}
