// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Sentence Similarity III
//
// https://leetcode.com/problems/sentence-similarity-iii/
//
// Question ID: 1813
// Difficult  : Medium
// Solve Date : 2024/10/06 13:02

#include <iosfwd>
#include <sstream>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1813. Sentence Similarity III|:
//
// You are given two strings |sentence1| and |sentence2|, each representing a
// sentence composed of words. A sentence is a list of words that are separated
// by a single space with no leading or trailing spaces. Each word consists of
// only uppercase and lowercase English characters. Two sentences |s1| and |s2|
// are considered similar if it is possible to insert an arbitrary sentence
// (possibly empty) inside one of these sentences such that the two sentences
// become equal. Note that the inserted sentence must be separated from existing
// words by spaces. For example,
//
//  • |s1 = "Hello Jane"| and |s2 = "Hello my name is Jane"| can be made equal
//  by inserting |"my name is"| between |"Hello"| and |"Jane"| in s1.
//
//  • |s1 = "Frog cool"| and |s2 = "Frogs are cool"| are not similar, since
//  although there is a sentence |"s are"| inserted into |s1|, it is not
//  separated from |"Frog"| by a space.
// Given two sentences |sentence1| and |sentence2|, return true if |sentence1|
// and |sentence2| are similar. Otherwise, return false.
//
//

LEETCODE_BEGIN_RESOLVING(1813, SentenceSimilarityIII, Solution);

class Solution {
public:
  bool areSentencesSimilar(string sentence1, string sentence2) {
    if (sentence1 == sentence2) {
      return true;
    }
    vector<string> s1;
    vector<string> s2;
    stringstream   ss1(sentence1);
    stringstream   ss2(sentence2);

    string word;
    while (ss1 >> word) {
      s1.emplace_back(std::move(word));
    }
    while (ss2 >> word) {
      s2.emplace_back(std::move(word));
    }

    int s1i  = 0;
    int s2i  = 0;
    int s1ri = s1.size() - 1;
    int s2ri = s2.size() - 1;

    while (s1i <= s1ri && s2i <= s2ri && s1[s1i] == s2[s2i]) {
      ++s1i;
      ++s2i;
    }
    while (s1i <= s1ri && s2i <= s2ri && s1[s1ri] == s2[s2ri]) {
      --s1ri;
      --s2ri;
    }
    return s1i > s1ri || s2i > s2ri;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= sentence1.length, sentence2.length <= 100|
// * |sentence1| and |sentence2| consist of lowercase and uppercase English
// letters and spaces.
// * The words in |sentence1| and |sentence2| are separated by a single space.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1813, SentenceSimilarityIII, example_1) {
  auto   solution  = MakeSolution();
  string sentence1 = "My name is Haley";
  string sentence2 = "My Haley";
  bool   expect    = true;
  bool   actual    = solution->areSentencesSimilar(sentence1, sentence2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sentence1 = "of", sentence2 = "A lot of words"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1813, SentenceSimilarityIII, example_2) {
  auto   solution  = MakeSolution();
  string sentence1 = "of";
  string sentence2 = "A lot of words";
  bool   expect    = false;
  bool   actual    = solution->areSentencesSimilar(sentence1, sentence2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: sentence1 = "Eating right now", sentence2 = "Eating"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1813, SentenceSimilarityIII, example_3) {
  auto   solution  = MakeSolution();
  string sentence1 = "Eating right now";
  string sentence2 = "Eating";
  bool   expect    = true;
  bool   actual    = solution->areSentencesSimilar(sentence1, sentence2);
  LCD_EXPECT_EQ(expect, actual);
}
