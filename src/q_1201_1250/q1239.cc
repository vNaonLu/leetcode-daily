// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Length of a Concatenated String with Unique Characters
//
// https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
//
// Question ID: 1239
// Difficult  : Medium
// Solve Date : 2021/09/22 08:00

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1239. Maximum Length of a Concatenated String with Unique
// Characters|:
//
// You are given an array of strings |arr|. A string |s| is formed by the
// concatenation of a subsequence of |arr| that has unique characters. Return
// the maximum possible length of |s|. A subsequence is an array that can be
// derived from another array by deleting some or no elements without changing
// the order of the remaining elements.  
//

LEETCODE_BEGIN_RESOLVING(1239,
                         MaximumLengthOfAConcatenatedStringWithUniqueCharacters,
                         Solution);

class Solution {
public:
  int maxLength(vector<string> &arr) {
    int            res     = 0;
    vector<string> combine = {""};
    for (string &w : arr) {
      int length = combine.size();
      for (int i = 0; i < length; ++i) {
        string              str = combine[i] + w;
        unordered_set<char> str_set(str.begin(), str.end());
        if (str_set.size() != str.size())
          continue;
        combine.push_back(str);
        res = max(res, (int)str.size());
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 16|
// * |1 <= arr[i].length <= 26|
// * |arr[i]| contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = ["un","iq","ue"]
// Output: 4
//
// All the valid concatenations are:
// - ""
// - "un"
// - "iq"
// - "ue"
// - "uniq" ("un" + "iq")
// - "ique" ("iq" + "ue")
// Maximum length is 4.

LEETCODE_SOLUTION_UNITTEST(
    1239, MaximumLengthOfAConcatenatedStringWithUniqueCharacters, example_1) {
  auto           solution = MakeSolution();
  vector<string> arr      = {"un", "iq", "ue"};
  int            expect   = 4;
  int            actual   = solution->maxLength(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = ["cha","r","act","ers"]
// Output: 6
//
// Possible longest valid concatenations are "chaers" ("cha" + "ers") and
// "acters" ("act" + "ers").

LEETCODE_SOLUTION_UNITTEST(
    1239, MaximumLengthOfAConcatenatedStringWithUniqueCharacters, example_2) {
  auto           solution = MakeSolution();
  vector<string> arr      = {"cha", "r", "act", "ers"};
  int            expect   = 6;
  int            actual   = solution->maxLength(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
// Output: 26
//
// The only string in arr has all 26 characters.

LEETCODE_SOLUTION_UNITTEST(
    1239, MaximumLengthOfAConcatenatedStringWithUniqueCharacters, example_3) {
  auto           solution = MakeSolution();
  vector<string> arr      = {"abcdefghijklmnopqrstuvwxyz"};
  int            expect   = 26;
  int            actual   = solution->maxLength(arr);
  LCD_EXPECT_EQ(expect, actual);
}
