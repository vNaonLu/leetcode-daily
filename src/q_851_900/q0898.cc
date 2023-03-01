// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Bitwise ORs of Subarrays
//
// https://leetcode.com/problems/bitwise-ors-of-subarrays/
//
// Question ID: 898
// Difficult  : Medium
// Solve Date : 2021/10/06 00:20

#include <array>
#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |898. Bitwise ORs of Subarrays|:
//
// Given an integer array |arr|, return the number of distinct bitwise ORs of
// all the non-empty subarrays of |arr|. The bitwise OR of a subarray is the
// bitwise OR of each integer in the subarray. The bitwise OR of a subarray of
// one integer is that integer. A subarray is a contiguous non-empty sequence of
// elements within an array.  
//

LEETCODE_BEGIN_RESOLVING(898, BitwiseORsOfSubarrays, Solution);

class Solution {
public:
  int subarrayBitwiseORs(vector<int> &arr) {
    vector<int> res;
    int         l = 0, r;
    for (const auto &a : arr) {
      r = res.size();
      res.push_back(a);
      for (int i = l; i < r; ++i) {
        int val = res[i] | a;
        if (res.back() != val)
          res.push_back(val);
      }
      l = r;
    }
    return unordered_set(res.begin(), res.end()).size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 5 * 10⁴|
// * |0 <= arr[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [0]
// Output: 1
//
// There is only one possible result: 0.

LEETCODE_SOLUTION_UNITTEST(898, BitwiseORsOfSubarrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0};
  int         expect   = 1;
  int         actual   = solution->subarrayBitwiseORs(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,1,2]
// Output: 3
//
// The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
// These yield the results 1, 1, 2, 1, 3, 3.
// There are 3 unique values, so the answer is 3.

LEETCODE_SOLUTION_UNITTEST(898, BitwiseORsOfSubarrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 1, 2};
  int         expect   = 3;
  int         actual   = solution->subarrayBitwiseORs(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [1,2,4]
// Output: 6
//
// The possible results are 1, 2, 3, 4, 6, and 7.

LEETCODE_SOLUTION_UNITTEST(898, BitwiseORsOfSubarrays, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 4};
  int         expect   = 6;
  int         actual   = solution->subarrayBitwiseORs(arr);
  LCD_EXPECT_EQ(expect, actual);
}
