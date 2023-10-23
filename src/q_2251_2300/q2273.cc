// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Resultant Array After Removing Anagrams
//
// https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/
//
// Question ID: 2273
// Difficult  : Easy
// Solve Date : 2023/10/17 20:24

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2273. Find Resultant Array After Removing Anagrams|:
//
// You are given a 0-indexed string array |words|, where |words[i]| consists of
// lowercase English letters. In one operation, select any index |i| such that
// |0 < i < words.length| and |words[i - 1]| and |words[i]| are anagrams, and
// delete |words[i]| from |words|. Keep performing this operation as long as you
// can select an index that satisfies the conditions. Return |words| after
// performing all operations. It can be shown that selecting the indices for
// each operation in any arbitrary order will lead to the same result. An
// Anagram is a word or phrase formed by rearranging the letters of a different
// word or phrase using all the original letters exactly once. For example,
// |"dacb"| is an anagram of |"abdc"|.
//
//

LEETCODE_BEGIN_RESOLVING(2273, FindResultantArrayAfterRemovingAnagrams,
                         Solution);

class Solution {
public:
  vector<string> removeAnagrams(vector<string> &words) {
    vector<string> res;
    string         prev;
    for (auto &s : words) {
      auto h = hashWord(s);
      if (prev != h) {
        res.emplace_back(s);
        prev = std::move(h);
      }
    }
    return res;
  }

private:
  string hashWord(const string &s) {
    string res;
    res.resize(26, '0');
    for (auto c : s) {
      ++res[c - 'a'];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 10|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["abba","baba","bbaa","cd","cd"]
// Output: ["abba","cd"]
//
// One of the ways we can obtain the resultant array is by using the following
// operations:
// - Since words[2] = "bbaa" and words[1] = "baba" are anagrams, we choose index
// 2 and delete words[2].
//  Now words = ["abba","baba","cd","cd"].
// - Since words[1] = "baba" and words[0] = "abba" are anagrams, we choose index
// 1 and delete words[1].
//  Now words = ["abba","cd","cd"].
// - Since words[2] = "cd" and words[1] = "cd" are anagrams, we choose index 2
// and delete words[2].
//  Now words = ["abba","cd"].
// We can no longer perform any operations, so ["abba","cd"] is the final
// answer.

LEETCODE_SOLUTION_UNITTEST(2273, FindResultantArrayAfterRemovingAnagrams,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abba", "baba", "bbaa", "cd", "cd"};
  vector<string> expect   = {"abba", "cd"};
  vector<string> actual   = solution->removeAnagrams(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a","b","c","d","e"]
// Output: ["a","b","c","d","e"]
//
// No two adjacent strings in words are anagrams of each other, so no operations
// are performed.

LEETCODE_SOLUTION_UNITTEST(2273, FindResultantArrayAfterRemovingAnagrams,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "b", "c", "d", "e"};
  vector<string> expect   = {"a", "b", "c", "d", "e"};
  vector<string> actual   = solution->removeAnagrams(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: ["a","b","a"]
// Output: ["a","b","a"]
//

LEETCODE_SOLUTION_UNITTEST(2273, FindResultantArrayAfterRemovingAnagrams,
                           extra_testcase_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "b", "a"};
  vector<string> expect   = {"a", "b", "a"};
  vector<string> actual   = solution->removeAnagrams(words);
  LCD_EXPECT_EQ(expect, actual);
}
