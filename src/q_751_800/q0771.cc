// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Jewels and Stones
//
// https://leetcode.com/problems/jewels-and-stones/
//
// Question ID: 771
// Difficult  : Easy
// Solve Date : 2022/02/21 23:48

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |771. Jewels and Stones|:
//
// You're given strings |jewels| representing the types of stones that are
// jewels, and |stones| representing the stones you have. Each character in
// |stones| is a type of stone you have. You want to know how many of the stones
// you have are also jewels. Letters are case sensitive, so |"a"| is considered
// a different type of stone from |"A"|.  
//

LEETCODE_BEGIN_RESOLVING(771, JewelsAndStones, Solution);

class Solution {
public:
  int numJewelsInStones(string jewels, string stones) {
    unordered_set<char> jewels_set(jewels.begin(), jewels.end());
    int                 res = 0;
    for (const auto &c : stones) {
      if (jewels_set.find(c) != jewels_set.end()) {
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
// * |1 <= jewels.length, stones.length <= 50|
// * |jewels| and |stones| consist of only English letters.
// * All the characters of  |jewels| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: jewels = "aA", stones = "aAAbbbb"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(771, JewelsAndStones, example_1) {
  auto   solution = MakeSolution();
  string jewels   = "aA";
  string stones   = "aAAbbbb";
  int    expect   = 3;
  int    actual   = solution->numJewelsInStones(jewels, stones);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: jewels = "z", stones = "ZZ"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(771, JewelsAndStones, example_2) {
  auto   solution = MakeSolution();
  string jewels   = "z";
  string stones   = "ZZ";
  int    expect   = 0;
  int    actual   = solution->numJewelsInStones(jewels, stones);
  LCD_EXPECT_EQ(expect, actual);
}
