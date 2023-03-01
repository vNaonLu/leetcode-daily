// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Group Anagrams
//
// https://leetcode.com/problems/group-anagrams/
//
// Question ID: 49
// Difficult  : Medium
// Solve Date : 2021/09/26 17:38

#include <algorithm>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |49. Group Anagrams|:
//
// Given an array of strings |strs|, group the anagrams together. You can return
// the answer in any order. An Anagram is a word or phrase formed by rearranging
// the letters of a different word or phrase, typically using all the original
// letters exactly once.  
//

LEETCODE_BEGIN_RESOLVING(49, GroupAnagrams, Solution);

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    map<vector<char>, vector<string>> mapping;
    for (const auto &s : strs) {
      vector<char> key(s.begin(), s.end());
      sort(key.begin(), key.end());
      mapping[key].push_back(s);
    }
    vector<vector<string>> res;
    for (auto it = mapping.begin(); it != mapping.end(); ++it) {
      res.push_back(it->second);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= strs.length <= 10⁴|
// * |0 <= strs[i].length <= 100|
// * |strs[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: strs = ["eat","tea","tan","ate","nat","bat"]
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
//

LEETCODE_SOLUTION_UNITTEST(49, GroupAnagrams, example_1) {
  auto                   solution = MakeSolution();
  vector<string>         strs     = {"eat", "tea", "tan", "ate", "nat", "bat"};
  vector<vector<string>> expect   = {
      {"bat"},
      {"nat", "tan"},
      {"ate", "eat", "tea"}
  };
  vector<vector<string>> actual = solution->groupAnagrams(strs);
  EXPECT_ANYORDER_WITH_DEPTH_EQ(1, expect, actual);
}

// [Example #2]
//  Input: strs = [""]
// Output: [[""]]
//

LEETCODE_SOLUTION_UNITTEST(49, GroupAnagrams, example_2) {
  auto                   solution = MakeSolution();
  vector<string>         strs     = {""};
  vector<vector<string>> expect   = {{""}};
  vector<vector<string>> actual   = solution->groupAnagrams(strs);
  EXPECT_ANYORDER_WITH_DEPTH_EQ(1, expect, actual);
}

// [Example #3]
//  Input: strs = ["a"]
// Output: [["a"]]
//

LEETCODE_SOLUTION_UNITTEST(49, GroupAnagrams, example_3) {
  auto                   solution = MakeSolution();
  vector<string>         strs     = {"a"};
  vector<vector<string>> expect   = {{"a"}};
  vector<vector<string>> actual   = solution->groupAnagrams(strs);
  EXPECT_ANYORDER_EQ(expect, actual);
}
