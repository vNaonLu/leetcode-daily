// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Stream of Characters
//
// https://leetcode.com/problems/stream-of-characters/
//
// Question ID: 1032
// Difficult  : Hard
// Solve Date : 2021/12/04 22:22

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1032. Stream of Characters|:
//
// Design an algorithm that accepts a stream of characters and checks if a
// suffix of these characters is a string of a given array of strings |words|.
// For example, if |words = ["abc", "xyz"]| and the stream added the four
// characters (one by one) |'a'|, |'x'|, |'y'|, and |'z'|, your algorithm should
// detect that the suffix |"xyz"| of the characters |"axyz"| matches |"xyz"|
// from |words|. Implement the |StreamChecker| class:
//
//  • |StreamChecker(String[] words)| Initializes the object with the strings
//  array |words|.
//
//  • |boolean query(char letter)| Accepts a new character from the stream and
//  returns |true| if any non-empty suffix from the stream forms a word that is
//  in |words|.
//  
//

LEETCODE_BEGIN_RESOLVING(1032, StreamOfCharacters, StreamChecker);

class StreamChecker {
private:
  struct trie {
    vector<optional<trie>> next;
    bool                   is_end;
    trie() : is_end{false} { next.resize(26); }
  };
  trie         _head;
  vector<char> _queries;
  size_t       max_length{0};

public:
  StreamChecker(vector<string> &words) {
    for (const auto &s : words) {
      auto *node = &_head;
      for (auto it = s.rbegin(); it != s.rend(); ++it) {
        int idx = *it - 'a';
        if (!node->next[idx])
          node->next[idx] = trie{};
        node = &node->next[idx].value();
      }
      node->is_end = true;
      max_length   = max(max_length, s.size());
    }
  }
  bool query(char letter) {
    _queries.insert(_queries.begin(), letter);
    if (_queries.size() > max_length)
      _queries.pop_back();
    auto *node = &_head;
    for (auto it = _queries.begin(); it != _queries.end(); ++it) {
      if (node->is_end)
        return true;
      if (!node->next[*it - 'a'])
        return false;
      node = &node->next[*it - 'a'].value();
    }
    return node->is_end;
  }
};

LEETCODE_END_RESOLVING(StreamChecker);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 2000|
// * |1 <= words[i].length <= 200|
// * |words[i]| consists of lowercase English letters.
// * |letter| is a lowercase English letter.
// * At most |4 * 10⁴| calls will be made to query.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["StreamChecker", "query", "query", "query", "query", "query",
//  "query", "query", "query", "query", "query", "query", "query"]
// [[["cd", "f", "kl"]], ["a"], ["b"], ["c"], ["d"], ["e"], ["f"], ["g"], ["h"],
// ["i"], ["j"], ["k"], ["l"]] Output: [null, false, false, false, true, false,
// true, false, false, false, false, false, true]
//
// StreamChecker streamChecker = new StreamChecker(["cd", "f", "kl"]);
// streamChecker.query("a"); // return False
// streamChecker.query("b"); // return False
// streamChecker.query("c"); // return False
// streamChecker.query("d"); // return True, because 'cd' is in the wordlist
// streamChecker.query("e"); // return False
// streamChecker.query("f"); // return True, because 'f' is in the wordlist
// streamChecker.query("g"); // return False
// streamChecker.query("h"); // return False
// streamChecker.query("i"); // return False
// streamChecker.query("j"); // return False
// streamChecker.query("k"); // return False
// streamChecker.query("l"); // return True, because 'kl' is in the wordlist

LEETCODE_SOLUTION_UNITTEST(1032, StreamOfCharacters, example_1) {
  vector<string> s0_words       = {"cd", "f", "kl"};
  auto           stream_checker = MakeStreamChecker(s0_words);
  char           s1_letter      = 'a';
  bool           s1_expect      = false;
  bool           s1_actual      = stream_checker->query(s1_letter);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  char s2_letter = 'b';
  bool s2_expect = false;
  bool s2_actual = stream_checker->query(s2_letter);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  char s3_letter = 'c';
  bool s3_expect = false;
  bool s3_actual = stream_checker->query(s3_letter);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  char s4_letter = 'd';
  bool s4_expect = true;
  bool s4_actual = stream_checker->query(s4_letter);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  char s5_letter = 'e';
  bool s5_expect = false;
  bool s5_actual = stream_checker->query(s5_letter);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  char s6_letter = 'f';
  bool s6_expect = true;
  bool s6_actual = stream_checker->query(s6_letter);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  char s7_letter = 'g';
  bool s7_expect = false;
  bool s7_actual = stream_checker->query(s7_letter);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  char s8_letter = 'h';
  bool s8_expect = false;
  bool s8_actual = stream_checker->query(s8_letter);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  char s9_letter = 'i';
  bool s9_expect = false;
  bool s9_actual = stream_checker->query(s9_letter);
  LCD_EXPECT_EQ(s9_expect, s9_actual);
  char s10_letter = 'j';
  bool s10_expect = false;
  bool s10_actual = stream_checker->query(s10_letter);
  LCD_EXPECT_EQ(s10_expect, s10_actual);
  char s11_letter = 'k';
  bool s11_expect = false;
  bool s11_actual = stream_checker->query(s11_letter);
  LCD_EXPECT_EQ(s11_expect, s11_actual);
  char s12_letter = 'l';
  bool s12_expect = true;
  bool s12_actual = stream_checker->query(s12_letter);
  LCD_EXPECT_EQ(s12_expect, s12_actual);
}
