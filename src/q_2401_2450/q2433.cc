// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find The Original Array of Prefix Xor
//
// https://leetcode.com/problems/find-the-original-array-of-prefix-xor/
//
// Question ID: 2433
// Difficult  : Medium
// Solve Date : 2023/10/31 19:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2433. Find The Original Array of Prefix Xor|:
//
// You are given an integer array |pref| of size |n|. Find and return the array
// |arr| of size |n| that satisfies:
//
//  • |pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i]|.
// Note that |^| denotes the bitwise-xor operation.
// It can be proven that the answer is unique.
//
//

LEETCODE_BEGIN_RESOLVING(2433, FindTheOriginalArrayOfPrefixXor, Solution);

class Solution {
public:
  vector<int> findArray(vector<int> &pref) {
    vector<int> res;
    res.emplace_back(pref.front());

    for (int i = 1; i < pref.size(); ++i) {
      res.emplace_back(pref[i - 1] ^ pref[i]);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= pref.length <= 10⁵|
// * |0 <= pref[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: pref = [5,2,0,3,1]
// Output: [5,7,2,3,2]
//
// From the array [5,7,2,3,2] we have the following:
// - pref[0] = 5.
// - pref[1] = 5 ^ 7 = 2.
// - pref[2] = 5 ^ 7 ^ 2 = 0.
// - pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3.
// - pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1.

LEETCODE_SOLUTION_UNITTEST(2433, FindTheOriginalArrayOfPrefixXor, example_1) {
  auto        solution = MakeSolution();
  vector<int> pref     = {5, 2, 0, 3, 1};
  vector<int> expect   = {5, 7, 2, 3, 2};
  vector<int> actual   = solution->findArray(pref);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: pref = [13]
// Output: [13]
//
// We have pref[0] = arr[0] = 13.

LEETCODE_SOLUTION_UNITTEST(2433, FindTheOriginalArrayOfPrefixXor, example_2) {
  auto        solution = MakeSolution();
  vector<int> pref     = {13};
  vector<int> expect   = {13};
  vector<int> actual   = solution->findArray(pref);
  LCD_EXPECT_EQ(expect, actual);
}
