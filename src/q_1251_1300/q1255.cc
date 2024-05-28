// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Score Words Formed by Letters
//
// https://leetcode.com/problems/maximum-score-words-formed-by-letters/
//
// Question ID: 1255
// Difficult  : Hard
// Solve Date : 2024/05/24 22:03

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1255. Maximum Score Words Formed by Letters|:
//
// Given a list of |words|, list of  single |letters| (might be repeating) and
// |score| of every character. Return the maximum score of any valid set of
// words formed by using the given letters ( |words[i]| cannot be used two or
// more times). It is not necessary to use all characters in |letters| and each
// letter can only be used once. Score of letters |'a'|, |'b'|, |'c'|, ... ,
// |'z'| is given by |score[0]|, |score[1]|, ... , |score[25]| respectively.
//
//

LEETCODE_BEGIN_RESOLVING(1255, MaximumScoreWordsFormedByLetters, Solution);

class Solution {
public:
  int maxScoreWords(vector<string> &words, vector<char> &letters,
                    vector<int> &score) {
    vector<int> a(26, 0);
    vector<int> b(26, 0);
    int         res = 0;
    for (auto x : letters) {
      ++a[x - 'a'];
    }
    helper(&a, &b, &res, 0, words, score);
    return res;
  }

private:
  void helper(vector<int> *a, vector<int> *b, int *res, int idx,
              vector<string> const &words, vector<int> const &score) {
    if (idx == words.size()) {
      int sc = 0;
      for (int i = 0; i < 26; ++i) {
        if ((*b)[i] > (*a)[i]) {
          return;
        }
        sc += score[i] * (*b)[i];
      }
      *res = max(*res, sc);
      return;
    }

    helper(a, b, res, idx + 1, words, score);
    for (auto x : words[idx]) {
      ++(*b)[x - 'a'];
    }
    helper(a, b, res, idx + 1, words, score);
    for (auto x : words[idx]) {
      --(*b)[x - 'a'];
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 14|
// * |1 <= words[i].length <= 15|
// * |1 <= letters.length <= 100|
// * |letters[i].length == 1|
// * |score.length == 26|
// * |0 <= score[i] <= 10|
// * |words[i]|, |letters[i]| contains only lower case English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["dog","cat","dad","good"], letters =
//  ["a","a","c","d","d","d","g","o","o"], score =
//  [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
// Output: 23
//

LEETCODE_SOLUTION_UNITTEST(1255, MaximumScoreWordsFormedByLetters, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"dog", "cat", "dad", "good"};
  vector<char>   letters  = {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'};
  vector<int>    score    = {1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0,
                             0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int            expect   = 23;
  int            actual   = solution->maxScoreWords(words, letters, score);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["xxxz","ax","bx","cx"], letters =
//  ["z","a","b","c","x","x","x"], score =
//  [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]
// Output: 27
//

LEETCODE_SOLUTION_UNITTEST(1255, MaximumScoreWordsFormedByLetters, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"xxxz", "ax", "bx", "cx"};
  vector<char>   letters  = {'z', 'a', 'b', 'c', 'x', 'x', 'x'};
  vector<int>    score    = {4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10};
  int            expect   = 27;
  int            actual   = solution->maxScoreWords(words, letters, score);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["leetcode"], letters = ["l","e","t","c","o","d"], score =
//  [0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1255, MaximumScoreWordsFormedByLetters, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"leetcode"};
  vector<char>   letters  = {'l', 'e', 't', 'c', 'o', 'd'};
  vector<int>    score    = {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0,
                             0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
  int            expect   = 0;
  int            actual   = solution->maxScoreWords(words, letters, score);
  LCD_EXPECT_EQ(expect, actual);
}
