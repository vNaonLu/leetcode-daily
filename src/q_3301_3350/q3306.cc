// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count of Substrings Containing Every Vowel and K Consonants II
//
// https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/
//
// Question ID: 3306
// Difficult  : Medium
// Solve Date : 2025/03/10 18:46

#include <iosfwd>
#include <map>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3306. Count of Substrings Containing Every Vowel and K
// Consonants II|:
//
//

LEETCODE_BEGIN_RESOLVING(3306,
                         CountOfSubstringsContainingEveryVowelAndKConsonantsII,
                         Solution);

class Solution {
public:
  long long countOfSubstrings(string const &word, int k) {
    return impl(word, k) - impl(word, k - 1);
  }

private:
  bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
  }

  int64_t impl(string const &word, int k) {
    int64_t        res = 0;
    int            lo  = 0;
    int            hi  = 0;
    int            c   = 0;
    map<char, int> v;
    for (hi = 0; hi < word.size(); ++hi) {
      if (isVowel(word[hi])) {
        ++v[word[hi]];
      } else {
        ++c;
      }

      while (v.size() == 5 && c > k) {
        if (isVowel(word[lo])) {
          if (--v[word[lo]] == 0) {
            v.erase(word[lo]);
          }
        } else {
          --c;
        }
        ++lo;
      }

      res += (hi - lo + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |5 <= word.length <= 2 * 10⁵|
// * |word| consists only of lowercase English letters.
// * |0 <= k <= word.length - 5|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "aeioqq", k = 1
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(
    3306, CountOfSubstringsContainingEveryVowelAndKConsonantsII, example_1) {
  auto      solution = MakeSolution();
  string    word     = "aeioqq";
  int       k        = 1;
  long long expect   = 0;
  long long actual   = solution->countOfSubstrings(word, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "aeiou", k = 0
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(
    3306, CountOfSubstringsContainingEveryVowelAndKConsonantsII, example_2) {
  auto      solution = MakeSolution();
  string    word     = "aeiou";
  int       k        = 0;
  long long expect   = 1;
  long long actual   = solution->countOfSubstrings(word, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "ieaouqqieaouqq"
// 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(
    3306, CountOfSubstringsContainingEveryVowelAndKConsonantsII,
    extra_testcase_1) {
  auto      solution = MakeSolution();
  string    word     = "ieaouqqieaouqq";
  int       k        = 1;
  long long expect   = 3;
  long long actual   = solution->countOfSubstrings(word, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: "aeueio"
// 0
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(
    3306, CountOfSubstringsContainingEveryVowelAndKConsonantsII,
    extra_testcase_2) {
  auto      solution = MakeSolution();
  string    word     = "aeueio";
  int       k        = 0;
  long long expect   = 1;
  long long actual   = solution->countOfSubstrings(word, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #3]
//  Input: "aadieuoh"
// 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(
    3306, CountOfSubstringsContainingEveryVowelAndKConsonantsII,
    extra_testcase_3) {
  auto      solution = MakeSolution();
  string    word     = "aadieuoh";
  int       k        = 1;
  long long expect   = 2;
  long long actual   = solution->countOfSubstrings(word, k);
  LCD_EXPECT_EQ(expect, actual);
}
