// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Distribute Candies
//
// https://leetcode.com/problems/distribute-candies/
//
// Question ID: 575
// Difficult  : Easy
// Solve Date : 2023/07/04 20:08

#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |575. Distribute Candies|:
//
// Alice has |n| candies, where the |iᵗʰ| candy is of type |candyType[i]|. Alice
// noticed that she started to gain weight, so she visited a doctor. The doctor
// advised Alice to only eat |n / 2| of the candies she has ( |n| is always
// even). Alice likes her candies very much, and she wants to eat the maximum
// number of different types of candies while still following the doctor's
// advice. Given the integer array |candyType| of length |n|, return the maximum
// number of different types of candies she can eat if she only eats |n / 2| of
// them.
//
//

LEETCODE_BEGIN_RESOLVING(575, DistributeCandies, Solution);

class Solution {
public:
  int distributeCandies(vector<int> &candyType) {
    unordered_set<int> st(candyType.begin(), candyType.end());
    return min(st.size(), candyType.size() / 2);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == candyType.length|
// * |2 <= n <= 10⁴|
// * |n| is even.
// * |-10⁵ <= candyType[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: candyType = [1,1,2,2,3,3]
// Output: 3
//
// Alice can only eat 6 / 2 = 3 candies. Since there are only 3 types, she can
// eat one of each type.

LEETCODE_SOLUTION_UNITTEST(575, DistributeCandies, example_1) {
  auto        solution  = MakeSolution();
  vector<int> candyType = {1, 1, 2, 2, 3, 3};
  int         expect    = 3;
  int         actual    = solution->distributeCandies(candyType);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: candyType = [1,1,2,3]
// Output: 2
//
// Alice can only eat 4 / 2 = 2 candies. Whether she eats types [1,2], [1,3], or
// [2,3], she still can only eat 2 different types.

LEETCODE_SOLUTION_UNITTEST(575, DistributeCandies, example_2) {
  auto        solution  = MakeSolution();
  vector<int> candyType = {1, 1, 2, 3};
  int         expect    = 2;
  int         actual    = solution->distributeCandies(candyType);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: candyType = [6,6,6,6]
// Output: 1
//
// Alice can only eat 4 / 2 = 2 candies. Even though she can eat 2 candies, she
// only has 1 type.

LEETCODE_SOLUTION_UNITTEST(575, DistributeCandies, example_3) {
  auto        solution  = MakeSolution();
  vector<int> candyType = {6, 6, 6, 6};
  int         expect    = 1;
  int         actual    = solution->distributeCandies(candyType);
  LCD_EXPECT_EQ(expect, actual);
}
