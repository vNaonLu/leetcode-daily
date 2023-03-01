#include <array>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 208.
 *      Implement Trie (Prefix Tree)
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   A <a href="https://en.wikipedia.org/wiki/Trie" target="_blank"> “trie”
 *   </a> (pronounced as 'try') or “prefix tree” is a tree data structure
 *   used to efficiently store and retrieve keys in a dataset of strings.
 *   There are various applications of this data structure, such as
 *   autocomplete and
 *   Implement the Trie
 *       -  ‘Trie()’ Initializes the trie
 *       -  ‘void insert(String word)’ Inserts the string ‘word’ into the
 *       -  ‘boolean search(String word)’ Returns ‘true’ if the string
 *   ‘word’ is in the trie (i.e., was inserted before), and ‘false’
 *       -  ‘boolean startsWith(String prefix)’ Returns ‘true’ if there is
 *   a previously inserted string ‘word’ that has the prefix ‘prefix’ , and
 *   ‘false’ otherwise.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ word.length, prefix.length ≤ 2000’
 *   • ‘word’ and ‘prefix’ consist only of lowercase English letters.
 *   • At most ‘3 × 10⁴’ calls “in total” will be made to ‘insert’ , ‘search’ ,
 * and ‘startsWith’ .
 *
 */

struct q208 : public ::testing::Test {
  // Leetcode answer here
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

  /**
   * Your Trie object will be instantiated and called as such:
   * Trie* obj = new Trie();
   * obj->insert(word);
   * bool param_2 = obj->search(word);
   * bool param_3 = obj->startsWith(prefix);
   */

  class Trie *trie;
};

TEST_F(q208, sample_input01) {
  trie = new Trie();
  trie->insert("apple");
  EXPECT_EQ(trie->search("apple"), true);
  EXPECT_EQ(trie->search("app"), false);
  EXPECT_EQ(trie->startsWith("app"), true);
  trie->insert("app");
  EXPECT_EQ(trie->search("app"), true);
  delete trie;
}