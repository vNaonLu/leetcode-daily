// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Decode XORed Array
//
// https://leetcode.com/problems/decode-xored-array/
//
// Question ID: 1720
// Difficult  : Easy
// Solve Date : 2022/02/05 15:26

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1720. Decode XORed Array|:
//
// There is a hidden integer array |arr| that consists of |n| non-negative
// integers. It was encoded into another integer array |encoded| of length |n -
// 1|, such that |encoded[i] = arr[i] XOR arr[i + 1]|. For example, if |arr =
// [1,0,2,1]|, then |encoded = [1,2,3]|. You are given the |encoded| array. You
// are also given an integer |first|, that is the first element of |arr|, i.e.
// |arr[0]|. Return the original array |arr|. It can be proved that the answer
// exists and is unique.  
//

LEETCODE_BEGIN_RESOLVING(1720, DecodeXORedArray, Solution);

class Solution {
public:
  vector<int> decode(vector<int> &encoded, int first) {
    vector<int> res(encoded.size() + 1);
    res.front() = first;
    for (int i = 0; i < encoded.size(); ++i) {
      res[i + 1] = encoded[i] ^ res[i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁴|
// * |encoded.length == n - 1|
// * |0 <= encoded[i] <= 10⁵|
// * |0 <= first <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: encoded = [1,2,3], first = 1
// Output: [1,0,2,1]
//
// If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0 XOR 2, 2 XOR 1]
// = [1,2,3]

LEETCODE_SOLUTION_UNITTEST(1720, DecodeXORedArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> encoded  = {1, 2, 3};
  int         first    = 1;
  vector<int> expect   = {1, 0, 2, 1};
  vector<int> actual   = solution->decode(encoded, first);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: encoded = [6,2,7,3], first = 4
// Output: [4,2,0,7,4]
//

LEETCODE_SOLUTION_UNITTEST(1720, DecodeXORedArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> encoded  = {6, 2, 7, 3};
  int         first    = 4;
  vector<int> expect   = {4, 2, 0, 7, 4};
  vector<int> actual   = solution->decode(encoded, first);
  LCD_EXPECT_EQ(expect, actual);
}
