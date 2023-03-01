// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Fruit Into Baskets
//
// https://leetcode.com/problems/fruit-into-baskets/
//
// Question ID: 904
// Difficult  : Medium
// Solve Date : 2023/02/07 21:56

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |904. Fruit Into Baskets|:
//
// You are visiting a farm that has a single row of fruit trees arranged from
// left to right. The trees are represented by an integer array |fruits| where
// |fruits[i]| is the type of fruit the |iᵗʰ| tree produces. You want to collect
// as much fruit as possible. However, the owner has some strict rules that you
// must follow:
//
//  • You only have two baskets, and each basket can only hold a single type of
//  fruit. There is no limit on the amount of fruit each basket can hold.
//
//  • Starting from any tree of your choice, you must pick exactly one fruit
//  from every tree (including the start tree) while moving to the right. The
//  picked fruits must fit in one of your baskets.
//
//  • Once you reach a tree with fruit that cannot fit in your baskets, you must
//  stop.
// Given the integer array |fruits|, return the maximum number of fruits you can
// pick.
//

LEETCODE_BEGIN_RESOLVING(904, FruitIntoBaskets, Solution);

class Solution {
public:
  int totalFruit(vector<int> &fruits) {
    int           cnt = 0;
    int           res = 0;
    map<int, int> memo;
    auto          beg = fruits.begin();
    auto          it  = beg;
    while (it != fruits.end()) {
      ++memo[*it];
      ++cnt;
      while (memo.size() > 2) {
        auto left = beg++;
        --memo[*left];
        --cnt;
        if (memo[*left] == 0) {
          memo.erase(*left);
        }
      }
      res = max(res, cnt);
      ++it;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= fruits.length <= 10⁵|
// * |0 <= fruits[i] < fruits.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: fruits = [1,2,1]
// Output: 3
//
// We can pick from all 3 trees.

LEETCODE_SOLUTION_UNITTEST(904, FruitIntoBaskets, example_1) {
  auto        solution = MakeSolution();
  vector<int> fruits   = {1, 2, 1};
  int         expect   = 3;
  int         actual   = solution->totalFruit(fruits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: fruits = [0,1,2,2]
// Output: 3
//
// We can pick from trees [1,2,2].
// If we had started at the first tree, we would only pick from trees [0,1].

LEETCODE_SOLUTION_UNITTEST(904, FruitIntoBaskets, example_2) {
  auto        solution = MakeSolution();
  vector<int> fruits   = {0, 1, 2, 2};
  int         expect   = 3;
  int         actual   = solution->totalFruit(fruits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: fruits = [1,2,3,2,2]
// Output: 4
//
// We can pick from trees [2,3,2,2].
// If we had started at the first tree, we would only pick from trees [1,2].

LEETCODE_SOLUTION_UNITTEST(904, FruitIntoBaskets, example_3) {
  auto        solution = MakeSolution();
  vector<int> fruits   = {1, 2, 3, 2, 2};
  int         expect   = 4;
  int         actual   = solution->totalFruit(fruits);
  LCD_EXPECT_EQ(expect, actual);
}
