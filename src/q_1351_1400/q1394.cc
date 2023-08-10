// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Lucky Integer in an Array
//
// https://leetcode.com/problems/find-lucky-integer-in-an-array/
//
// Question ID: 1394
// Difficult  : Easy
// Solve Date : 2023/08/10 19:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1394. Find Lucky Integer in an Array|:
//
// Given an array of integers |arr|, a lucky integer is an integer that has a
// frequency in the array equal to its value. Return the largest lucky integer
// in the array. If there is no lucky integer return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(1394, FindLuckyIntegerInAnArray, Solution);

class Solution {
public:
  int findLucky(vector<int> &arr) {
    vector<int> freq(501, 0);
    for (auto x : arr) {
      ++freq[x];
    }
    for (int i = freq.size() - 1; i > 0; --i) {
      if (freq[i] == i) {
        return i;
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 500|
// * |1 <= arr[i] <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,2,3,4]
// Output: 2
//
// The only lucky number in the array is 2 because frequency[2] == 2.

LEETCODE_SOLUTION_UNITTEST(1394, FindLuckyIntegerInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 2, 3, 4};
  int         expect   = 2;
  int         actual   = solution->findLucky(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2,2,3,3,3]
// Output: 3
//
// 1, 2 and 3 are all lucky numbers, return the largest of them.

LEETCODE_SOLUTION_UNITTEST(1394, FindLuckyIntegerInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 2, 3, 3, 3};
  int         expect   = 3;
  int         actual   = solution->findLucky(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [2,2,2,3,3]
// Output: -1
//
// There are no lucky numbers in the array.

LEETCODE_SOLUTION_UNITTEST(1394, FindLuckyIntegerInAnArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 2, 2, 3, 3};
  int         expect   = -1;
  int         actual   = solution->findLucky(arr);
  LCD_EXPECT_EQ(expect, actual);
}
