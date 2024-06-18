// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Implement Magic Dictionary
//
// https://leetcode.com/problems/implement-magic-dictionary/
//
// Question ID: 676
// Difficult  : Medium
// Solve Date : 2024/06/18 20:23

#include <array>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |676. Implement Magic Dictionary|:
//
// Design a data structure that is initialized with a list of different words.
// Provided a string, you should determine if you can change exactly one
// character in this string to match any word in the data structure. Implement
// the |MagicDictionary| class:
//
//  • |MagicDictionary()| Initializes the object.
//
//  • |void buildDict(String[] dictionary)| Sets the data structure with an
//  array of distinct strings |dictionary|.
//
//  • |bool search(String searchWord)| Returns |true| if you can change exactly
//  one character in |searchWord| to match any string in the data structure,
//  otherwise returns |false|.
//
//

LEETCODE_BEGIN_RESOLVING(676, ImplementMagicDictionary, MagicDictionary);

class MagicDictionary {
public:
  MagicDictionary() {}

  void buildDict(vector<string> dictionary) {
    for (auto &s : dictionary) {
      buildTrie(s.begin(), s.end());
    }
  }

  bool search(string searchWord) {
    return blurSearch(searchWord.begin(), searchWord.end(), &root_, 1);
  }

private:
  struct Trie {
    array<unique_ptr<Trie>, 26> next;
    bool                        is_end{false};
  };

  template <typename It>
  void buildTrie(It beg, It end) {
    auto *p = &root_;
    while (beg != end) {
      if (!p->next[*beg - 'a']) {
        p->next[*beg - 'a'] = make_unique<Trie>();
      }
      p = p->next[*beg - 'a'].get();
      beg++;
    }
    p->is_end = true;
  }

  template <typename It>
  bool blurSearch(It beg, It end, Trie const *p, int threshold) {
    if (beg == end) {
      return p && p->is_end && threshold == 0;
    }

    if (!p || threshold < 0) {
      return false;
    }

    if (p->next[*beg - 'a'] &&
        blurSearch(beg + 1, end, p->next[*beg - 'a'].get(), threshold)) {
      return true;
    }

    // Skip this character.
    for (int i = 0; i < p->next.size(); ++i) {
      auto &next = p->next[i];
      if (i == *beg - 'a') {
        continue;
      }
      if (next && blurSearch(beg + 1, end, next.get(), threshold - 1)) {
        return true;
      }
    }

    return false;
  }

  Trie root_;
};

LEETCODE_END_RESOLVING(MagicDictionary);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= dictionary.length <= 100|
// * |1 <= dictionary[i].length <= 100|
// * |dictionary[i]| consists of only lower-case English letters.
// * All the strings in |dictionary| are distinct.
// * |1 <= searchWord.length <= 100|
// * |searchWord| consists of only lower-case English letters.
// * |buildDict| will be called only once before |search|.
// * At most |100| calls will be made to |search|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MagicDictionary", "buildDict", "search", "search", "search",
//  "search"]
// [[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
// Output: [null, null, false, true, false, false]
//

LEETCODE_SOLUTION_UNITTEST(676, ImplementMagicDictionary, example_1) {
  auto           magic_dictionary = MakeMagicDictionary();
  vector<string> s1_dictionary    = {"hello", "leetcode"};
  magic_dictionary->buildDict(s1_dictionary);
  string s2_searchWord = "hello";
  bool   s2_expect     = false;
  bool   s2_actual     = magic_dictionary->search(s2_searchWord);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  string s3_searchWord = "hhllo";
  bool   s3_expect     = true;
  bool   s3_actual     = magic_dictionary->search(s3_searchWord);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  string s4_searchWord = "hell";
  bool   s4_expect     = false;
  bool   s4_actual     = magic_dictionary->search(s4_searchWord);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  string s5_searchWord = "leetcoded";
  bool   s5_expect     = false;
  bool   s5_actual     = magic_dictionary->search(s5_searchWord);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}

// [Extra Testcase #1]
//  Input: ["MagicDictionary", "buildDict", "search", "search", "search",
//  "search"]
// [[], [["hello","hallo","leetcode"]], ["hello"], ["hhllo"], ["hell"],
// ["leetcoded"]] Output: [null,null,true,true,false,false]
//

LEETCODE_SOLUTION_UNITTEST(676, ImplementMagicDictionary, extra_testcase_1) {
  auto           magic_dictionary = MakeMagicDictionary();
  vector<string> s1_dictionary    = {"hello", "hallo", "leetcode"};
  magic_dictionary->buildDict(s1_dictionary);
  string s2_searchWord = "hello";
  bool   s2_expect     = true;
  bool   s2_actual     = magic_dictionary->search(s2_searchWord);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  string s3_searchWord = "hhllo";
  bool   s3_expect     = true;
  bool   s3_actual     = magic_dictionary->search(s3_searchWord);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  string s4_searchWord = "hell";
  bool   s4_expect     = false;
  bool   s4_actual     = magic_dictionary->search(s4_searchWord);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  string s5_searchWord = "leetcoded";
  bool   s5_expect     = false;
  bool   s5_actual     = magic_dictionary->search(s5_searchWord);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
