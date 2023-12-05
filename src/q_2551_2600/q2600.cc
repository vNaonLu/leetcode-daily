// Copyright 2023 Naon Lu
//
// This file describes the solution of
// K Items With the Maximum Sum
//
// https://leetcode.com/problems/k-items-with-the-maximum-sum/
//
// Question ID: 2600
// Difficult  : Easy
// Solve Date : 2023/12/05 20:59

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2600. K Items With the Maximum Sum|:
//
// There is a bag that consists of items, each item has a number |1|, |0|, or
// |-1| written on it. You are given four non-negative integers |numOnes|,
// |numZeros|, |numNegOnes|, and |k|. The bag initially contains:
//
//  • |numOnes| items with |1|s written on them.
//
//  • |numZeroes| items with |0|s written on them.
//
//  • |numNegOnes| items with |-1|s written on them.
// We want to pick exactly |k| items among the available items. Return the
// maximum possible sum of numbers written on the items.
//
//

LEETCODE_BEGIN_RESOLVING(2600, KItemsWithTheMaximumSum, Solution);

class Solution {
public:
  int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
    int res = min(k, numOnes);
    k -= res;
    if (k > 0) {
      k -= min(k, numZeros);
    }
    if (k > 0) {
      res -= min(k, numNegOnes);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= numOnes, numZeros, numNegOnes <= 50|
// * |0 <= k <= numOnes + numZeros + numNegOnes|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numOnes = 3, numZeros = 2, numNegOnes = 0, k = 2
// Output: 2
//
// We have a bag of items with numbers written on them {1, 1, 1, 0, 0}. We take
// 2 items with 1 written on them and get a sum in a total of 2. It can be
// proven that 2 is the maximum possible sum.

LEETCODE_SOLUTION_UNITTEST(2600, KItemsWithTheMaximumSum, example_1) {
  auto solution   = MakeSolution();
  int  numOnes    = 3;
  int  numZeros   = 2;
  int  numNegOnes = 0;
  int  k          = 2;
  int  expect     = 2;
  int actual = solution->kItemsWithMaximumSum(numOnes, numZeros, numNegOnes, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numOnes = 3, numZeros = 2, numNegOnes = 0, k = 4
// Output: 3
//
// We have a bag of items with numbers written on them {1, 1, 1, 0, 0}. We take
// 3 items with 1 written on them, and 1 item with 0 written on it, and get a
// sum in a total of 3. It can be proven that 3 is the maximum possible sum.

LEETCODE_SOLUTION_UNITTEST(2600, KItemsWithTheMaximumSum, example_2) {
  auto solution   = MakeSolution();
  int  numOnes    = 3;
  int  numZeros   = 2;
  int  numNegOnes = 0;
  int  k          = 4;
  int  expect     = 3;
  int actual = solution->kItemsWithMaximumSum(numOnes, numZeros, numNegOnes, k);
  LCD_EXPECT_EQ(expect, actual);
}
