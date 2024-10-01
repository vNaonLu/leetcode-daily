// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Check If Array Pairs Are Divisible by k
//
// https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/
//
// Question ID: 1497
// Difficult  : Medium
// Solve Date : 2024/10/01 19:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1497. Check If Array Pairs Are Divisible by k|:
//
// Given an array of integers |arr| of even length |n| and an integer |k|.
// We want to divide the array into exactly |n / 2| pairs such that the sum of
// each pair is divisible by |k|. Return |true| If you can find a way to do that
// or |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(1497, CheckIfArrayPairsAreDivisibleByK, Solution);

class Solution {
public:
  bool canArrange(vector<int> &arr, int k) {
    vector<int> freq(k, 0);
    for (auto x : arr) {
      int rem = ((x % k) + k) % k;
      ++freq[rem];
    }

    if (freq[0] % 2 != 0) {
      return false;
    }

    for (int i = 1; i <= k / 2; ++i) {
      if (freq[i] != freq[k - i]) {
        return false;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |arr.length == n|
// * |1 <= n <= 10⁵|
// * |n| is even.
// * |-10⁹ <= arr[i] <= 10⁹|
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1497, CheckIfArrayPairsAreDivisibleByK, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4, 5, 10, 6, 7, 8, 9};
  int         k        = 5;
  bool        expect   = true;
  bool        actual   = solution->canArrange(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2,3,4,5,6], k = 7
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1497, CheckIfArrayPairsAreDivisibleByK, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4, 5, 6};
  int         k        = 7;
  bool        expect   = true;
  bool        actual   = solution->canArrange(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [1,2,3,4,5,6], k = 10
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1497, CheckIfArrayPairsAreDivisibleByK, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4, 5, 6};
  int         k        = 10;
  bool        expect   = false;
  bool        actual   = solution->canArrange(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [-1,-1,-1,-1,2,2,-2,-2]
// 3
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1497, CheckIfArrayPairsAreDivisibleByK,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {-1, -1, -1, -1, 2, 2, -2, -2};
  int         k        = 3;
  bool        expect   = false;
  bool        actual   = solution->canArrange(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}
