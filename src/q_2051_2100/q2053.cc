// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Kth Distinct String in an Array
//
// https://leetcode.com/problems/kth-distinct-string-in-an-array/
//
// Question ID: 2053
// Difficult  : Easy
// Solve Date : 2023/01/05 16:23

#include <iosfwd>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2053. Kth Distinct String in an Array|:
//
// A distinct string is a string that is present only once in an array.
// Given an array of strings |arr|, and an integer |k|, return the |kᵗʰ|
// distinct string present in |arr|. If there are fewer than |k| distinct
// strings, return an empty string |""|. Note that the strings are considered in
// the order in which they appear in the array.
//

LEETCODE_BEGIN_RESOLVING(2053, KthDistinctStringInAnArray, Solution);

class Solution {
public:
  string kthDistinct(vector<string> &arr, int k) {
    list<string>                                  candidates;
    unordered_set<string>                         appeared;
    unordered_map<string, list<string>::iterator> memo;

    for (auto &s : arr) {
      auto iter = memo.find(s);
      if (iter == memo.end() && !appeared.count(s)) {
        candidates.emplace_back(s);
        memo[s] = --candidates.end();
        appeared.emplace(s);
      } else {
        if (iter != memo.end()) {
          candidates.erase(iter->second);
          memo.erase(iter);
        }
      }
    }
    auto res = candidates.begin();
    while (--k && res != candidates.end()) {
      ++res;
    }
    return res == candidates.end() ? "" : std::move(*res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= arr.length <= 1000|
// * |1 <= arr[i].length <= 5|
// * |arr[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = ["d","b","c","b","c","a"], k = 2
// Output: "a"
//
// The only distinct strings in arr are "d" and "a".
// "d" appears 1ˢᵗ, so it is the 1ˢᵗ distinct string.
// "a" appears 2ⁿᵈ, so it is the 2ⁿᵈ distinct string.
// Since k == 2, "a" is returned.

LEETCODE_SOLUTION_UNITTEST(2053, KthDistinctStringInAnArray, example_1) {
  auto           solution = MakeSolution();
  vector<string> arr      = {"d", "b", "c", "b", "c", "a"};
  int            k        = 2;
  string         expect   = "a";
  string         actual   = solution->kthDistinct(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = ["aaa","aa","a"], k = 1
// Output: "aaa"
//
// All strings in arr are distinct, so the 1ˢᵗ string "aaa" is returned.

LEETCODE_SOLUTION_UNITTEST(2053, KthDistinctStringInAnArray, example_2) {
  auto           solution = MakeSolution();
  vector<string> arr      = {"aaa", "aa", "a"};
  int            k        = 1;
  string         expect   = "aaa";
  string         actual   = solution->kthDistinct(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = ["a","b","a"], k = 3
// Output: ""
//
// The only distinct string is "b". Since there are fewer than 3 distinct
// strings, we return an empty string "".

LEETCODE_SOLUTION_UNITTEST(2053, KthDistinctStringInAnArray, example_3) {
  auto           solution = MakeSolution();
  vector<string> arr      = {"a", "b", "a"};
  int            k        = 3;
  string         expect   = "";
  string         actual   = solution->kthDistinct(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}
