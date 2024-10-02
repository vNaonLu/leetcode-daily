// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Sum of Prefix Scores of Strings
//
// https://leetcode.com/problems/sum-of-prefix-scores-of-strings/
//
// Question ID: 2416
// Difficult  : Hard
// Solve Date : 2024/09/25 21:49

#include <iosfwd>
#include <map>
#include <memory>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2416. Sum of Prefix Scores of Strings|:
//
// You are given an array |words| of size |n| consisting of non-empty strings.
// We define the score of a string |word| as the number of strings |words[i]|
// such that |word| is a prefix of |words[i]|.
//
//  • For example, if |words = ["a", "ab", "abc", "cab"]|, then the score of
//  |"ab"| is |2|, since |"ab"| is a prefix of both |"ab"| and |"abc"|.
// Return an array |answer| of size |n| where |answer[i]| is the sum of scores
// of every non-empty prefix of |words[i]|. Note that a string is considered as
// a prefix of itself.
//
//

LEETCODE_BEGIN_RESOLVING(2416, SumOfPrefixScoresOfStrings, Solution);

class Solution {
public:
  vector<int> sumPrefixScores(vector<string> &words) {
    Trie t;
    for (auto &s : words) {
      t.add(s, 0);
    }
    vector<int> res;
    for (auto &s : words) {
      res.push_back(t.dfs(s, 0));
    }
    return res;
  }

private:
  class Trie {
  public:
    Trie() : score{0} {}
    void add(string const &s, int i) {
      if (i) {
        ++score;
      }

      if (i == s.size()) {
        return;
      }

      if (!children[s[i]]) {
        children[s[i]] = make_unique<Trie>();
      }

      children[s[i]]->add(s, i + 1);
    }

    int dfs(string const &s, int i) {
      if (i == s.size()) {
        return score;
      }

      return score + children[s[i]]->dfs(s, i + 1);
    }

  private:
    int                         score;
    map<char, unique_ptr<Trie>> children;
  };
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length <= 1000|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["abc","ab","bc","b"]
// Output: [5,4,3,2]
//

LEETCODE_SOLUTION_UNITTEST(2416, SumOfPrefixScoresOfStrings, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abc", "ab", "bc", "b"};
  vector<int>    expect   = {5, 4, 3, 2};
  vector<int>    actual   = solution->sumPrefixScores(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["abcd"]
// Output: [4]
//

LEETCODE_SOLUTION_UNITTEST(2416, SumOfPrefixScoresOfStrings, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abcd"};
  vector<int>    expect   = {4};
  vector<int>    actual   = solution->sumPrefixScores(words);
  LCD_EXPECT_EQ(expect, actual);
}
