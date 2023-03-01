// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Ransom Note
//
// https://leetcode.com/problems/ransom-note/
//
// Question ID: 383
// Difficult  : Easy
// Solve Date : 2021/09/10 08:00

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |383. Ransom Note|:
//
// Given two strings |ransomNote| and |magazine|, return |true| if |ransomNote|
// can be constructed by using the letters from |magazine| and |false|
// otherwise. Each letter in |magazine| can only be used once in |ransomNote|.  
//

LEETCODE_BEGIN_RESOLVING(383, RansomNote, Solution);

class Solution {
private:
  template <typename Iterator>
  auto getDictionary(Iterator beg, Iterator end) {
    auto res = unordered_map<typename Iterator::value_type, uint32_t>();
    while (beg != end) {
      ++res[*beg++];
    }
    return res;
  }

public:
  bool canConstruct(string ransomNote, string magazine) {
    auto dict = getDictionary(magazine.begin(), magazine.end());
    auto beg  = ransomNote.begin();
    while (beg != ransomNote.end()) {
      auto find = dict.find(*beg++);
      if (find == dict.end() || find->second == 0) {
        return false;
      }
      --find->second;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= ransomNote.length, magazine.length <= 10⁵|
// * |ransomNote| and |magazine| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ransomNote = "a", magazine = "b"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(383, RansomNote, example_1) {
  auto   solution   = MakeSolution();
  string ransomNote = "a";
  string magazine   = "b";
  bool   expect     = false;
  bool   actual     = solution->canConstruct(ransomNote, magazine);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ransomNote = "aa", magazine = "ab"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(383, RansomNote, example_2) {
  auto   solution   = MakeSolution();
  string ransomNote = "aa";
  string magazine   = "ab";
  bool   expect     = false;
  bool   actual     = solution->canConstruct(ransomNote, magazine);
  EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: ransomNote = "aa", magazine = "aab"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(383, RansomNote, example_3) {
  auto   solution   = MakeSolution();
  string ransomNote = "aa";
  string magazine   = "aab";
  bool   expect     = true;
  bool   actual     = solution->canConstruct(ransomNote, magazine);
  EXPECT_EQ(expect, actual);
}
