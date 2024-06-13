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
#include <unordered_map>
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
    unordered_map<string, vector<char>> mp;
    for (auto &s : allowed) {
      mp[s.substr(0, 2)].emplace_back(s[2]);
    }
    string tmp;
    return iterateNextLayer(mp, bottom.begin(), bottom.end(), &tmp);
  }

private:
  template <typename MapType, typename It>
  bool iterateNextLayer(MapType const &mp, It beg, It end, string *cur_layer) {
    if (beg == end || beg + 1 == end) {
      if (cur_layer->size() == 1) {
        return true;
      }

      string tmp;
      return iterateNextLayer(mp, cur_layer->begin(), cur_layer->end(), &tmp);
    }

    string key  = (string("") + *beg) + *(beg + 1);
    auto   find = mp.find(key);
    if (find == mp.end()) {
      // not found
      return false;
    }

    for (auto c : find->second) {
      cur_layer->push_back(c);
      if (iterateNextLayer(mp, beg + 1, end, cur_layer)) {
        return true;
      }
      cur_layer->pop_back();
    }

    return false;
  }
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
