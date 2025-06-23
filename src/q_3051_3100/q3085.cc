// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Deletions to Make String K-Special
//
// https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/
//
// Question ID: 3085
// Difficult  : Medium
// Solve Date : 2025/06/21 13:44

#include <algorithm>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3085. Minimum Deletions to Make String K-Special|:
//
// You are given a string |word| and an integer |k|.
// We consider |word| to be k-special if ||freq(word[i]) - freq(word[j])| <= k|
// for all indices |i| and |j| in the string. Here, |freq(x)| denotes the
// frequency of the character |x| in |word|, and ||y|| denotes the absolute
// value of |y|. Return the minimum number of characters you need to delete to
// make |word| k-special.
//
//

LEETCODE_BEGIN_RESOLVING(3085, MinimumDeletionsToMakeStringKSpecial, Solution);

class Solution {
public:
  int minimumDeletions(const string &word, int k) {
    array<int, 26> freq{};
    for (unsigned char c : word)
      ++freq[c - 'a'];

    vector<int> freqList;
    freqList.reserve(26);
    for (int f : freq)
      if (f > 0)
        freqList.push_back(f);

    sort(freqList.begin(), freqList.end());

    int n = freqList.size(), total = word.size(), removedLeft = 0,
        inWindowSum = 0;
    int res = numeric_limits<int>::max(), r = 0;

    for (int l = 0; l < n; ++l) {
      int base  = freqList[l];
      int limit = base + k;

      while (r < n && freqList[r] <= limit)
        inWindowSum += freqList[r++];

      int rightCount = n - r;
      int rightSum   = total - inWindowSum;
      int delRight   = rightSum - rightCount * limit;

      res = min(res, removedLeft + delRight);

      total -= freqList[l];
      removedLeft += freqList[l];
      inWindowSum -= freqList[l];
    }

    return res;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 10⁵|
// * |0 <= k <= 10⁵|
// * |word| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "aabcaba", k = 0
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3085, MinimumDeletionsToMakeStringKSpecial,
                           example_1) {
  auto   solution = MakeSolution();
  string word     = "aabcaba";
  int    k        = 0;
  int    expect   = 3;
  int    actual   = solution->minimumDeletions(word, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "dabdcbdcdcd", k = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3085, MinimumDeletionsToMakeStringKSpecial,
                           example_2) {
  auto   solution = MakeSolution();
  string word     = "dabdcbdcdcd";
  int    k        = 2;
  int    expect   = 2;
  int    actual   = solution->minimumDeletions(word, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word = "aaabaaa", k = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3085, MinimumDeletionsToMakeStringKSpecial,
                           example_3) {
  auto   solution = MakeSolution();
  string word     = "aaabaaa";
  int    k        = 2;
  int    expect   = 1;
  int    actual   = solution->minimumDeletions(word, k);
  LCD_EXPECT_EQ(expect, actual);
}
