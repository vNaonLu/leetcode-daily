// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Difference Between Even and Odd Frequency II
//
// https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/
//
// Question ID: 3445
// Difficult  : Hard
// Solve Date : 2025/06/11 20:29

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3445. Maximum Difference Between Even and Odd Frequency II|:
//
// You are given a string |s| and an integer |k|. Your task is to find the
// maximum difference between the frequency of two characters, |freq[a] -
// freq[b]|, in a substring |subs| of |s|, such that:
//
//  • |subs| has a size of at least |k|.
//
//  • Character |a| has an odd frequency in |subs|.
//
//  • Character |b| has an even frequency in |subs|.
// Return the maximum difference.
// Note that |subs| can contain more than 2 distinct characters.
//
//

LEETCODE_BEGIN_RESOLVING(3445, MaximumDifferenceBetweenEvenAndOddFrequencyII,
                         Solution);

class Solution {
public:
  int maxDifference(string s, int k) {
    int n   = s.size();
    int ans = numeric_limits<int>::min();

    for (int a = 0; a <= 4; ++a) {
      for (int b = 0; b <= 4; ++b) {
        if (a == b) {
          continue;
        }

        vector<int> s1(n + 1);
        vector<int> s2(n + 1);

        for (int i = 1; i <= n; ++i) {
          s1[i] = s1[i - 1] + (s[i - 1] - '0' == a);
          s2[i] = s2[i - 1] + (s[i - 1] - '0' == b);
        }

        int g[2][2] = {
            {numeric_limits<int>::min(), numeric_limits<int>::min()},
            {numeric_limits<int>::min(), numeric_limits<int>::min()}
        };
        int j = 0;

        for (int i = k; i <= n; ++i) {
          while (i - j >= k && s1[i] > s1[j] && s2[i] > s2[j]) {
            int pa    = s1[j] % 2;
            int pb    = s2[j] % 2;
            g[pa][pb] = max(g[pa][pb], s2[j] - s1[j]);
            ++j;
          }

          int pa   = s1[i] % 2;
          int pb   = s2[i] % 2;
          int need = g[1 - pa][pb];

          if (need != numeric_limits<int>::min()) {
            ans = max(ans, (s1[i] - s2[i]) + need);
          }
        }
      }
    }

    return ans == numeric_limits<int>::min() ? -1 : ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= s.length <= 3 * 10⁴|
// * |s| consists only of digits |'0'| to |'4'|.
// * The input is generated that at least one substring has a character with an
// even frequency and a character with an odd frequency.
// * |1 <= k <= s.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "12233", k = 4
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3445, MaximumDifferenceBetweenEvenAndOddFrequencyII,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "12233";
  int    k        = 4;
  int    expect   = -1;
  int    actual   = solution->maxDifference(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "1122211", k = 3
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3445, MaximumDifferenceBetweenEvenAndOddFrequencyII,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "1122211";
  int    k        = 3;
  int    expect   = 1;
  int    actual   = solution->maxDifference(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "110", k = 3
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3445, MaximumDifferenceBetweenEvenAndOddFrequencyII,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "110";
  int    k        = 3;
  int    expect   = -1;
  int    actual   = solution->maxDifference(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
