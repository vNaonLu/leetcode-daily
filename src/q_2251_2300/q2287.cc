// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rearrange Characters to Make Target String
//
// https://leetcode.com/problems/rearrange-characters-to-make-target-string/
//
// Question ID: 2287
// Difficult  : Easy
// Solve Date : 2023/10/19 21:24

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2287. Rearrange Characters to Make Target String|:
//
// You are given two 0-indexed strings |s| and |target|. You can take some
// letters from |s| and rearrange them to form new strings. Return the maximum
// number of copies of |target| that can be formed by taking letters from |s|
// and rearranging them.
//
//

LEETCODE_BEGIN_RESOLVING(2287, RearrangeCharactersToMakeTargetString, Solution);

class Solution {
public:
  int rearrangeCharacters(string s, string target) {
    map<char, int> mp;
    int            res = 0;
    for (auto c : target) {
      ++mp[c];
    }

    vector<int> freq(26, 0);
    for (auto c : s) {
      if (mp.count(c)) {
        ++freq[c - 'a'];
      }
    }

    for (auto &[c, cnt] : mp) {
      if (res == 0 && freq[c - 'a'] >= cnt) {
        res = freq[c - 'a'] / cnt;
      } else if (freq[c - 'a'] >= cnt) {
        res = min(res, freq[c - 'a'] / cnt);
      } else {
        return 0;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |1 <= target.length <= 10|
// * |s| and |target| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ilovecodingonleetcode", target = "code"
// Output: 2
//
// For the first copy of "code", take the letters at indices 4, 5, 6, and 7.
// For the second copy of "code", take the letters at indices 17, 18, 19,
// and 20. The strings that are formed are "ecod" and "code" which can both be
// rearranged into "code". We can make at most two copies of "code", so we
// return 2.

LEETCODE_SOLUTION_UNITTEST(2287, RearrangeCharactersToMakeTargetString,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "ilovecodingonleetcode";
  string target   = "code";
  int    expect   = 2;
  int    actual   = solution->rearrangeCharacters(s, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcba", target = "abc"
// Output: 1
//
// We can make one copy of "abc" by taking the letters at indices 0, 1, and 2.
// We can make at most one copy of "abc", so we return 1.
// Note that while there is an extra 'a' and 'b' at indices 3 and 4, we cannot
// reuse the letter 'c' at index 2, so we cannot make a second copy of "abc".

LEETCODE_SOLUTION_UNITTEST(2287, RearrangeCharactersToMakeTargetString,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "abcba";
  string target   = "abc";
  int    expect   = 1;
  int    actual   = solution->rearrangeCharacters(s, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abbaccaddaeea", target = "aaaaa"
// Output: 1
//
// We can make one copy of "aaaaa" by taking the letters at indices 0, 3, 6, 9,
// and 12. We can make at most one copy of "aaaaa", so we return 1.

LEETCODE_SOLUTION_UNITTEST(2287, RearrangeCharactersToMakeTargetString,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "abbaccaddaeea";
  string target   = "aaaaa";
  int    expect   = 1;
  int    actual   = solution->rearrangeCharacters(s, target);
  LCD_EXPECT_EQ(expect, actual);
}
