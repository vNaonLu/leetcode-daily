// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Indices of Stable Mountains
//
// https://leetcode.com/problems/find-indices-of-stable-mountains/
//
// Question ID: 3285
// Difficult  : Easy
// Solve Date : 2024/09/16 21:38

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3285. Find Indices of Stable Mountains|:
//
// There are |n| mountains in a row, and each mountain has a height. You are
// given an integer array |height| where |height[i]| represents the height of
// mountain |i|, and an integer |threshold|. A mountain is called stable if the
// mountain just before it (if it exists) has a height strictly greater than
// |threshold|. Note that mountain 0 is not stable. Return an array containing
// the indices of all stable mountains in any order.
//
//

LEETCODE_BEGIN_RESOLVING(3285, FindIndicesOfStableMountains, Solution);

class Solution {
public:
  vector<int> stableMountains(vector<int> &height, int threshold) {
    int         n = height.size();
    vector<int> res;
    for (int i = 0; i < n - 1; ++i) {
      if (height[i] > threshold) {
        res.emplace_back(i + 1);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n == height.length <= 100|
// * |1 <= height[i] <= 100|
// * |1 <= threshold <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: height = [1,2,3,4,5], threshold = 2
// Output: [3,4]
//

LEETCODE_SOLUTION_UNITTEST(3285, FindIndicesOfStableMountains, example_1) {
  auto        solution  = MakeSolution();
  vector<int> height    = {1, 2, 3, 4, 5};
  int         threshold = 2;
  vector<int> expect    = {3, 4};
  vector<int> actual    = solution->stableMountains(height, threshold);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: height = [10,1,10,1,10], threshold = 3
// Output: [1,3]
//

LEETCODE_SOLUTION_UNITTEST(3285, FindIndicesOfStableMountains, example_2) {
  auto        solution  = MakeSolution();
  vector<int> height    = {10, 1, 10, 1, 10};
  int         threshold = 3;
  vector<int> expect    = {1, 3};
  vector<int> actual    = solution->stableMountains(height, threshold);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: height = [10,1,10,1,10], threshold = 10
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(3285, FindIndicesOfStableMountains, example_3) {
  auto        solution  = MakeSolution();
  vector<int> height    = {10, 1, 10, 1, 10};
  int         threshold = 10;
  vector<int> expect    = {};
  vector<int> actual    = solution->stableMountains(height, threshold);
  LCD_EXPECT_EQ(expect, actual);
}
