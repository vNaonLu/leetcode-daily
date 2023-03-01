// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Positions of Large Groups
//
// https://leetcode.com/problems/positions-of-large-groups/
//
// Question ID: 830
// Difficult  : Easy
// Solve Date : 2022/07/10 14:13

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |830. Positions of Large Groups|:
//
// In a string |s|of lowercase letters, these letters form consecutive groups of
// the same character. For example, a string like |s = "abbxxxxzyy"| has the
// groups |"a"|, |"bb"|, |"xxxx"|, |"z"|, and |"yy"|. A group is identified by
// an interval |[start, end]|, where |start|and |end|denote the start and
// endindices (inclusive) of the group. In the above example, |"xxxx"|has the
// interval |[3,6]|. A group is consideredlargeif it has 3 or more characters.
// Returnthe intervals of every large group sorted inincreasing order by start
// index.
//

LEETCODE_BEGIN_RESOLVING(830, PositionsOfLargeGroups, Solution);

class Solution {
public:
  vector<vector<int>> largeGroupPositions(string s) {
    vector<vector<int>> res;
    int                 l = 0;

    for (int i = 1; i < s.size(); ++i) {
      if (s[l] != s[i]) {
        if (i - l >= 3) {
          res.emplace_back(vector<int>{l, i - 1});
        }
        l = i;
      }
    }

    if (s.size() - l >= 3) {
      res.emplace_back(vector<int>{l, (int)s.size() - 1});
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| contains lowercase English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abbxxxxzzy"
// Output: [[3,6]]
//
// |"xxxx" is the only |large group with start index 3 and end index 6.

LEETCODE_SOLUTION_UNITTEST(830, PositionsOfLargeGroups, example_1) {
  auto                solution = MakeSolution();
  string              s        = "abbxxxxzzy";
  vector<vector<int>> expect   = {
      {3, 6}
  };
  vector<vector<int>> actual = solution->largeGroupPositions(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abc"
// Output: []
//
// We have groups "a", "b", and "c", none of which are large groups.

LEETCODE_SOLUTION_UNITTEST(830, PositionsOfLargeGroups, example_2) {
  auto                solution = MakeSolution();
  string              s        = "abc";
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->largeGroupPositions(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abcdddeeeeaabbbcd"
// Output: [[3,5],[6,9],[12,14]]
//
// The large groups are "ddd", "eeee", and "bbb".

LEETCODE_SOLUTION_UNITTEST(830, PositionsOfLargeGroups, example_3) {
  auto                solution = MakeSolution();
  string              s        = "abcdddeeeeaabbbcd";
  vector<vector<int>> expect   = {
      { 3,  5},
      { 6,  9},
      {12, 14}
  };
  vector<vector<int>> actual = solution->largeGroupPositions(s);
  LCD_EXPECT_EQ(expect, actual);
}
