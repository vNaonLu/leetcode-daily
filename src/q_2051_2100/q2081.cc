// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Sum of k-Mirror Numbers
//
// https://leetcode.com/problems/sum-of-k-mirror-numbers/
//
// Question ID: 2081
// Difficult  : Hard
// Solve Date : 2025/06/23 19:30

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2081. Sum of k-Mirror Numbers|:
//
// A k-mirror number is a positive integer without leading zeros that reads the
// same both forward and backward in base-10 as well as in base-k.
//
//  • For example, |9| is a 2-mirror number. The representation of |9| in
//  base-10 and base-2 are |9| and |1001| respectively, which read the same both
//  forward and backward.
//
//  • On the contrary, |4| is not a 2-mirror number. The representation of |4|
//  in base-2 is |100|, which does not read the same both forward and backward.
// Given the base |k| and the number |n|, return the sum of the |n| smallest
// k-mirror numbers.
//
//

LEETCODE_BEGIN_RESOLVING(2081, SumOfKMirrorNumbers, Solution);

class Solution {
public:
  long long createPalindrome(long long num, bool odd) {
    long long x = num;
    if (odd)
      x /= 10;
    while (x > 0) {
      num = num * 10 + x % 10;
      x /= 10;
    }
    return num;
  }

  bool isPalindrome(long long num, int base) {
    vector<int> digits;
    while (num > 0) {
      digits.push_back(num % base);
      num /= base;
    }
    int i = 0, j = digits.size() - 1;
    while (i < j) {
      if (digits[i++] != digits[j--])
        return false;
    }
    return true;
  }

  long long kMirror(int k, int n) {
    long long sum = 0;
    for (long long len = 1; n > 0; len *= 10) {
      for (long long i = len; n > 0 && i < len * 10; i++) {
        long long p = createPalindrome(i, true);
        if (isPalindrome(p, k)) {
          sum += p;
          n--;
        }
      }
      for (long long i = len; n > 0 && i < len * 10; i++) {
        long long p = createPalindrome(i, false);
        if (isPalindrome(p, k)) {
          sum += p;
          n--;
        }
      }
    }
    return sum;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= k <= 9|
// * |1 <= n <= 30|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: k = 2, n = 5
// Output: 25
// Explanation:
// The 5 smallest 2-mirror numbers and their representations in base-2 are
// listed as follows:
//  base-10 base-2
//  1 1
//  3 11
//  5 101
//  7 111
//  9 1001
// Their sum = 1 + 3 + 5 + 7 + 9 = 25.
//

LEETCODE_SOLUTION_UNITTEST(2081, SumOfKMirrorNumbers, example_1) {
  auto      solution = MakeSolution();
  int       k        = 2;
  int       n        = 5;
  long long expect   = 25;
  long long actual   = solution->kMirror(k, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: k = 3, n = 7
// Output: 499
// Explanation:
// The 7 smallest 3-mirror numbers are and their representations in base-3 are
// listed as follows:
//  base-10 base-3
//  1 1
//  2 2
//  4 11
//  8 22
//  121 11111
//  151 12121
//  212 21212
// Their sum = 1 + 2 + 4 + 8 + 121 + 151 + 212 = 499.
//

LEETCODE_SOLUTION_UNITTEST(2081, SumOfKMirrorNumbers, example_2) {
  auto      solution = MakeSolution();
  int       k        = 3;
  int       n        = 7;
  long long expect   = 499;
  long long actual   = solution->kMirror(k, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: k = 7, n = 17
// Output: 20379000
//

LEETCODE_SOLUTION_UNITTEST(2081, SumOfKMirrorNumbers, example_3) {
  auto      solution = MakeSolution();
  int       k        = 7;
  int       n        = 17;
  long long expect   = 20379000;
  long long actual   = solution->kMirror(k, n);
  LCD_EXPECT_EQ(expect, actual);
}
