// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Kth Bit in Nth Binary String
//
// https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/
//
// Question ID: 1545
// Difficult  : Medium
// Solve Date : 2021/10/05 23:51

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1545. Find Kth Bit in Nth Binary String|:
//
// Given two positive integers |n| and |k|, the binary string |Sₙ| is formed as
// follows:
//
//  • |S₁ = "0"|
//
//  • |Sᵢ = S^{i - 1} + "1" + reverse(invert(S^{i - 1}))| for |i > 1|
// Where |+| denotes the concatenation operation, |reverse(x)| returns the
// reversed string |x|, and |invert(x)| inverts all the bits in |x| ( |0|
// changes to |1| and |1| changes to |0|). For example, the first four strings
// in the above sequence are:
//
//  • |S^{1 }= "0"|
//
//  • |S^{2 }= "011"|
//
//  • |S^{3 }= "0111001"|
//
//  • |S₄ = "011100110110001"|
// Return the |kᵗʰ| bit in |Sₙ|. It is guaranteed that |k| is valid for the
// given |n|.  
//

LEETCODE_BEGIN_RESOLVING(1545, FindKthBitInNthBinaryString, Solution);

class Solution {
public:
  char findKthBit(int n, int k) {
    if (n == 1)
      return '0';
    int half = 1 << (n - 1);
    if (k == half) {
      return '1';
    } else if (k < half) {
      return findKthBit(n - 1, k);
    } else {
      return findKthBit(n - 1, (half << 1) - k) == '0' ? '1' : '0';
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 20|
// * |1 <= k <= 2ⁿ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 1
// Output: "0"
//
// S₃ is "0111001".
// The 1ˢᵗ bit is "0".

LEETCODE_SOLUTION_UNITTEST(1545, FindKthBitInNthBinaryString, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  k        = 1;
  char expect   = '0';
  char actual   = solution->findKthBit(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, k = 11
// Output: "1"
//
// S₄ is "011100110110001".
// The 11ᵗʰ bit is "1".

LEETCODE_SOLUTION_UNITTEST(1545, FindKthBitInNthBinaryString, example_2) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  k        = 11;
  char expect   = '1';
  char actual   = solution->findKthBit(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
