// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Prime Number of Set Bits in Binary Representation
//
// https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/
//
// Question ID: 762
// Difficult  : Easy
// Solve Date : 2021/10/06 01:12

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |762. Prime Number of Set Bits in Binary Representation|:
//
// Given two integers |left| and |right|, return the count of numbers in the
// inclusive range |[left, right]| having a prime number of set bits in their
// binary representation. Recall that the number of set bits an integer has is
// the number of |1|'s present when written in binary.
//
//  • For example, |21| written in binary is |10101|, which has |3| set bits.
//  
//

LEETCODE_BEGIN_RESOLVING(762, PrimeNumberOfSetBitsInBinaryRepresentation,
                         Solution);

class Solution {
public:
  int countPrimeSetBits(int left, int right) {
    vector<bool> primes(33, true);
    primes[0] = primes[1] = false;
    for (int i = 2; i * i <= 32; ++i)
      if (primes[i])
        for (int j = 2; j * i <= 32; ++j)
          primes[i * j] = false;
    int res = 0;
    while (left <= right)
      if (primes[__builtin_popcount(left++)])
        ++res;
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= left <= right <= 10⁶|
// * |0 <= right - left <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: left = 6, right = 10
// Output: 4
//
// 6 -> 110 (2 set bits, 2 is prime)
// 7 -> 111 (3 set bits, 3 is prime)
// 8 -> 1000 (1 set bit, 1 is not prime)
// 9 -> 1001 (2 set bits, 2 is prime)
// 10 -> 1010 (2 set bits, 2 is prime)
// 4 numbers have a prime number of set bits.

LEETCODE_SOLUTION_UNITTEST(762, PrimeNumberOfSetBitsInBinaryRepresentation,
                           example_1) {
  auto solution = MakeSolution();
  int  left     = 6;
  int  right    = 10;
  int  expect   = 4;
  int  actual   = solution->countPrimeSetBits(left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: left = 10, right = 15
// Output: 5
//
// 10 -> 1010 (2 set bits, 2 is prime)
// 11 -> 1011 (3 set bits, 3 is prime)
// 12 -> 1100 (2 set bits, 2 is prime)
// 13 -> 1101 (3 set bits, 3 is prime)
// 14 -> 1110 (3 set bits, 3 is prime)
// 15 -> 1111 (4 set bits, 4 is not prime)
// 5 numbers have a prime number of set bits.

LEETCODE_SOLUTION_UNITTEST(762, PrimeNumberOfSetBitsInBinaryRepresentation,
                           example_2) {
  auto solution = MakeSolution();
  int  left     = 10;
  int  right    = 15;
  int  expect   = 5;
  int  actual   = solution->countPrimeSetBits(left, right);
  LCD_EXPECT_EQ(expect, actual);
}
