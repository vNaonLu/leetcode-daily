// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Defuse the Bomb
//
// https://leetcode.com/problems/defuse-the-bomb/
//
// Question ID: 1652
// Difficult  : Easy
// Solve Date : 2022/12/19 21:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1652. Defuse the Bomb|:
//
// You have a bomb to defuse, and your time is running out! Your informer will
// provide you with a circular array |code|of length of |n|and a key |k|. To
// decrypt the code, you must replace every number. All the numbers are replaced
// simultaneously.
//
//  • If |k > 0|, replace the |iᵗʰ| number with the sum of the next |k| numbers.
//
//  • If |k < 0|, replace the |iᵗʰ| number with the sum of the previous |k|
//  numbers.
//
//  • If |k == 0|, replace the |iᵗʰ| number with |0|.
// As |code| is circular, the next element of |code[n-1]| is |code[0]|, and the
// previous element of |code[0]| is |code[n-1]|. Given the circular array |code|
// and an integer key |k|, return the decrypted code to defuse the bomb!
//

LEETCODE_BEGIN_RESOLVING(1652, DefuseTheBomb, Solution);

class Solution {
public:
  vector<int> decrypt(vector<int> &code, int k) {
    if (k == 0) {
      return vector<int>(code.size());
    } else {
      auto n   = code.size();
      auto res = vector<int>(n);
      if (k > 0) {
        for (int i = 0; i < n; ++i) {
          for (int j = 1; j <= k; ++j) {
            res[i] += code[(i + j) % n];
          }
        }
      } else {
        for (int i = 0; i < n; ++i) {
          for (int j = -1; j >= k; --j) {
            res[i] += code[(i + j + n) % n];
          }
        }
      }
      return res;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == code.length|
// * |1 <= n<= 100|
// * |1 <= code[i] <= 100|
// * |-(n - 1) <= k <= n - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: code = [5,7,1,4], k = 3
// Output: [12,10,16,13]
//
// Each number is replaced by the sum of the next 3 numbers. The decrypted code
// is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.

LEETCODE_SOLUTION_UNITTEST(1652, DefuseTheBomb, example_1) {
  auto        solution = MakeSolution();
  vector<int> code     = {5, 7, 1, 4};
  int         k        = 3;
  vector<int> expect   = {12, 10, 16, 13};
  vector<int> actual   = solution->decrypt(code, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: code = [1,2,3,4], k = 0
// Output: [0,0,0,0]
//
// When k is zero, the numbers are replaced by 0.

LEETCODE_SOLUTION_UNITTEST(1652, DefuseTheBomb, example_2) {
  auto        solution = MakeSolution();
  vector<int> code     = {1, 2, 3, 4};
  int         k        = 0;
  vector<int> expect   = {0, 0, 0, 0};
  vector<int> actual   = solution->decrypt(code, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: code = [2,4,9,3], k = -2
// Output: [12,5,6,13]
//
// The decrypted code is [3+9, 2+3, 4+2, 9+4]. Notice that the numbers wrap
// around again. If k is negative, the sum is of the previous numbers.

LEETCODE_SOLUTION_UNITTEST(1652, DefuseTheBomb, example_3) {
  auto        solution = MakeSolution();
  vector<int> code     = {2, 4, 9, 3};
  int         k        = -2;
  vector<int> expect   = {12, 5, 6, 13};
  vector<int> actual   = solution->decrypt(code, k);
  LCD_EXPECT_EQ(expect, actual);
}
