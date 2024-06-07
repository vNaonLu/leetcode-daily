// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Replace Words
//
// https://leetcode.com/problems/replace-words/
//
// Question ID: 648
// Difficult  : Medium
// Solve Date : 2024/06/07 10:08

#include <array>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |648. Replace Words|:
//
// In English, we have a concept called root, which can be followed by some
// other word to form another longer word - let's call this word derivative. For
// example, when the root |"help"| is followed by the word |"ful"|, we can form
// a derivative |"helpful"|. Given a |dictionary| consisting of many roots and a
// |sentence| consisting of words separated by spaces, replace all the
// derivatives in the sentence with the root forming it. If a derivative can be
// replaced by more than one root, replace it with the root that has the
// shortest length. Return the |sentence| after the replacement.
//
//

LEETCODE_BEGIN_RESOLVING(648, ReplaceWords, Solution);

class Solution {
public:
  string replaceWords(vector<string> &dictionary, string sentence) {
    TrieMap t(dictionary);
    string  res;
    auto    left = sentence.begin();
    auto    it   = left;
    while (left != sentence.end()) {
      while (it != sentence.end()) {
        if (*it == ' ') {
          break;
        }
        ++it;
      }

      string word(left, t.sliceIfNeeded(left, it));
      res  = res.empty() ? word : (res + " " + word);
      left = it == sentence.end() ? it : ++it;
    }
    return res;
  }

private:
  class TrieMap {
    struct Node;

  public:
    TrieMap(vector<string> const &dict) {
      for (auto const &s : dict) {
        insert(s);
      }
    }
    template <typename It>
    It sliceIfNeeded(It beg, It end) {
      auto *p = root.child[*beg++ - 'a'].get();
      if (!p) {
        return end;
      }
      while (beg != end) {
        if (!p->child[*beg - 'a'] || p->end) {
          if (p->end) {
            return beg;
          } else {
            return end;
          }
        } else {
          p = p->child[*beg - 'a'].get();
        }
        ++beg;
      }
      return end;
    }

  private:
    void insert(string const &s) {
      auto *p = &root;
      for (auto c : s) {
        if (!p->child[c - 'a']) {
          p->child[c - 'a'] = make_unique<Node>();
        }
        p = p->child[c - 'a'].get();
      }
      p->end = true;
    }

    struct Node {
      array<unique_ptr<Node>, 26> child;
      bool                        end{false};
    } root;
  };
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= dictionary.length <= 1000|
// * |1 <= dictionary[i].length <= 100|
// * |dictionary[i]| consists of only lower-case letters.
// * |1 <= sentence.length <= 10⁶|
// * |sentence| consists of only lower-case letters and spaces.
// * The number of words in |sentence| is in the range |[1, 1000]|
// * The length of each word in |sentence| is in the range |[1, 1000]|
// * Every two consecutive words in |sentence| will be separated by exactly one
// space.
// * |sentence| does not have leading or trailing spaces.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled
//  by the battery"
// Output: "the cat was rat by the bat"
//

LEETCODE_SOLUTION_UNITTEST(648, ReplaceWords, example_1) {
  auto           solution   = MakeSolution();
  vector<string> dictionary = {"cat", "bat", "rat"};
  string         sentence   = "the cattle was rattled by the battery";
  string         expect     = "the cat was rat by the bat";
  string         actual     = solution->replaceWords(dictionary, sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
// Output: "a a b c"
//

LEETCODE_SOLUTION_UNITTEST(648, ReplaceWords, example_2) {
  auto           solution   = MakeSolution();
  vector<string> dictionary = {"a", "b", "c"};
  string         sentence   = "aadsfasf absbs bbab cadsfafs";
  string         expect     = "a a b c";
  string         actual     = solution->replaceWords(dictionary, sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: ["a", "aa", "aaa", "aaaa"]
// "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa"
// Output: "a a a a a a a a bbb baba a"
//

LEETCODE_SOLUTION_UNITTEST(648, ReplaceWords, extra_testcase_1) {
  auto           solution   = MakeSolution();
  vector<string> dictionary = {"a", "aa", "aaa", "aaaa"};
  string         sentence   = "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa";
  string         expect     = "a a a a a a a a bbb baba a";
  string         actual     = solution->replaceWords(dictionary, sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: ["a","b","c"]
// "aadsfasf absbs bbab cadsfafs"
// Output: "a a b c"
//

LEETCODE_SOLUTION_UNITTEST(648, ReplaceWords, extra_testcase_2) {
  auto           solution   = MakeSolution();
  vector<string> dictionary = {"a", "b", "c"};
  string         sentence   = "aadsfasf absbs bbab cadsfafs";
  string         expect     = "a a b c";
  string         actual     = solution->replaceWords(dictionary, sentence);
  LCD_EXPECT_EQ(expect, actual);
}
