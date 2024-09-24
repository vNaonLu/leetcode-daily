// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Length of the Longest Common Prefix
//
// https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/
//
// Question ID: 3043
// Difficult  : Medium
// Solve Date : 2024/09/24 19:53

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3043. Find the Length of the Longest Common Prefix|:
//
// You are given two arrays with positive integers |arr1| and |arr2|.
// A prefix of a positive integer is an integer formed by one or more of its
// digits, starting from its leftmost digit. For example, |123| is a prefix of
// the integer |12345|, while |234| is not. A common prefix of two integers |a|
// and |b| is an integer |c|, such that |c| is a prefix of both |a| and |b|. For
// example, |5655359| and |56554| have a common prefix |565| while |1223| and
// |43456| do not have a common prefix. You need to find the length of the
// longest common prefix between all pairs of integers |(x, y)| such that |x|
// belongs to |arr1| and |y| belongs to |arr2|. Return the length of the longest
// common prefix among all pairs. If no common prefix exists among them, return
// |0|.
//
//

LEETCODE_BEGIN_RESOLVING(3043, FindTheLengthOfTheLongestCommonPrefix, Solution);

class Solution {
public:
  int longestCommonPrefix(vector<int> &arr1, vector<int> &arr2) {
    unordered_map<string, int> prefix_mp;
    for (auto x : arr1) {
      auto   str = to_string(x);
      string p;
      for (auto c : str) {
        p += c;
        ++prefix_mp[p];
      }
    }

    int res = 0;
    for (auto x : arr2) {
      auto   str = to_string(x);
      string p;
      for (auto c : str) {
        p += c;
        if (prefix_mp.count(p)) {
          res = max<int>(res, p.size());
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr1.length, arr2.length <= 5 * 10⁴|
// * |1 <= arr1[i], arr2[i] <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr1 = [1,10,100], arr2 = [1000]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3043, FindTheLengthOfTheLongestCommonPrefix,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {1, 10, 100};
  vector<int> arr2     = {1000};
  int         expect   = 3;
  int         actual   = solution->longestCommonPrefix(arr1, arr2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr1 = [1,2,3], arr2 = [4,4,4]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3043, FindTheLengthOfTheLongestCommonPrefix,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {1, 2, 3};
  vector<int> arr2     = {4, 4, 4};
  int         expect   = 0;
  int         actual   = solution->longestCommonPrefix(arr1, arr2);
  LCD_EXPECT_EQ(expect, actual);
}
