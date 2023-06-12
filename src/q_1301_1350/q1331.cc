// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rank Transform of an Array
//
// https://leetcode.com/problems/rank-transform-of-an-array/
//
// Question ID: 1331
// Difficult  : Easy
// Solve Date : 2023/06/09 11:35

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1331. Rank Transform of an Array|:
//
// Given an array of integers |arr|, replace each element with its rank.
// The rank represents how large the element is. The rank has the following
// rules:
//
//  • Rank is an integer starting from 1.
//
//  • The larger the element, the larger the rank. If two elements are equal,
//  their rank must be the same.
//
//  • Rank should be as small as possible.
//
//

LEETCODE_BEGIN_RESOLVING(1331, RankTransformOfAnArray, Solution);

class Solution {
public:
  vector<int> arrayRankTransform(vector<int> &arr) {
    map<int, vector<int>> memo;
    vector<int>           res(arr.size(), -1);
    for (int i = 0; i < arr.size(); ++i) {
      memo[arr[i]].emplace_back(i);
    }
    int rank = 1;
    for (auto &it : memo) {
      for (auto idx : it.second) {
        res[idx] = rank;
      }
      ++rank;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= arr.length <= 10⁵|
// * |-10⁹ <= arr[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [40,10,20,30]
// Output: [4,1,2,3]
//
// : 40 is the largest element. 10 is the smallest. 20 is the second smallest.
// 30 is the third smallest.

LEETCODE_SOLUTION_UNITTEST(1331, RankTransformOfAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {40, 10, 20, 30};
  vector<int> expect   = {4, 1, 2, 3};
  vector<int> actual   = solution->arrayRankTransform(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [100,100,100]
// Output: [1,1,1]
//
// : Same elements share the same rank.

LEETCODE_SOLUTION_UNITTEST(1331, RankTransformOfAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {100, 100, 100};
  vector<int> expect   = {1, 1, 1};
  vector<int> actual   = solution->arrayRankTransform(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [37,12,28,9,100,56,80,5,12]
// Output: [5,3,4,2,8,6,7,1,3]
//

LEETCODE_SOLUTION_UNITTEST(1331, RankTransformOfAnArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {37, 12, 28, 9, 100, 56, 80, 5, 12};
  vector<int> expect   = {5, 3, 4, 2, 8, 6, 7, 1, 3};
  vector<int> actual   = solution->arrayRankTransform(arr);
  LCD_EXPECT_EQ(expect, actual);
}
