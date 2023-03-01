// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Add and Search Words Data Structure
//
// https://leetcode.com/problems/design-add-and-search-words-data-structure/
//
// Question ID: 211
// Difficult  : Medium
// Solve Date : 2022/01/28 18:12

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |211. Design Add and Search Words Data Structure|:
//
// Design a data structure that supports adding new words and finding if a
// string matches any previously added string. Implement the |WordDictionary|
// class:
//
//  • |WordDictionary()| Initializes the object.
//
//  • |void addWord(word)| Adds |word| to the data structure, it can be matched
//  later.
//
//  • |bool search(word)| Returns |true| if there is any string in the data
//  structure that matches |word| or |false| otherwise. |word| may contain dots
//  |'.'| where dots can be matched with any letter.
//  
//

LEETCODE_BEGIN_RESOLVING(211, DesignAddAndSearchWordsDataStructure,
                         WordDictionary);

class WordDictionary {
private:
  struct trie {
    unordered_map<char, trie *> next;
    bool                        is_end = false;
  } *head = nullptr;

  bool searchHelper(string_view s, trie *p, size_t i = 0) {
    if (i == s.size() && p->is_end)
      return true;
    auto c = s[i];
    if (c != '.' && !p->next.count(c))
      return false;
    else if (c != '.')
      return searchHelper(s, p->next[c], i + 1);
    else {
      for (auto &[k, v] : p->next) {
        if (searchHelper(s, v, i + 1))
          return true;
      }
      return false;
    }
  }

public:
  WordDictionary() { head = new trie(); }

  void addWord(string word) {
    trie *p = head;
    for (const auto &c : word) {
      if (!p->next.count(c)) {
        p->next[c] = new trie();
      }
      p = p->next[c];
    }
    p->is_end = true;
  }

  bool search(string word) { return searchHelper(word, head); }
};

LEETCODE_END_RESOLVING(WordDictionary);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 25|
// * |word| in |addWord| consists of lowercase English letters.
// * |word| in |search| consist of |'.'| or lowercase English letters.
// * There will be at most |3| dots in |word| for |search| queries.
// * At most |10⁴| calls will be made to |addWord| and |search|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input:
//  ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
// [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
// Output: [null,null,null,null,false,true,true,true]
//
// WordDictionary wordDictionary = new WordDictionary();
// wordDictionary.addWord("bad");
// wordDictionary.addWord("dad");
// wordDictionary.addWord("mad");
// wordDictionary.search("pad"); // return False
// wordDictionary.search("bad"); // return True
// wordDictionary.search(".ad"); // return True
// wordDictionary.search("b.."); // return True

LEETCODE_SOLUTION_UNITTEST(211, DesignAddAndSearchWordsDataStructure,
                           example_1) {
  auto   word_dictionary = MakeWordDictionary();
  string s1_word         = "bad";
  word_dictionary->addWord(s1_word);
  string s2_word = "dad";
  word_dictionary->addWord(s2_word);
  string s3_word = "mad";
  word_dictionary->addWord(s3_word);
  string s4_word   = "pad";
  bool   s4_expect = false;
  bool   s4_actual = word_dictionary->search(s4_word);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  string s5_word   = "bad";
  bool   s5_expect = true;
  bool   s5_actual = word_dictionary->search(s5_word);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  string s6_word   = ".ad";
  bool   s6_expect = true;
  bool   s6_actual = word_dictionary->search(s6_word);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  string s7_word   = "b..";
  bool   s7_expect = true;
  bool   s7_actual = word_dictionary->search(s7_word);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
}
