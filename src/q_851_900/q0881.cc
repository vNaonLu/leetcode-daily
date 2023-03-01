// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Boats to Save People
//
// https://leetcode.com/problems/boats-to-save-people/
//
// Question ID: 881
// Difficult  : Medium
// Solve Date : 2022/03/24 18:23

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |881. Boats to Save People|:
//
// You are given an array |people| where |people[i]| is the weight of the |iᵗʰ|
// person, and an infinite number of boats where each boat can carry a maximum
// weight of |limit|. Each boat carries at most two people at the same time,
// provided the sum of the weight of those people is at most |limit|. Return the
// minimum number of boats to carry every given person.  
//

LEETCODE_BEGIN_RESOLVING(881, BoatsToSavePeople, Solution);

class Solution {
public:
  int numRescueBoats(vector<int> &people, int limit) {
    sort(people.begin(), people.end());
    int left = 0, right = people.size() - 1;
    int res = 0;
    while (left <= right) {
      int curr = people[right--];

      if (right >= 0 && curr <= limit - people[right]) {
        curr += people[right--];
      } else if (left <= right && curr <= limit - people[left]) {
        curr += people[left++];
      }

      ++res;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= people.length <= 5 * 10⁴|
// * |1 <= people[i] <= limit <= 3 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: people = [1,2], limit = 3
// Output: 1
//
// 1 boat (1, 2)

LEETCODE_SOLUTION_UNITTEST(881, BoatsToSavePeople, example_1) {
  auto        solution = MakeSolution();
  vector<int> people   = {1, 2};
  int         limit    = 3;
  int         expect   = 1;
  int         actual   = solution->numRescueBoats(people, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: people = [3,2,2,1], limit = 3
// Output: 3
//
// 3 boats (1, 2), (2) and (3)

LEETCODE_SOLUTION_UNITTEST(881, BoatsToSavePeople, example_2) {
  auto        solution = MakeSolution();
  vector<int> people   = {3, 2, 2, 1};
  int         limit    = 3;
  int         expect   = 3;
  int         actual   = solution->numRescueBoats(people, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: people = [3,5,3,4], limit = 5
// Output: 4
//
// 4 boats (3), (3), (4), (5)

LEETCODE_SOLUTION_UNITTEST(881, BoatsToSavePeople, example_3) {
  auto        solution = MakeSolution();
  vector<int> people   = {3, 5, 3, 4};
  int         limit    = 5;
  int         expect   = 4;
  int         actual   = solution->numRescueBoats(people, limit);
  LCD_EXPECT_EQ(expect, actual);
}
