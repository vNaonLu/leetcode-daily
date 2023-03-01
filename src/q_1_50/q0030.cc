// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Substring with Concatenation of All Words
//
// https://leetcode.com/problems/substring-with-concatenation-of-all-words/
//
// Question ID: 30
// Difficult  : Hard
// Solve Date : 2021/12/15 23:17

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |30. Substring with Concatenation of All Words|:
//
// You are given a string |s| and an array of strings |words|. All the strings
// of |words| are of the same length. A concatenated substring in |s| is a
// substring that contains all the strings of any permutation of |words|
// concatenated.
//
//  • For example, if |words = ["ab","cd","ef"]|, then |"abcdef"|, |"abefcd"|,
//  |"cdabef"|, |"cdefab"|, |"efabcd"|, and |"efcdab"| are all concatenated
//  strings. |"acdbef"| is not a concatenated substring because it is not the
//  concatenation of any permutation of |words|.
// Return the starting indices of all the concatenated substrings in |s|. You
// can return the answer in any order.  
//

LEETCODE_BEGIN_RESOLVING(30, SubstringWithConcatenationOfAllWords, Solution);

class Solution {
public:
  vector<int> findSubstring(string s, vector<string> &words) {
    vector<int>                res;
    unordered_map<string, int> target;
    for (const string &w : words)
      ++target[w];
    int len = words.front().size();
    if (len > s.size())
      return res;

    int                        cur = 0, start = 0;
    string                     str;
    unordered_map<string, int> moving;
    while (cur <= s.size() - len) {
      str = s.substr(cur, len);
      if (target.count(str)) {
        ++moving[str];
        if (moving[str] <= target[str]) {
          if (moving == target)
            res.push_back(start);
          else {
            cur += len;
            continue;
          }
        }
      }
      moving.clear();
      ++start;
      cur = start;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |1 <= words.length <= 5000|
// * |1 <= words[i].length <= 30|
// * |s| and |words[i]| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "barfoothefoobarman", words = ["foo","bar"]
// Output: [0,9]
//
// Since words.length == 2 and words[i].length == 3, the concatenated substring
// has to be of length 6. The substring starting at 0 is "barfoo". It is the
// concatenation of ["bar","foo"] which is a permutation of words. The substring
// starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is
// a permutation of words. The output order does not matter. Returning [9,0] is
// fine too.

LEETCODE_SOLUTION_UNITTEST(30, SubstringWithConcatenationOfAllWords,
                           example_1) {
  auto           solution = MakeSolution();
  string         s        = "barfoothefoobarman";
  vector<string> words    = {"foo", "bar"};
  vector<int>    expect   = {0, 9};
  vector<int>    actual   = solution->findSubstring(s, words);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
// Output: []
//
// Since words.length == 4 and words[i].length == 4, the concatenated substring
// has to be of length 16. There is no substring of length 16 is s that is equal
// to the concatenation of any permutation of words. We return an empty array.

LEETCODE_SOLUTION_UNITTEST(30, SubstringWithConcatenationOfAllWords,
                           example_2) {
  auto           solution = MakeSolution();
  string         s        = "wordgoodgoodgoodbestword";
  vector<string> words    = {"word", "good", "best", "word"};
  vector<int>    expect   = {};
  vector<int>    actual   = solution->findSubstring(s, words);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
// Output: [6,9,12]
//
// Since words.length == 3 and words[i].length == 3, the concatenated substring
// has to be of length 9. The substring starting at 6 is "foobarthe". It is the
// concatenation of ["foo","bar","the"] which is a permutation of words. The
// substring starting at 9 is "barthefoo". It is the concatenation of
// ["bar","the","foo"] which is a permutation of words. The substring starting
// at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"] which is
// a permutation of words.

LEETCODE_SOLUTION_UNITTEST(30, SubstringWithConcatenationOfAllWords,
                           example_3) {
  auto           solution = MakeSolution();
  string         s        = "barfoofoobarthefoobarman";
  vector<string> words    = {"bar", "foo", "the"};
  vector<int>    expect   = {6, 9, 12};
  vector<int>    actual   = solution->findSubstring(s, words);
  EXPECT_ANYORDER_EQ(expect, actual);
}
