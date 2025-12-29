// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Pyramid Transition Matrix
//
// https://leetcode.com/problems/pyramid-transition-matrix/
//
// Question ID: 756
// Difficult  : Medium
// Solve Date : 2024/06/13 21:14

#include <iosfwd>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |756. Pyramid Transition Matrix|:
//
// You are stacking blocks to form a pyramid. Each block has a color, which is
// represented by a single letter. Each row of blocks contains one less block
// than the row beneath it and is centered on top. To make the pyramid
// aesthetically pleasing, there are only specific triangular patterns that are
// allowed. A triangular pattern consists of a single block stacked on top of
// two blocks. The patterns are given as a list of three-letter strings
// |allowed|, where the first two characters of a pattern represent the left and
// right bottom blocks respectively, and the third character is the top block.
//
//  • For example, |"ABC"| represents a triangular pattern with a |'C'| block
//  stacked on top of an |'A'| (left) and |'B'| (right) block. Note that this is
//  different from |"BAC"| where |'B'| is on the left bottom and |'A'| is on the
//  right bottom.
// You start with a bottom row of blocks |bottom|, given as a single string,
// that you must use as the base of the pyramid. Given |bottom| and |allowed|,
// return |true| if you can build the pyramid all the way to the top such that
// every triangular pattern in the pyramid is in |allowed|, or |false|
// otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(756, PyramidTransitionMatrix, Solution);

class Solution {
public:
  bool pyramidTransition(string bottom, vector<string> &allowed) {
    unordered_map<string_view, unordered_set<char>> mp;
    for (auto &s : allowed) {
      string_view sv = s;
      mp[sv.substr(0, 2)].emplace(s[2]);
    }
    return dfs(mp, bottom);
  }

private:
  template <typename MapType>
  vector<string> iterateNextLayer(MapType const &mp, string_view layer) {
    vector<string> res = {""};
    auto           n   = layer.size();

    res.reserve(layer.size());
    for (int i = 0; i < n - 1; ++i) {
      auto key  = layer.substr(i, 2);
      auto find = mp.find(key);
      if (find == mp.end()) {
        return {};
      }

      decltype(res) next;
      next.reserve(layer.size());
      for (auto &s : res) {
        for (auto c : find->second) {
          next.emplace_back(s + c);
        }
      }

      res = std::move(next);
    }
    return res;
  }

  template <typename MapType>
  bool dfs(MapType const &mp, string_view layer) {
    if (layer.size() == 1) {
      return true;
    }

    if (auto [_, ok] = tried_but_failed_.emplace(layer); !ok) {
      return false;
    }

    for (auto &s : iterateNextLayer(mp, layer)) {
      if (dfs(mp, s)) {
        return true;
      }
    }

    return false;
  }

  unordered_set<string> tried_but_failed_;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= bottom.length <= 6|
// * |0 <= allowed.length <= 216|
// * |allowed[i].length == 3|
// * The letters in all input strings are from the set |{'A', 'B', 'C', 'D',
// 'E', 'F'}|.
// * All the values of |allowed| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(756, PyramidTransitionMatrix, example_1) {
  auto           solution = MakeSolution();
  string         bottom   = "BCD";
  vector<string> allowed  = {"BCC", "CDE", "CEA", "FFF"};
  bool           expect   = true;
  bool           actual   = solution->pyramidTransition(bottom, allowed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: bottom = "AAAA", allowed = ["AAB","AAC","BCD","BBE","DEF"]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(756, PyramidTransitionMatrix, example_2) {
  auto           solution = MakeSolution();
  string         bottom   = "AAAA";
  vector<string> allowed  = {"AAB", "AAC", "BCD", "BBE", "DEF"};
  bool           expect   = false;
  bool           actual   = solution->pyramidTransition(bottom, allowed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "ABBBBA"
// ["ACA","ACF","ACE","ACD","ABA","ABF","ABE","ABD","FCA","FCF","FCE","FCD","FBA","FBF","FBE","FBD","ECA","ECF","ECE","ECD","EBA","EBF","EBE","EBD","DCA","DCF","DCE","DCD","DBA","DBF","DBE","DBD","CAA","CAF","CAE","CAD","CFA","CFF","CFE","CFD","CEA","CEF","CEE","CED","CDA","CDF","CDE","CDD","BAA","BAF","BAE","BAD","BFA","BFF","BFE","BFD","BEA","BEF","BEE","BED","BDA","BDF","BDE","BDD","CCA","CCF","CCE","CCD","CBA","CBF","CBE","CBD","BCA","BCF","BCE","BCD","BBA","BBF","BBE","BBD","CCC","CCB","CBC","CBB","BCC","BCB","BBC","BBB"]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST_WITH_TIMED_OUT(756, PyramidTransitionMatrix,
                                          extra_testcase_1, 4021) {
  auto           solution = MakeSolution();
  string         bottom   = "ABBBBA";
  vector<string> allowed  = {
      "ACA", "ACF", "ACE", "ACD", "ABA", "ABF", "ABE", "ABD", "FCA", "FCF",
      "FCE", "FCD", "FBA", "FBF", "FBE", "FBD", "ECA", "ECF", "ECE", "ECD",
      "EBA", "EBF", "EBE", "EBD", "DCA", "DCF", "DCE", "DCD", "DBA", "DBF",
      "DBE", "DBD", "CAA", "CAF", "CAE", "CAD", "CFA", "CFF", "CFE", "CFD",
      "CEA", "CEF", "CEE", "CED", "CDA", "CDF", "CDE", "CDD", "BAA", "BAF",
      "BAE", "BAD", "BFA", "BFF", "BFE", "BFD", "BEA", "BEF", "BEE", "BED",
      "BDA", "BDF", "BDE", "BDD", "CCA", "CCF", "CCE", "CCD", "CBA", "CBF",
      "CBE", "CBD", "BCA", "BCF", "BCE", "BCD", "BBA", "BBF", "BBE", "BBD",
      "CCC", "CCB", "CBC", "CBB", "BCC", "BCB", "BBC", "BBB"};
  bool expect = false;
  bool actual = solution->pyramidTransition(bottom, allowed);
  LCD_EXPECT_EQ(expect, actual);
}
