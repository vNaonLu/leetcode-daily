// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Deletions to Make Character Frequencies Unique
//
// https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/
//
// Question ID: 1647
// Difficult  : Medium
// Solve Date : 2022/06/28 18:08

#include <iosfwd>
#include <queue>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1647. Minimum Deletions to Make Character Frequencies
// Unique|:
//
// A string |s| is called good if there are no two different characters in |s|
// that have the same frequency. Given a string |s|, return the minimum number
// of characters you need to delete to make |s| good. The frequency of a
// character in a string is the number of times it appears in the string. For
// example, in the string |"aab"|, the frequency of |'a'| is |2|, while the
// frequency of |'b'| is |1|.
//

LEETCODE_BEGIN_RESOLVING(1647, MinimumDeletionsToMakeCharacterFrequenciesUnique,
                         Solution);

class Solution {
public:
  int minDeletions(string s) {
    vector<int> freq(26, 0);
    for (auto &c : s) {
      ++freq[c - 'a'];
    }

    priority_queue<int> pq;
    for (auto &c : freq) {
      if (c > 0) {
        pq.emplace(c);
      }
    }

    int res = 0;
    while (pq.size() > 1) {
      int top = pq.top();
      pq.pop();

      if (top == pq.top()) {
        if (top - 1 > 0) {
          pq.emplace(top - 1);
        }

        ++res;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s|contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aab"
// Output: 0
//
// |s| is already good.

LEETCODE_SOLUTION_UNITTEST(1647,
                           MinimumDeletionsToMakeCharacterFrequenciesUnique,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "aab";
  int    expect   = 0;
  int    actual   = solution->minDeletions(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaabbbcc"
// Output: 2
//
// You can delete two 'b's resulting in the good string "aaabcc".
// Another way it to delete one 'b' and one 'c' resulting in the good string
// "aaabbc".

LEETCODE_SOLUTION_UNITTEST(1647,
                           MinimumDeletionsToMakeCharacterFrequenciesUnique,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aaabbbcc";
  int    expect   = 2;
  int    actual   = solution->minDeletions(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "ceabaacb"
// Output: 2
//
// You can delete both 'c's resulting in the good string "eabaab".
// Note that we only care about characters that are still in the string at the
// end (i.e. frequency of 0 is ignored).

LEETCODE_SOLUTION_UNITTEST(1647,
                           MinimumDeletionsToMakeCharacterFrequenciesUnique,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "ceabaacb";
  int    expect   = 2;
  int    actual   = solution->minDeletions(s);
  LCD_EXPECT_EQ(expect, actual);
}
