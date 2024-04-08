// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Circular Array Loop
//
// https://leetcode.com/problems/circular-array-loop/
//
// Question ID: 457
// Difficult  : Medium
// Solve Date : 2024/04/05 15:32

#include <iosfwd>
#include <optional>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |457. Circular Array Loop|:
//
// You are playing a game involving a circular array of non-zero integers
// |nums|. Each |nums[i]| denotes the number of indices forward/backward you
// must move if you are located at index |i|:
//
//  • If |nums[i]| is positive, move |nums[i]| steps forward, and
//
//  • If |nums[i]| is negative, move |nums[i]| steps backward.
// Since the array is circular, you may assume that moving forward from the last
// element puts you on the first element, and moving backwards from the first
// element puts you on the last element. A cycle in the array consists of a
// sequence of indices |seq| of length |k| where:
//
//  • Following the movement rules above results in the repeating index sequence
//  |seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...|
//
//  • Every |nums[seq[j]]| is either all positive or all negative.
//
//  • |k > 1|
// Return |true| if there is a cycle in |nums|, or |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(457, CircularArrayLoop, Solution);

class Solution {
public:
  bool circularArrayLoop(vector<int> &nums) {
    vector<optional<bool>> isloop(nums.size(), nullopt);
    for (int i = 0; i < nums.size(); ++i) {
      if (checkLoop(nums, &isloop, i)) {
        return true;
      }
    }
    return false;
  }

private:
  bool checkLoop(vector<int> const &v, vector<optional<bool>> *isloop,
                 int cur) {
    if (!(*isloop)[cur]) {
      (*isloop)[cur] = true;
      int nxt        = next(v, cur);
      if (cur == nxt || v[cur] * v[nxt] < 0) {
        // self loop or different direction.
        (*isloop)[cur] = false;
      } else {
        (*isloop)[cur] = checkLoop(v, isloop, nxt);
      }
    }
    return *(*isloop)[cur];
  }

  int next(vector<int> const &v, int x) {
    return ((x + v[x] + v.size()) % v.size());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5000|
// * |-1000 <= nums[i] <= 1000|
// * |nums[i] != 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,-1,1,2,2]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(457, CircularArrayLoop, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, -1, 1, 2, 2};
  bool        expect   = true;
  bool        actual   = solution->circularArrayLoop(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,-2,-3,-4,-5,6]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(457, CircularArrayLoop, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -2, -3, -4, -5, 6};
  bool        expect   = false;
  bool        actual   = solution->circularArrayLoop(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,-1,5,1,4]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(457, CircularArrayLoop, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -1, 5, 1, 4};
  bool        expect   = true;
  bool        actual   = solution->circularArrayLoop(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [-2,1,-1,-2,-2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(457, CircularArrayLoop, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-2, 1, -1, -2, -2};
  bool        expect   = false;
  bool        actual   = solution->circularArrayLoop(nums);
  LCD_EXPECT_EQ(expect, actual);
}
