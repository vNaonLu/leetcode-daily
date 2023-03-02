// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Removable Characters
//
// https://leetcode.com/problems/maximum-number-of-removable-characters/
//
// Question ID: 1898
// Difficult  : Medium
// Solve Date : 2022/07/19 12:27

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1898. Maximum Number of Removable Characters|:
//
// You are given two strings |s| and |p| where |p| is a subsequence of |s|. You
// are also given a distinct 0-indexed integer array |removable| containing a
// subset of indices of |s| ( |s| is also 0-indexed). You want to choose an
// integer |k| ( |0 <= k <= removable.length|) such that, after removing |k|
// characters from |s| using the first |k| indices in |removable|, |p| is still
// a subsequence of |s|. More formally, you will mark the character at
// |s[removable[i]]| for each |0 <= i < k|, then remove all marked characters
// and check if |p| is still a subsequence. Return the maximum |k| you can
// choose such that |p| is still a subsequence of |s| after the removals. A
// subsequence of a string is a new string generated from the original string
// with some characters (can be none) deleted without changing the relative
// order of the remaining characters.
//

LEETCODE_BEGIN_RESOLVING(1898, MaximumNumberOfRemovableCharacters, Solution);

class Solution {
private:
  bool helper(string s, string &p, int mid, vector<int> &rm) {
    for (int i = 0; i < mid; ++i) {
      s[rm[i]] = ' ';
    }
    auto it  = s.begin();
    auto pit = p.begin();
    while (it != s.end() && pit != p.end()) {
      if (*it++ == *pit) {
        ++pit;
      }
    }

    return pit == p.end();
  }

public:
  int maximumRemovals(string s, string p, vector<int> &removable) {
    int res = 0;
    int lo = 0, hi = removable.size();

    while (lo <= hi) {
      auto mid = lo + (hi - lo) / 2;
      if (helper(s, p, mid, removable)) {
        res = max(res, mid);
        lo  = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= p.length <= s.length <= 10⁵|
// * |0 <= removable.length < s.length|
// * |0 <= removable[i] < s.length|
// * |p| is a subsequence of |s|.
// * |s| and |p| both consist of lowercase English letters.
// * The elements in |removable| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcacb", p = "ab", removable = [3,1,0]
// Output: 2
//
// : After removing the characters at indices 3 and 1, "abcacb" becomes "accb".
// "ab" is a subsequence of "accb".
// If we remove the characters at indices 3, 1, and 0, "abcacb" becomes "ccb",
// and "ab" is no longer a subsequence. Hence, the maximum k is 2.

LEETCODE_SOLUTION_UNITTEST(1898, MaximumNumberOfRemovableCharacters,
                           example_1) {
  auto        solution  = MakeSolution();
  string      s         = "abcacb";
  string      p         = "ab";
  vector<int> removable = {3, 1, 0};
  int         expect    = 2;
  int         actual    = solution->maximumRemovals(s, p, removable);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcbddddd", p = "abcd", removable = [3,2,1,4,5,6]
// Output: 1
//
// : After removing the character at index 3, "abcbddddd" becomes "abcddddd".
// "abcd" is a subsequence of "abcddddd".

LEETCODE_SOLUTION_UNITTEST(1898, MaximumNumberOfRemovableCharacters,
                           example_2) {
  auto        solution  = MakeSolution();
  string      s         = "abcbddddd";
  string      p         = "abcd";
  vector<int> removable = {3, 2, 1, 4, 5, 6};
  int         expect    = 1;
  int         actual    = solution->maximumRemovals(s, p, removable);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abcab", p = "abc", removable = [0,1,2,3,4]
// Output: 0
//
// : If you remove the first index in the array removable, "abc" is no longer a
// subsequence.

LEETCODE_SOLUTION_UNITTEST(1898, MaximumNumberOfRemovableCharacters,
                           example_3) {
  auto        solution  = MakeSolution();
  string      s         = "abcab";
  string      p         = "abc";
  vector<int> removable = {0, 1, 2, 3, 4};
  int         expect    = 0;
  int         actual    = solution->maximumRemovals(s, p, removable);
  LCD_EXPECT_EQ(expect, actual);
}
