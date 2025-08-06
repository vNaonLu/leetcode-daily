// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Fruits Into Baskets III
//
// https://leetcode.com/problems/fruits-into-baskets-iii/
//
// Question ID: 3479
// Difficult  : Medium
// Solve Date : 2025/08/06 21:08

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3479. Fruits Into Baskets III|:
//
// You are given two arrays of integers, |fruits| and |baskets|, each of length
// |n|, where |fruits[i]| represents the quantity of the |iᵗʰ| type of fruit,
// and |baskets[j]| represents the capacity of the |jᵗʰ| basket. From left to
// right, place the fruits according to these rules:
//
//  • Each fruit type must be placed in the leftmost available basket with a
//  capacity greater than or equal to the quantity of that fruit type.
//
//  • Each basket can hold only one type of fruit.
//
//  • If a fruit type cannot be placed in any basket, it remains unplaced.
// Return the number of fruit types that remain unplaced after all possible
// allocations are made.
//
//

LEETCODE_BEGIN_RESOLVING(3479, FruitsIntoBasketsIII, Solution);

class Solution {
public:
  int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets) {
    int         n    = fruits.size();
    int         root = floor(sqrt(n));
    vector<int> v(root + 2, 0);
    for (int i = 0; i < n; ++i) {
      v[i / root] = max(v[i / root], baskets[i]);
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
      int ind = -1;
      for (int j = 0; j < root + 2; ++j) {
        if (v[j] >= fruits[i]) {
          ind = j;
          break;
        }
      }
      if (ind == -1) {
        ++res;
        continue;
      }
      for (int j = root * ind; j < root * (ind + 1); ++j) {
        if (baskets[j] >= fruits[i]) {
          baskets[j] = 0;
          break;
        }
      }
      v[ind] = 0;
      for (int j = root * ind; j < min((ind + 1) * root, n); ++j) {
        v[ind] = max(v[ind], baskets[j]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == fruits.length == baskets.length|
// * |1 <= n <= 10⁵|
// * |1 <= fruits[i], baskets[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: fruits = [4,2,5], baskets = [3,5,4]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3479, FruitsIntoBasketsIII, example_1) {
  auto        solution = MakeSolution();
  vector<int> fruits   = {4, 2, 5};
  vector<int> baskets  = {3, 5, 4};
  int         expect   = 1;
  int         actual   = solution->numOfUnplacedFruits(fruits, baskets);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: fruits = [3,6,1], baskets = [6,4,7]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3479, FruitsIntoBasketsIII, example_2) {
  auto        solution = MakeSolution();
  vector<int> fruits   = {3, 6, 1};
  vector<int> baskets  = {6, 4, 7};
  int         expect   = 0;
  int         actual   = solution->numOfUnplacedFruits(fruits, baskets);
  LCD_EXPECT_EQ(expect, actual);
}
