// Copyright 2023 Naon Lu
//
// This file describes the solution of
// String Compression II
//
// https://leetcode.com/problems/string-compression-ii/
//
// Question ID: 1531
// Difficult  : Hard
// Solve Date : 2022/10/15 13:26

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1531. String Compression II|:
//
// [Run-length encoding] is a string compression method that works byreplacing
// consecutive identical characters (repeated 2 or more times) with the
// concatenation of the character and the number marking the count of the
// characters (length of the run). For example, to compress the string
// |"aabccc"|we replace |"aa"|by |"a2"|and replace |"ccc"|by |"c3"|. Thus the
// compressed string becomes |"a2bc3"|. Notice that in this problem, we are not
// adding |'1'|after single characters. Given astring |s|and an integer |k|. You
// need to delete at most |k| characters from |s|such that the run-length
// encoded version of |s|has minimum length. Find the minimum length of the
// run-length encodedversion of |s| after deleting at most |k| characters.
//

LEETCODE_BEGIN_RESOLVING(1531, StringCompressionII, Solution);

class Solution {
private:
  int lengthOfDigit(int x) {
    return x == 1 ? 0 : (x < 10 ? 1 : (x < 100 ? 2 : 3));
  }

  int helper(vector<vector<int>> &dp, string &str, int left, int k) {
    if (k < 0) {
      return dp.size();
    }
    if (left >= str.size() || str.size() - left <= k) {
      return 0;
    }

    int &res = dp[left][k];
    if (res != -1) {
      return res;
    }
    res = str.size();

    auto cnt = vector<int>(26, 0);
    for (int i = left, most = 0; i < str.size(); ++i) {
      most = max(most, ++cnt[str[i] - 'a']);
      res  = min(res, 1 + lengthOfDigit(most) +
                          helper(dp, str, i + 1, (k - (i - left + 1 - most))));
    }
    return res;
  }

public:
  int getLengthOfOptimalCompression(string s, int k) {
    auto dp = vector<vector<int>>(127, vector<int>(127, -1));
    return helper(dp, s, 0, k);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |0 <= k <= s.length|
// * |s| contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aaabcccd", k = 2
// Output: 4
// Explanation: Compressing s without deleting anything will give us "a3bc3d" of
// length 6. Deleting any of the characters 'a' or 'c' would at most decrease
// the length of the compressed string to 5, for instance delete 2 'a' then we
// will have s = "abcccd" which compressed is abc3d. Therefore, the optimal way
// is to delete 'b' and 'd', then the compressed version of s will be "a3c3" of
// length 4.
//

LEETCODE_SOLUTION_UNITTEST(1531, StringCompressionII, example_1) {
  auto   solution = MakeSolution();
  string s        = "aaabcccd";
  int    k        = 2;
  int    expect   = 4;
  int    actual   = solution->getLengthOfOptimalCompression(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aabbaa", k = 2
// Output: 2
// Explanation: If we delete both 'b' characters, the resulting compressed
// string would be "a4" of length 2.
//

LEETCODE_SOLUTION_UNITTEST(1531, StringCompressionII, example_2) {
  auto   solution = MakeSolution();
  string s        = "aabbaa";
  int    k        = 2;
  int    expect   = 2;
  int    actual   = solution->getLengthOfOptimalCompression(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "aaaaaaaaaaa", k = 0
// Output: 3
//
// Since k is zero, we cannot delete anything. The compressed string is "a11" of
// length 3.

LEETCODE_SOLUTION_UNITTEST(1531, StringCompressionII, example_3) {
  auto   solution = MakeSolution();
  string s        = "aaaaaaaaaaa";
  int    k        = 0;
  int    expect   = 3;
  int    actual   = solution->getLengthOfOptimalCompression(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
