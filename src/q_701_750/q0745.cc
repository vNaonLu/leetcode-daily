// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Prefix and Suffix Search
//
// https://leetcode.com/problems/prefix-and-suffix-search/
//
// Question ID: 745
// Difficult  : Hard
// Solve Date : 2022/06/18 14:48

#include <array>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |745. Prefix and Suffix Search|:
//
// Design a special dictionary that searches the words in it by a prefix and a
// suffix. Implement the |WordFilter| class:
//
//  • |WordFilter(string[] words)| Initializes the object with the |words| in
//  the dictionary.
//
//  • |f(string pref, string suff)| Returns the index of the word in the
//  dictionary, which has the prefix |pref| and the suffix |suff|. If there is
//  more than one valid index, return the largest of them. If there is no such
//  word in the dictionary, return |-1|.
//

LEETCODE_BEGIN_RESOLVING(745, PrefixAndSuffixSearch, WordFilter);

class WordFilter {
private:
  struct Trie {
    int                         index;
    array<unique_ptr<Trie>, 27> next; /// with 'z' + 1
  };

  unique_ptr<Trie> memo;

  template <typename iterator>
  void build_trie(Trie *target, int index, iterator beg, iterator end) {
    Trie *p = target;
    while (beg != end) {
      auto &next = p->next[*beg++ - 'a'];

      if (nullptr == next) {
        next = make_unique<Trie>();
      }
      next->index = index;
      p           = next.get();
    }
  }

  void build_tries(vector<string> const &words) {
    for (int i = 0; i < words.size(); ++i) {
      const auto &s = words[i];
      for (int j = 0; j < s.size(); ++j) {
        string tmp = s.substr(j) + "[" + s;
        build_trie(memo.get(), i, tmp.begin(), tmp.end());
      }
    }
  }

  template <typename iterator>
  Trie *match(Trie *target, iterator beg, iterator end) {
    Trie *p = target;
    while (beg != end && nullptr != p) {
      p = p->next[*beg++ - 'a'].get();
    }
    return p;
  }

public:
  WordFilter(vector<string> &words) : memo{make_unique<Trie>()} {
    build_tries(words);
  }

  int f(string pre, string suf) {
    string key = suf + "[" + pre;
    auto   res = match(memo.get(), key.begin(), key.end());

    return res == nullptr ? -1 : res->index;
  }
};

LEETCODE_END_RESOLVING(WordFilter);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 10⁴|
// * |1 <= words[i].length <= 7|
// * |1 <= pref.length, suff.length <= 7|
// * |words[i]|, |pref| and |suff| consist of lowercase English letters only.
// * At most |10⁴| calls will be made to the function |f|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["WordFilter", "f"]
// [[["apple"]], ["a", "e"]]
// Output: [null, 0]
//
// WordFilter wordFilter = new WordFilter(["apple"]);
// wordFilter.f("a", "e"); // return 0, because the word at index 0 has prefix =
// "a" and suffix = "e".

LEETCODE_SOLUTION_UNITTEST(745, PrefixAndSuffixSearch, example_1) {
  vector<string> s0_words    = {"apple"};
  auto           word_filter = MakeWordFilter(s0_words);
  string         s1_pref     = "a";
  string         s1_suff     = "e";
  int            s1_expect   = 0;
  int            s1_actual   = word_filter->f(s1_pref, s1_suff);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
}
