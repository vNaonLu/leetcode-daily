// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Pushes to Type Word II
//
// https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/
//
// Question ID: 3016
// Difficult  : Medium
// Solve Date : 2024/08/06 21:51

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3016. Minimum Number of Pushes to Type Word II|:
//
// You are given a string |word| containing lowercase English letters.
// Telephone keypads have keys mapped with distinct collections of lowercase
// English letters, which can be used to form words by pushing them. For
// example, the key |2| is mapped with |["a","b","c"]|, we need to push the key
// one time to type |"a"|, two times to type |"b"|, and three times to type
// |"c"| . It is allowed to remap the keys numbered |2| to |9| to distinct
// collections of letters. The keys can be remapped to any amount of letters,
// but each letter must be mapped to exactly one key. You need to find the
// minimum number of times the keys will be pushed to type the string |word|.
// Return the minimum number of pushes needed to type |word| after remapping the
// keys. An example mapping of letters to keys on a telephone keypad is given
// below. Note that |1|, |*|, |#|, and |0| do not map to any letters.
// ![img](https://assets.leetcode.com/uploads/2023/12/26/keypaddesc.png)
//
//

LEETCODE_BEGIN_RESOLVING(3016, MinimumNumberOfPushesToTypeWordII, Solution);

class Solution {
public:
  int minimumPushes(string word) {
    vector<int> freq(26, 0);
    for (auto c : word) {
      ++freq[c - 'a'];
    }
    sort(freq.begin(), freq.end(), greater<int>{});
    int sz   = 0;
    int push = 1;
    int res  = 0;
    for (; sz < 26 && freq[sz] != 0; ++sz) {
      if (sz >= 8 && sz % 8 == 0) {
        ++push;
      }
      res += freq[sz] * push;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 10⁵|
// * |word| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "abcde"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3016, MinimumNumberOfPushesToTypeWordII, example_1) {
  auto   solution = MakeSolution();
  string word     = "abcde";
  int    expect   = 5;
  int    actual   = solution->minimumPushes(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "xyzxyzxyzxyz"
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(3016, MinimumNumberOfPushesToTypeWordII, example_2) {
  auto   solution = MakeSolution();
  string word     = "xyzxyzxyzxyz";
  int    expect   = 12;
  int    actual   = solution->minimumPushes(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word = "aabbccddeeffgghhiiiiii"
// Output: 24
//

LEETCODE_SOLUTION_UNITTEST(3016, MinimumNumberOfPushesToTypeWordII, example_3) {
  auto   solution = MakeSolution();
  string word     = "aabbccddeeffgghhiiiiii";
  int    expect   = 24;
  int    actual   = solution->minimumPushes(word);
  LCD_EXPECT_EQ(expect, actual);
}
