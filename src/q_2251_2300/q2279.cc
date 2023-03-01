// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Bags With Full Capacity of Rocks
//
// https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/
//
// Question ID: 2279
// Difficult  : Medium
// Solve Date : 2022/12/27 20:59

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2279. Maximum Bags With Full Capacity of Rocks|:
//
// You have |n| bags numbered from |0| to |n - 1|. You are given two 0-indexed
// integer arrays |capacity| and |rocks|. The |iᵗʰ| bag can hold a maximum of
// |capacity[i]| rocks and currently contains |rocks[i]| rocks. You are also
// given an integer |additionalRocks|, the number of additional rocks you can
// place in any of the bags. Return the maximum number of bags that could have
// full capacity after placing the additional rocks in some bags.
//

LEETCODE_BEGIN_RESOLVING(2279, MaximumBagsWithFullCapacityOfRocks, Solution);

class Solution {
public:
  int maximumBags(vector<int> &capacity, vector<int> &rocks,
                  int additionalRocks) {
    auto left = priority_queue<int, vector<int>, greater<int>>();
    auto res  = (int)0;
    for (int i = 0; i < capacity.size(); ++i) {
      auto cnt = max(0, capacity[i] - rocks[i]);
      if (cnt > 0) {
        left.emplace(cnt);
      } else {
        ++res;
      }
    }
    while (!left.empty() && left.top() <= additionalRocks) {
      ++res;
      additionalRocks -= left.top();
      left.pop();
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == capacity.length == rocks.length|
// * |1 <= n <= 5 * 10⁴|
// * |1 <= capacity[i] <= 10⁹|
// * |0 <= rocks[i] <= capacity[i]|
// * |1 <= additionalRocks <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
// Output: 3
//
// Place 1 rock in bag 0 and 1 rock in bag 1.
// The number of rocks in each bag are now [2,3,4,4].
// Bags 0, 1, and 2 have full capacity.
// There are 3 bags at full capacity, so we return 3.
// It can be shown that it is not possible to have more than 3 bags at full
// capacity. Note that there may be other ways of placing the rocks that result
// in an answer of 3.

LEETCODE_SOLUTION_UNITTEST(2279, MaximumBagsWithFullCapacityOfRocks,
                           example_1) {
  auto        solution        = MakeSolution();
  vector<int> capacity        = {2, 3, 4, 5};
  vector<int> rocks           = {1, 2, 4, 4};
  int         additionalRocks = 2;
  int         expect          = 3;
  int         actual = solution->maximumBags(capacity, rocks, additionalRocks);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: capacity = [10,2,2], rocks = [2,2,0], additionalRocks = 100
// Output: 3
//
// Place 8 rocks in bag 0 and 2 rocks in bag 2.
// The number of rocks in each bag are now [10,2,2].
// Bags 0, 1, and 2 have full capacity.
// There are 3 bags at full capacity, so we return 3.
// It can be shown that it is not possible to have more than 3 bags at full
// capacity. Note that we did not use all of the additional rocks.

LEETCODE_SOLUTION_UNITTEST(2279, MaximumBagsWithFullCapacityOfRocks,
                           example_2) {
  auto        solution        = MakeSolution();
  vector<int> capacity        = {10, 2, 2};
  vector<int> rocks           = {2, 2, 0};
  int         additionalRocks = 100;
  int         expect          = 3;
  int         actual = solution->maximumBags(capacity, rocks, additionalRocks);
  LCD_EXPECT_EQ(expect, actual);
}
