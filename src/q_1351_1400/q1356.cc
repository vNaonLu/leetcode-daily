// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Integers by The Number of 1 Bits
//
// https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/
//
// Question ID: 1356
// Difficult  : Easy
// Solve Date : 2021/10/06 00:58

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1356. Sort Integers by The Number of 1 Bits|:
//
// You are given an integer array |arr|. Sort the integers in the array in
// ascending order by the number of |1|'s in their binary representation and in
// case of two or more integers have the same number of |1|'s you have to sort
// them in ascending order. Return the array after sorting it.  
//

LEETCODE_BEGIN_RESOLVING(1356, SortIntegersByTheNumberOf1Bits, Solution);

class Solution {
public:
  vector<int> sortByBits(vector<int> &arr) {
    sort(arr.begin(), arr.end(), [](const int &a, const int &b) {
      int x = __builtin_popcount(a), y = __builtin_popcount(b);
      return x == y ? a < b : x < y;
    });
    return arr;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 500|
// * |0 <= arr[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [0,1,2,3,4,5,6,7,8]
// Output: [0,1,2,4,8,3,5,6,7]
// Explantion: [0] is the only integer with 0 bits.
// [1,2,4,8] all have 1 bit.
// [3,5,6] have 2 bits.
// [7] has 3 bits.
// The sorted array by bits is [0,1,2,4,8,3,5,6,7]
//

LEETCODE_SOLUTION_UNITTEST(1356, SortIntegersByTheNumberOf1Bits, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> expect   = {0, 1, 2, 4, 8, 3, 5, 6, 7};
  vector<int> actual   = solution->sortByBits(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
// Output: [1,2,4,8,16,32,64,128,256,512,1024]
// Explantion: All integers have 1 bit in the binary representation, you should
// just sort them in ascending order.
//

LEETCODE_SOLUTION_UNITTEST(1356, SortIntegersByTheNumberOf1Bits, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
  vector<int> expect   = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
  vector<int> actual   = solution->sortByBits(arr);
  LCD_EXPECT_EQ(expect, actual);
}
