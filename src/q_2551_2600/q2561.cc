// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Rearranging Fruits
//
// https://leetcode.com/problems/rearranging-fruits/
//
// Question ID: 2561
// Difficult  : Hard
// Solve Date : 2025/08/02 14:53

#include <algorithm>
#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2561. Rearranging Fruits|:
//
// You have two fruit baskets containing |n| fruits each. You are given two
// 0-indexed integer arrays |basket1| and |basket2| representing the cost of
// fruit in each basket. You want to make both baskets equal. To do so, you can
// use the following operation as many times as you want:
//
//  • Chose two indices |i| and |j|, and swap the |ith |fruit of |basket1| with
//  the |jth| fruit of |basket2|.
//
//  • The cost of the swap is |min(basket1[i],basket2[j])|.
// Two baskets are considered equal if sorting them according to the fruit cost
// makes them exactly the same baskets. Return the minimum cost to make both the
// baskets equal or |-1| if impossible.
//
//

LEETCODE_BEGIN_RESOLVING(2561, RearrangingFruits, Solution);

class Solution {
public:
  long long minCost(vector<int> &basket1, vector<int> &basket2) {
    unordered_map<int, int> mpp;
    for (int b : basket1) {
      mpp[b]++;
    }
    for (int b : basket2) {
      mpp[b]--;
    }

    int         mn = numeric_limits<int>::max();
    vector<int> temp;

    for (auto &[u, v] : mpp) {
      if (v % 2 == 1) {
        return -1;
      }
      for (int i = 0; i < abs(v) / 2; i++) {
        temp.push_back(u);
      }
      mn = min(mn, u);
    }
    sort(temp.begin(), temp.end());
    int64_t ans = 0;

    for (int i = 0; i < temp.size() / 2; i++) {
      ans += min(temp[i], 2 * mn);
    }

    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |basket1.length == basket2.length|
// * |1 <= basket1.length <= 10⁵|
// * |1 <= basket1[i],basket2[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2561, RearrangingFruits, example_1) {
  auto        solution = MakeSolution();
  vector<int> basket1  = {4, 2, 2, 2};
  vector<int> basket2  = {1, 4, 1, 2};
  long long   expect   = 1;
  long long   actual   = solution->minCost(basket1, basket2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2561, RearrangingFruits, example_2) {
  auto        solution = MakeSolution();
  vector<int> basket1  = {2, 3, 4, 1};
  vector<int> basket2  = {3, 2, 5, 1};
  long long   expect   = -1;
  long long   actual   = solution->minCost(basket1, basket2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [4,4,4,4,3]
// [5,5,5,5,3]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(2561, RearrangingFruits, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> basket1  = {4, 4, 4, 4, 3};
  vector<int> basket2  = {5, 5, 5, 5, 3};
  long long   expect   = 8;
  long long   actual   = solution->minCost(basket1, basket2);
  LCD_EXPECT_EQ(expect, actual);
}
