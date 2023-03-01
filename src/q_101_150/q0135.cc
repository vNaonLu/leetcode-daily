// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Candy
//
// https://leetcode.com/problems/candy/
//
// Question ID: 135
// Difficult  : Hard
// Solve Date : 2022/07/04 18:16

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |135. Candy|:
//
// There are |n| children standing in a line. Each child is assigned a rating
// value given in the integer array |ratings|. You are giving candies to these
// children subjected to the following requirements:
//
//  • Each child must have at least one candy.
//
//  • Children with a higher rating get more candies than their neighbors.
// Return the minimum number of candies you need to have to distribute the
// candies to the children.
//

LEETCODE_BEGIN_RESOLVING(135, Candy, Solution);

class Solution {
public:
  int candy(vector<int> &ratings) {
    vector<int> candies(ratings.size(), 1);
    for (int i = 1; i < ratings.size(); ++i) {
      if (ratings[i] > ratings[i - 1]) {
        candies[i] = candies[i - 1] + 1;
      }
    }
    for (int i = ratings.size() - 2; i >= 0; --i) {
      if (ratings[i] > ratings[i + 1]) {
        candies[i] = max(candies[i], candies[i + 1] + 1);
      }
    }

    return accumulate(candies.begin(), candies.end(), 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == ratings.length|
// * |1 <= n <= 2 * 10⁴|
// * |0 <= ratings[i] <= 2 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ratings = [1,0,2]
// Output: 5
//
// You can allocate to the first, second and third child with 2, 1, 2 candies
// respectively.

LEETCODE_SOLUTION_UNITTEST(135, Candy, example_1) {
  auto        solution = MakeSolution();
  vector<int> ratings  = {1, 0, 2};
  int         expect   = 5;
  int         actual   = solution->candy(ratings);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ratings = [1,2,2]
// Output: 4
//
// You can allocate to the first, second and third child with 1, 2, 1 candies
// respectively. The third child gets 1 candy because it satisfies the above two
// conditions.

LEETCODE_SOLUTION_UNITTEST(135, Candy, example_2) {
  auto        solution = MakeSolution();
  vector<int> ratings  = {1, 2, 2};
  int         expect   = 4;
  int         actual   = solution->candy(ratings);
  LCD_EXPECT_EQ(expect, actual);
}
