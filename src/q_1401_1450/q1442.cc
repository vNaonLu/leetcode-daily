// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Triplets That Can Form Two Arrays of Equal XOR
//
// https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/
//
// Question ID: 1442
// Difficult  : Medium
// Solve Date : 2024/05/30 22:51

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1442. Count Triplets That Can Form Two Arrays of Equal XOR|:
//
// Given an array of integers |arr|.
// We want to select three indices |i|, |j| and |k| where |(0 <= i < j <= k <
// arr.length)|. Let's define |a| and |b| as follows:
//
//  • |a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]|
//
//  • |b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]|
// Note that ^ denotes the bitwise-xor operation.
// Return the number of triplets ( |i|, |j| and |k|) Where |a == b|.
//
//

LEETCODE_BEGIN_RESOLVING(1442, CountTripletsThatCanFormTwoArraysOfEqualXOR,
                         Solution);

class Solution {
public:
  int countTriplets(vector<int> &arr) {
    int         n = arr.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      prefix[i + 1] = prefix[i] ^ arr[i];
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      for (int k = i; k < n; ++k) {
        if (prefix[i] == prefix[k + 1]) {
          res += k - i;
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
// * |1 <= arr.length <= 300|
// * |1 <= arr[i] <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,3,1,6,7]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1442, CountTripletsThatCanFormTwoArraysOfEqualXOR,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 3, 1, 6, 7};
  int         expect   = 4;
  int         actual   = solution->countTriplets(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,1,1,1,1]
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(1442, CountTripletsThatCanFormTwoArraysOfEqualXOR,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 1, 1, 1, 1};
  int         expect   = 10;
  int         actual   = solution->countTriplets(arr);
  LCD_EXPECT_EQ(expect, actual);
}
