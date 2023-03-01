// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Original Array From Doubled Array
//
// https://leetcode.com/problems/find-original-array-from-doubled-array/
//
// Question ID: 2007
// Difficult  : Medium
// Solve Date : 2022/09/15 20:09

#include <algorithm>
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2007. Find Original Array From Doubled Array|:
//
// An integer array |original| is transformed into a doubled array |changed| by
// appending twice the value of every element in |original|, and then randomly
// shuffling the resulting array. Given an array |changed|, return |original| if
// |changed| is a doubled array. If |changed| is not a doubled array, return an
// empty array. The elements in |original| may be returned in any order.
//

LEETCODE_BEGIN_RESOLVING(2007, FindOriginalArrayFromDoubledArray, Solution);

class Solution {
public:
  vector<int> findOriginalArray(vector<int> &changed) {
    if (changed.size() & 1) {
      return {};
    }
    sort(changed.begin(), changed.end());
    auto res  = vector<int>();
    auto freq = unordered_map<int, int>();
    for (auto x : changed) {
      ++freq[x];
    }
    for (auto x : changed) {
      auto curr = freq.find(x);
      if (curr->second != 0) {
        auto find_double = freq.find(x * 2);
        if (find_double == freq.end() || find_double->second == 0) {
          return {};
        }
        res.emplace_back(curr->first);
        --curr->second;
        --find_double->second;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= changed.length <= 10⁵|
// * |0 <= changed[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: changed = [1,3,4,2,6,8]
// Output: [1,3,4]
//
// One possible original array could be [1,3,4]:
// - Twice the value of 1 is 1 * 2 = 2.
// - Twice the value of 3 is 3 * 2 = 6.
// - Twice the value of 4 is 4 * 2 = 8.
// Other original arrays could be [4,3,1] or [3,1,4].

LEETCODE_SOLUTION_UNITTEST(2007, FindOriginalArrayFromDoubledArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> changed  = {1, 3, 4, 2, 6, 8};
  vector<int> expect   = {1, 3, 4};
  vector<int> actual   = solution->findOriginalArray(changed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: changed = [6,3,0,1]
// Output: []
//
// changed is not a doubled array.

LEETCODE_SOLUTION_UNITTEST(2007, FindOriginalArrayFromDoubledArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> changed  = {6, 3, 0, 1};
  vector<int> expect   = {};
  vector<int> actual   = solution->findOriginalArray(changed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: changed = [1]
// Output: []
//
// changed is not a doubled array.

LEETCODE_SOLUTION_UNITTEST(2007, FindOriginalArrayFromDoubledArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> changed  = {1};
  vector<int> expect   = {};
  vector<int> actual   = solution->findOriginalArray(changed);
  LCD_EXPECT_EQ(expect, actual);
}
