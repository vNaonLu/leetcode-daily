// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check Distances Between Same Letters
//
// https://leetcode.com/problems/check-distances-between-same-letters/
//
// Question ID: 2399
// Difficult  : Easy
// Solve Date : 2023/02/04 14:33

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2399. Check Distances Between Same Letters|:
//
// You are given a 0-indexed string |s| consisting of only lowercase English
// letters, where each letter in |s| appears exactly twice. You are also given a
// 0-indexed integer array |distance| of length |26|. Each letter in the
// alphabet is numbered from |0| to |25| (i.e. |'a' -> 0|, |'b' -> 1|, |'c' ->
// 2|, ... , |'z' -> 25|). In a well-spaced string, the number of letters
// between the two occurrences of the |iᵗʰ| letter is |distance[i]|. If the
// |iᵗʰ| letter does not appear in |s|, then |distance[i]| can be ignored.
// Return |true| if |s| is a well-spaced string, otherwise return |false|.
//

LEETCODE_BEGIN_RESOLVING(2399, CheckDistancesBetweenSameLetters, Solution);

class Solution {
public:
  bool checkDistances(string s, vector<int> &distance) {
    vector<int> tmp(26, -1);
    for (int i = 0; i < s.size(); ++i) {
      auto c = s[i];
      if (tmp[c - 'a'] < 0) {
        tmp[c - 'a'] = i;
      } else {
        tmp[c - 'a'] = i - 1 - tmp[c - 'a'];
      }
    }
    for (int i = 0; i < tmp.size(); ++i) {
      if (tmp[i] != -1 && tmp[i] != distance[i]) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 52|
// * |s| consists only of lowercase English letters.
// * Each letter appears in |s| exactly twice.
// * |distance.length == 26|
// * |0 <= distance[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abaccb", distance =
//  [1,3,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
// Output: true
//
// - 'a' appears at indices 0 and 2 so it satisfies distance[0] = 1.
// - 'b' appears at indices 1 and 5 so it satisfies distance[1] = 3.
// - 'c' appears at indices 3 and 4 so it satisfies distance[2] = 0.
// Note that distance[3] = 5, but since 'd' does not appear in s, it can be
// ignored. Return true because s is a well-spaced string.

LEETCODE_SOLUTION_UNITTEST(2399, CheckDistancesBetweenSameLetters, example_1) {
  auto        solution = MakeSolution();
  string      s        = "abaccb";
  vector<int> distance = {1, 3, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  bool        expect   = true;
  bool        actual   = solution->checkDistances(s, distance);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aa", distance =
//  [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
// Output: false
//
// - 'a' appears at indices 0 and 1 so there are zero letters between them.
// Because distance[0] = 1, s is not a well-spaced string.

LEETCODE_SOLUTION_UNITTEST(2399, CheckDistancesBetweenSameLetters, example_2) {
  auto        solution = MakeSolution();
  string      s        = "aa";
  vector<int> distance = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  bool        expect   = false;
  bool        actual   = solution->checkDistances(s, distance);
  LCD_EXPECT_EQ(expect, actual);
}
