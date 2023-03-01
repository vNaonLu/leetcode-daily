// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Word Ladder
//
// https://leetcode.com/problems/word-ladder/
//
// Question ID: 127
// Difficult  : Hard
// Solve Date : 2022/02/12 16:27

#include <iosfwd>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |127. Word Ladder|:
//
// A transformation sequence from word |beginWord| to word |endWord| using a
// dictionary |wordList| is a sequence of words |beginWord -> s₁ -> s₂ -> ... ->
// sₖ| such that:
//
//  • Every adjacent pair of words differs by a single letter.
//
//  • Every |sᵢ| for |1 <= i <= k| is in |wordList|. Note that |beginWord| does
//  not need to be in |wordList|.
//
//  • |sₖ == endWord|
// Given two words, |beginWord| and |endWord|, and a dictionary |wordList|,
// return the number of words in the shortest transformation sequence from
// |beginWord| to |endWord|, or |0| if no such sequence exists.  
//

LEETCODE_BEGIN_RESOLVING(127, WordLadder, Solution);

class Solution {
public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    unordered_set<string> words(wordList.begin(), wordList.end());
    unordered_set<string> memos;
    queue<string>         step;
    int                   res = 0;
    step.emplace(move(beginWord));
    memos.insert(step.front());
    while (true != step.empty()) {
      queue<string> curr = move(step);
      ++res;
      while (true != curr.empty()) {
        auto s = curr.front();
        curr.pop();
        if (s == endWord)
          return res;
        for (int i = 0; i < s.size(); ++i) {
          string new_word = s;
          for (char c = 'a'; c <= 'z'; ++c) {
            new_word[i] = c;
            if (memos.find(new_word) == memos.end() &&
                words.find(new_word) != words.end()) {
              memos.insert(new_word);
              step.emplace(new_word);
            }
          }
        }
      }
    }
    return 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= beginWord.length <= 10|
// * |endWord.length == beginWord.length|
// * |1 <= wordList.length <= 5000|
// * |wordList[i].length == beginWord.length|
// * |beginWord|, |endWord|, and |wordList[i]| consist of lowercase English
// letters.
// * |beginWord != endWord|
// * All the words in |wordList| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: beginWord = "hit", endWord = "cog", wordList =
//  ["hot","dot","dog","lot","log","cog"]
// Output: 5
//
// One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" ->
// cog", which is 5 words long.

LEETCODE_SOLUTION_UNITTEST(127, WordLadder, example_1) {
  auto           solution  = MakeSolution();
  string         beginWord = "hit";
  string         endWord   = "cog";
  vector<string> wordList  = {"hot", "dot", "dog", "lot", "log", "cog"};
  int            expect    = 5;
  int            actual = solution->ladderLength(beginWord, endWord, wordList);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: beginWord = "hit", endWord = "cog", wordList =
//  ["hot","dot","dog","lot","log"]
// Output: 0
//
// The endWord "cog" is not in wordList, therefore there is no valid
// transformation sequence.

LEETCODE_SOLUTION_UNITTEST(127, WordLadder, example_2) {
  auto           solution  = MakeSolution();
  string         beginWord = "hit";
  string         endWord   = "cog";
  vector<string> wordList  = {"hot", "dot", "dog", "lot", "log"};
  int            expect    = 0;
  int            actual = solution->ladderLength(beginWord, endWord, wordList);
  LCD_EXPECT_EQ(expect, actual);
}
