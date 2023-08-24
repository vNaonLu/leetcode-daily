// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shuffle String
//
// https://leetcode.com/problems/shuffle-string/
//
// Question ID: 1528
// Difficult  : Easy
// Solve Date : 2023/08/24 19:54

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1528. Shuffle String|:
//
// You are given a string |s| and an integer array |indices| of the same length.
// The string |s| will be shuffled such that the character at the |iᵗʰ| position
// moves to |indices[i]| in the shuffled string. Return the shuffled string.
//
//

LEETCODE_BEGIN_RESOLVING(1528, ShuffleString, Solution);

class Solution {
public:
  string restoreString(string s, vector<int> &indices) {
    string res(s.size(), ' ');
    auto   beg = s.begin();
    for (auto i : indices) {
      res[i] = *beg++;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |s.length == indices.length == n|
// * |1 <= n <= 100|
// * |s| consists of only lowercase English letters.
// * |0 <= indices[i] < n|
// * All values of |indices| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "codeleet", indices = [4,5,6,7,0,2,1,3]
// Output: "leetcode"
//
// As shown, "codeleet" becomes "leetcode" after shuffling.

LEETCODE_SOLUTION_UNITTEST(1528, ShuffleString, example_1) {
  auto        solution = MakeSolution();
  string      s        = "codeleet";
  vector<int> indices  = {4, 5, 6, 7, 0, 2, 1, 3};
  string      expect   = "leetcode";
  string      actual   = solution->restoreString(s, indices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abc", indices = [0,1,2]
// Output: "abc"
//
// After shuffling, each character remains in its position.

LEETCODE_SOLUTION_UNITTEST(1528, ShuffleString, example_2) {
  auto        solution = MakeSolution();
  string      s        = "abc";
  vector<int> indices  = {0, 1, 2};
  string      expect   = "abc";
  string      actual   = solution->restoreString(s, indices);
  LCD_EXPECT_EQ(expect, actual);
}
