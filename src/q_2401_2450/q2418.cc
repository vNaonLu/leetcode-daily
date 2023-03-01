// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort the People
//
// https://leetcode.com/problems/sort-the-people/
//
// Question ID: 2418
// Difficult  : Easy
// Solve Date : 2023/01/18 17:53

#include <algorithm>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2418. Sort the People|:
//
// You are given an array of strings |names|, and an array |heights| that
// consists of distinct positive integers. Both arrays are of length |n|. For
// each index |i|, |names[i]| and |heights[i]| denote the name and height of the
// |iᵗʰ| person. Return |names| sorted in descending order by the people's
// heights.
//

LEETCODE_BEGIN_RESOLVING(2418, SortThePeople, Solution);

class Solution {
public:
  vector<string> sortPeople(vector<string> &names, vector<int> &heights) {
    vector<string>                 res;
    map<int, string, greater<int>> tmp;
    for (int i = 0; i < heights.size(); ++i) {
      tmp.emplace(heights[i], names[i]);
    }
    for (auto &[h, name] : tmp) {
      res.emplace_back(std::move(name));
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == names.length == heights.length|
// * |1 <= n <= 10³|
// * |1 <= names[i].length <= 20|
// * |1 <= heights[i] <= 10⁵|
// * |names[i]| consists of lower and upper case English letters.
// * All the values of |heights| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: names = ["Mary","John","Emma"], heights = [180,165,170]
// Output: ["Mary","Emma","John"]
//
// Mary is the tallest, followed by Emma and John.

LEETCODE_SOLUTION_UNITTEST(2418, SortThePeople, example_1) {
  auto           solution = MakeSolution();
  vector<string> names    = {"Mary", "John", "Emma"};
  vector<int>    heights  = {180, 165, 170};
  vector<string> expect   = {"Mary", "Emma", "John"};
  vector<string> actual   = solution->sortPeople(names, heights);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: names = ["Alice","Bob","Bob"], heights = [155,185,150]
// Output: ["Bob","Alice","Bob"]
//
// The first Bob is the tallest, followed by Alice and the second Bob.

LEETCODE_SOLUTION_UNITTEST(2418, SortThePeople, example_2) {
  auto           solution = MakeSolution();
  vector<string> names    = {"Alice", "Bob", "Bob"};
  vector<int>    heights  = {155, 185, 150};
  vector<string> expect   = {"Bob", "Alice", "Bob"};
  vector<string> actual   = solution->sortPeople(names, heights);
  LCD_EXPECT_EQ(expect, actual);
}
