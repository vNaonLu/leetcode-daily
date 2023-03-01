// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Common Prefix
//
// https://leetcode.com/problems/longest-common-prefix/
//
// Question ID: 14
// Difficult  : Easy
// Solve Date : 2021/11/07 15:25

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |14. Longest Common Prefix|:
//
// Write a function to find the longest common prefix string amongst an array of
// strings. If there is no common prefix, return an empty string |""|.  
//

LEETCODE_BEGIN_RESOLVING(14, LongestCommonPrefix, Solution);

class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    auto &fst = strs.front();
    auto  end = fst.end();
    for (auto it = strs.begin() + 1; it != strs.end(); ++it) {
      auto local  = fst.begin();
      auto it_beg = (*it).begin();
      while (local != end && it_beg != (*it).end()) {
        if (*local != *it_beg) {
          break;
        }
        ++local;
        ++it_beg;
      }
      end = local;
    }
    return string(fst.begin(), end);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= strs.length <= 200|
// * |0 <= strs[i].length <= 200|
// * |strs[i]| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: strs = ["flower","flow","flight"]
// Output: "fl"
//

LEETCODE_SOLUTION_UNITTEST(14, LongestCommonPrefix, example_1) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"flower", "flow", "flight"};
  string         expect   = "fl";
  string         actual   = solution->longestCommonPrefix(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: strs = ["dog","racecar","car"]
// Output: ""
//
// There is no common prefix among the input strings.

LEETCODE_SOLUTION_UNITTEST(14, LongestCommonPrefix, example_2) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"dog", "racecar", "car"};
  string         expect   = "";
  string         actual   = solution->longestCommonPrefix(strs);
  LCD_EXPECT_EQ(expect, actual);
}
