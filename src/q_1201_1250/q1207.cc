// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Number of Occurrences
//
// https://leetcode.com/problems/unique-number-of-occurrences/
//
// Question ID: 1207
// Difficult  : Easy
// Solve Date : 2022/11/30 12:55

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1207. Unique Number of Occurrences|:
//
// Given an array of integers |arr|, return |true| if the number of occurrences
// of each value in the array is unique or |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(1207, UniqueNumberOfOccurrences, Solution);

class Solution {
public:
  bool uniqueOccurrences(vector<int> &arr) {
    auto freq = unordered_map<int, int>();
    for (auto x : arr) {
      ++freq[x];
    }
    auto is_unique = unordered_set<int>();
    for (auto &x : freq) {
      if (!is_unique.emplace(x.second).second) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 1000|
// * |-1000 <= arr[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,2,1,1,3]
// Output: true
//
// The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the
// same number of occurrences.

LEETCODE_SOLUTION_UNITTEST(1207, UniqueNumberOfOccurrences, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 2, 1, 1, 3};
  bool        expect   = true;
  bool        actual   = solution->uniqueOccurrences(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1207, UniqueNumberOfOccurrences, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2};
  bool        expect   = false;
  bool        actual   = solution->uniqueOccurrences(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1207, UniqueNumberOfOccurrences, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {-3, 0, 1, -3, 1, 1, 1, -3, 10, 0};
  bool        expect   = true;
  bool        actual   = solution->uniqueOccurrences(arr);
  LCD_EXPECT_EQ(expect, actual);
}
