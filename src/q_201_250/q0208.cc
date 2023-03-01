// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Implement Trie (Prefix Tree)
//
// https://leetcode.com/problems/implement-trie-prefix-tree/
//
// Question ID: 208
// Difficult  : Medium
// Solve Date : 2021/10/08 12:18

#include <array>
#include <iosfwd>
#include <memory>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |208. Implement Trie (Prefix Tree)|:
//
// A trie (pronounced as "try") or prefix tree is a tree data structure used to
// efficiently store and retrieve keys in a dataset of strings. There are
// various applications of this data structure, such as autocomplete and
// spellchecker. Implement the Trie class:
//
//  • |Trie()| Initializes the trie object.
//
//  • |void insert(String word)| Inserts the string |word| into the trie.
//
//  • |boolean search(String word)| Returns |true| if the string |word| is in
//  the trie (i.e., was inserted before), and |false| otherwise.
//
//  • |boolean startsWith(String prefix)| Returns |true| if there is a
//  previously inserted string |word| that has the prefix |prefix|, and |false|
//  otherwise.
//  
//

LEETCODE_BEGIN_RESOLVING(208, ImplementTriePrefixTree, Trie);

class Trie {
  array<unique_ptr<Trie>, 127> next;
  bool                         end;

public:
  Trie() : end{false} {}

  void insert(string word) {
    auto p   = this;
    auto beg = word.begin();
    while (beg != word.end()) {
      auto &nxt = p->next[*beg++];
      if (nullptr == nxt) {
        nxt = make_unique<Trie>();
      }
      p = nxt.get();
    }
    p->end = true;
  }

  bool search(string word) {
    auto p   = this;
    auto beg = word.begin();
    while (beg != word.end()) {
      auto &nxt = p->next[*beg++];
      if (nullptr == nxt) {
        return false;
      }
      p = nxt.get();
    }
    return p != nullptr && p->end;
  }

  bool startsWith(string prefix) {
    auto p   = this;
    auto beg = prefix.begin();
    while (beg != prefix.end()) {
      auto &nxt = p->next[*beg++];
      if (nullptr == nxt) {
        return false;
      }
      p = nxt.get();
    }
    return p != nullptr;
  }
};

LEETCODE_END_RESOLVING(Trie);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word.length, prefix.length <= 2000|
// * |word| and |prefix| consist only of lowercase English letters.
// * At most |3 * 10⁴| calls in total will be made to |insert|, |search|, and
// |startsWith|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Trie", "insert", "search", "search", "startsWith", "insert",
//  "search"]
// [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
// Output: [null, null, true, false, true, null, true]
//
// Trie trie = new Trie();
// trie.insert("apple");
// trie.search("apple"); // return True
// trie.search("app"); // return False
// trie.startsWith("app"); // return True
// trie.insert("app");
// trie.search("app"); // return True

LEETCODE_SOLUTION_UNITTEST(208, ImplementTriePrefixTree, example_1) {
  auto   trie    = MakeTrie();
  string s1_word = "apple";
  trie->insert(s1_word);
  string s2_word   = "apple";
  bool   s2_expect = true;
  bool   s2_actual = trie->search(s2_word);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  string s3_word   = "app";
  bool   s3_expect = false;
  bool   s3_actual = trie->search(s3_word);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  string s4_prefix = "app";
  bool   s4_expect = true;
  bool   s4_actual = trie->startsWith(s4_prefix);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  string s5_word = "app";
  trie->insert(s5_word);
  string s6_word   = "app";
  bool   s6_expect = true;
  bool   s6_actual = trie->search(s6_word);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
