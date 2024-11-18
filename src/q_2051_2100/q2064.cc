// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimized Maximum of Products Distributed to Any Store
//
// https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/
//
// Question ID: 2064
// Difficult  : Medium
// Solve Date : 2024/11/14 19:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2064. Minimized Maximum of Products Distributed to Any
// Store|:
//
// You are given an integer |n| indicating there are |n| specialty retail
// stores. There are |m| product types of varying amounts, which are given as a
// 0-indexed integer array |quantities|, where |quantities[i]| represents the
// number of products of the |iᵗʰ| product type. You need to distribute all
// products to the retail stores following these rules:
//
//  • A store can only be given at most one product type but can be given any
//  amount of it.
//
//  • After distribution, each store will have been given some number of
//  products (possibly |0|). Let |x| represent the maximum number of products
//  given to any store. You want |x| to be as small as possible, i.e., you want
//  to minimize the maximum number of products that are given to any store.
// Return the minimum possible |x|.
//
//

LEETCODE_BEGIN_RESOLVING(2064, MinimizedMaximumOfProductsDistributedToAnyStore,
                         Solution);

class Solution {
public:
  int minimizedMaximum(int n, vector<int> &quantities) {
    int s   = 1;
    int e   = 100000;
    int res = -1;
    while (s <= e) {
      int m = s + (e - s) / 2;
      if (isPossible(n, quantities, m)) {
        res = m;
        e   = m - 1;
      } else {
        s = m + 1;
      }
    }
    return res;
  }

private:
  bool isPossible(int n, vector<int> const &q, int mid) {
    int stores = 0;
    for (auto x : q) {
      stores += x / mid;
      if (x % mid) {
        ++stores;
      }
      if (stores > n) {
        return false;
      }
    }
    return stores <= n;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == quantities.length|
// * |1 <= m <= n <= 10⁵|
// * |1 <= quantities[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, quantities = [11,6]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2064,
                           MinimizedMaximumOfProductsDistributedToAnyStore,
                           example_1) {
  auto        solution   = MakeSolution();
  int         n          = 6;
  vector<int> quantities = {11, 6};
  int         expect     = 3;
  int         actual     = solution->minimizedMaximum(n, quantities);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7, quantities = [15,10,10]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2064,
                           MinimizedMaximumOfProductsDistributedToAnyStore,
                           example_2) {
  auto        solution   = MakeSolution();
  int         n          = 7;
  vector<int> quantities = {15, 10, 10};
  int         expect     = 5;
  int         actual     = solution->minimizedMaximum(n, quantities);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 1, quantities = [100000]
// Output: 100000
//

LEETCODE_SOLUTION_UNITTEST(2064,
                           MinimizedMaximumOfProductsDistributedToAnyStore,
                           example_3) {
  auto        solution   = MakeSolution();
  int         n          = 1;
  vector<int> quantities = {100000};
  int         expect     = 100000;
  int         actual     = solution->minimizedMaximum(n, quantities);
  LCD_EXPECT_EQ(expect, actual);
}
