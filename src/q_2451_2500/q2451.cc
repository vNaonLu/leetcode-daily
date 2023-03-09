// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Odd String Difference
//
// https://leetcode.com/problems/odd-string-difference/
//
// Question ID: 2451
// Difficult  : Easy
// Solve Date : 2023/03/09 12:10

#include <iosfwd>
#include <map>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2451. Odd String Difference|:
//
// You are given an array of equal-length strings |words|. Assume that the
// length of each string is |n|. Each string |words[i]| can be converted into a
// difference integer array |difference[i]| of length |n - 1| where
// |difference[i][j] = words[i][j+1] - words[i][j]| where |0 <= j <= n - 2|.
// Note that the difference between two letters is the difference between their
// positions in the alphabet i.e.the position of |'a'| is |0|, |'b'| is |1|, and
// |'z'| is |25|.
//
//  • For example, for the string |"acb"|, the difference integer array is |[2 -
//  0, 1 - 2] = [2, -1]|.
// All the strings in words have the same difference integer array, except one.
// You should find that string. Return the string in |words| that has different
// difference integer array.
//

LEETCODE_BEGIN_RESOLVING(2451, OddStringDifference, Solution);

class Solution {
private:
  void convert(string *s) {
    auto mn = *min_element(s->begin(), s->end()) - 'a';
    for (auto &c : *s) {
      c -= mn;
    }
  }

public:
  string oddString(vector<string> &words) {
    map<string, vector<string_view>> memo;
    int                              idx = 0;
    for (auto &s : words) {
      ++idx;
      auto cv = s;
      convert(&cv);
      memo[cv].emplace_back(s);

      if (memo.size() > 1 && idx >= 3) {
        for (auto &[ss, cnt] : memo) {
          if (cnt.size() == 1) {
            return string(cnt.front());
          }
        }
      }
    }
    return "";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= words.length <= 100|
// * |n == words[i].length|
// * |2 <= n <= 20|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["adc","wzy","abc"]
// Output: "abc"
//
// - The difference integer array of "adc" is [3 - 0, 2 - 3] = [3, -1].
// - The difference integer array of "wzy" is [25 - 22, 24 - 25]= [3, -1].
// - The difference integer array of "abc" is [1 - 0, 2 - 1] = [1, 1].
// The odd array out is [1, 1], so we return the corresponding string, "abc".

LEETCODE_SOLUTION_UNITTEST(2451, OddStringDifference, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"adc", "wzy", "abc"};
  string         expect   = "abc";
  string         actual   = solution->oddString(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["aaa","bob","ccc","ddd"]
// Output: "bob"
//
// All the integer arrays are [0, 0] except for "bob", which corresponds to [13,
// -13].

LEETCODE_SOLUTION_UNITTEST(2451, OddStringDifference, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"aaa", "bob", "ccc", "ddd"};
  string         expect   = "bob";
  string         actual   = solution->oddString(words);
  LCD_EXPECT_EQ(expect, actual);
}
