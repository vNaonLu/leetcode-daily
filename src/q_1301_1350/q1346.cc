// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check If N and Its Double Exist
//
// https://leetcode.com/problems/check-if-n-and-its-double-exist/
//
// Question ID: 1346
// Difficult  : Easy
// Solve Date : 2022/04/11 18:30

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1346. Check If N and Its Double Exist|:
//
// Given an array |arr| of integers, check if there exist two indices |i| and
// |j| such that :
//
//  • |i != j|
//
//  • |0 <= i, j < arr.length|
//
//  • |arr[i] == 2 * arr[j]|
//  
//

LEETCODE_BEGIN_RESOLVING(1346, CheckIfNAndItsDoubleExist, Solution);

class Solution {
public:
  bool checkIfExist(vector<int> &arr) {
    unordered_set<int> memos;
    for (auto &x : arr) {
      if (memos.count(x * 2)) {

        return true;
      } else if (!(x & 1) && memos.count(x / 2)) {

        return true;
      }
      memos.emplace(x);
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= arr.length <= 500|
// * |-10³ <= arr[i] <= 10³|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [10,2,5,3]
// Output: true
//
// For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]

LEETCODE_SOLUTION_UNITTEST(1346, CheckIfNAndItsDoubleExist, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {10, 2, 5, 3};
  bool        expect   = true;
  bool        actual   = solution->checkIfExist(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [3,1,7,11]
// Output: false
//
// There is no i and j that satisfy the conditions.

LEETCODE_SOLUTION_UNITTEST(1346, CheckIfNAndItsDoubleExist, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 1, 7, 11};
  bool        expect   = false;
  bool        actual   = solution->checkIfExist(arr);
  LCD_EXPECT_EQ(expect, actual);
}
