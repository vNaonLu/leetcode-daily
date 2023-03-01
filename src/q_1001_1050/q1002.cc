// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Common Characters
//
// https://leetcode.com/problems/find-common-characters/
//
// Question ID: 1002
// Difficult  : Easy
// Solve Date : 2021/11/24 18:10

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1002. Find Common Characters|:
//
// Given a string array |words|, return an array of all characters that show up
// in all strings within the |words| (including duplicates). You may return the
// answer in any order.  
//

LEETCODE_BEGIN_RESOLVING(1002, FindCommonCharacters, Solution);

class Solution {
public:
  vector<string> commonChars(vector<string> &words) {
    vector<unordered_map<char, int>> counts(words.size());
    for (int i = 0; i < words.size(); ++i)
      for (const auto &c : words[i])
        ++counts[i][c];
    vector<string> res;
    for (auto &m : counts.front()) {
      while (m.second--) {
        bool common = true;
        for (int i = 1; i < counts.size() && common; ++i)
          if (!counts[i].count(m.first) || counts[i][m.first]-- <= 0)
            common = false;
        if (common)
          res.emplace_back(1, m.first);
        else
          break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 100|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["bella","label","roller"]
// Output: ["e","l","l"]
//

LEETCODE_SOLUTION_UNITTEST(1002, FindCommonCharacters, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"bella", "label", "roller"};
  vector<string> expect   = {"e", "l", "l"};
  vector<string> actual   = solution->commonChars(words);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["cool","lock","cook"]
// Output: ["c","o"]
//

LEETCODE_SOLUTION_UNITTEST(1002, FindCommonCharacters, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"cool", "lock", "cook"};
  vector<string> expect   = {"c", "o"};
  vector<string> actual   = solution->commonChars(words);
  EXPECT_ANYORDER_EQ(expect, actual);
}
