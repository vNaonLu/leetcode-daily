// Copyright 2024 Naon Lu
//
// This file describes the solution of
// XOR Queries of a Subarray
//
// https://leetcode.com/problems/xor-queries-of-a-subarray/
//
// Question ID: 1310
// Difficult  : Medium
// Solve Date : 2024/09/13 23:23

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1310. XOR Queries of a Subarray|:
//
// You are given an array |arr| of positive integers. You are also given the
// array |queries| where |queries[i] = [left_{i, }rightᵢ]|. For each query |i|
// compute the XOR of elements from |leftᵢ| to |rightᵢ| (that is, |arr[leftᵢ]
// XOR arr[leftᵢ + 1] XOR ... XOR arr[rightᵢ]| ). Return an array |answer| where
// |answer[i]| is the answer to the |iᵗʰ| query.
//
//

LEETCODE_BEGIN_RESOLVING(1310, XORQueriesOfASubarray, Solution);

class Solution {
public:
  vector<int> xorQueries(vector<int> &arr, vector<vector<int>> &queries) {
    partial_sum(arr.begin(), arr.end(), arr.begin(), bit_xor<int>());

    vector<int> res;
    for (auto &v : queries) {
      int q0 = v[0];
      int q1 = v[1];
      res.emplace_back((q0 == 0) ? arr[q1] : (arr[q1] ^ arr[q0 - 1]));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr.length, queries.length <= 3 * 10⁴|
// * |1 <= arr[i] <= 10⁹|
// * |queries[i].length == 2|
// * |0 <= leftᵢ <= rightᵢ < arr.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
// Output: [2,7,14,8]
//

LEETCODE_SOLUTION_UNITTEST(1310, XORQueriesOfASubarray, example_1) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {1, 3, 4, 8};
  vector<vector<int>> queries  = {
      {0, 1},
      {1, 2},
      {0, 3},
      {3, 3}
  };
  vector<int> expect = {2, 7, 14, 8};
  vector<int> actual = solution->xorQueries(arr, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
// Output: [8,0,4,4]
//

LEETCODE_SOLUTION_UNITTEST(1310, XORQueriesOfASubarray, example_2) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {4, 8, 2, 10};
  vector<vector<int>> queries  = {
      {2, 3},
      {1, 3},
      {0, 0},
      {0, 3}
  };
  vector<int> expect = {8, 0, 4, 4};
  vector<int> actual = solution->xorQueries(arr, queries);
  LCD_EXPECT_EQ(expect, actual);
}
