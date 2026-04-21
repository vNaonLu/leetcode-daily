// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimize Hamming Distance After Swap Operations
//
// https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/
//
// Question ID: 1722
// Difficult  : Medium
// Solve Date : 2026/04/21 16:44

#include <iosfwd>
#include <numeric>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1722. Minimize Hamming Distance After Swap Operations|:
//
// You are given two integer arrays, |source| and |target|, both of length |n|.
// You are also given an array |allowedSwaps| where each |allowedSwaps[i] = [aᵢ,
// bᵢ]| indicates that you are allowed to swap the elements at index |aᵢ| and
// index |bᵢ| (0-indexed) of array |source|. Note that you can swap elements at
// a specific pair of indices multiple times and in any order. The Hamming
// distance of two arrays of the same length, |source| and |target|, is the
// number of positions where the elements are different. Formally, it is the
// number of indices |i| for |0 <= i <= n-1| where |source[i] != target[i]|
// (0-indexed). Return the minimum Hamming distance of |source| and |target|
// after performing any amount of swap operations on array |source|.
//
//

LEETCODE_BEGIN_RESOLVING(1722, MinimizeHammingDistanceAfterSwapOperations,
                         Solution);

class Solution {
public:
  vector<int> parent;

  int find(int x) {
    if (parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  }

  void unite(int a, int b) { parent[find(a)] = find(b); }

  int minimumHammingDistance(vector<int> &source, vector<int> &target,
                             vector<vector<int>> &allowedSwaps) {
    int n = source.size();
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);

    for (auto &swap : allowedSwaps) {
      unite(swap[0], swap[1]);
    }

    // Group source values by their component root
    unordered_map<int, unordered_map<int, int>> groups;
    for (int i = 0; i < n; i++) {
      groups[find(i)][source[i]]++;
    }

    int hammingDist = 0;
    for (int i = 0; i < n; i++) {
      int   root = find(i);
      auto &freq = groups[root];
      if (freq.count(target[i]) && freq[target[i]] > 0) {
        freq[target[i]]--; // matched, consume this source value
      } else {
        hammingDist++; // no match found in this component
      }
    }

    return hammingDist;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == source.length == target.length|
// * |1 <= n <= 10⁵|
// * |1 <= source[i], target[i] <= 10⁵|
// * |0 <= allowedSwaps.length <= 10⁵|
// * |allowedSwaps[i].length == 2|
// * |0 <= aᵢ, bᵢ <= n - 1|
// * |aᵢ != bᵢ|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1722, MinimizeHammingDistanceAfterSwapOperations,
                           example_1) {
  auto                solution     = MakeSolution();
  vector<int>         source       = {1, 2, 3, 4};
  vector<int>         target       = {2, 1, 4, 5};
  vector<vector<int>> allowedSwaps = {
      {0, 1},
      {2, 3}
  };
  int expect = 1;
  int actual = solution->minimumHammingDistance(source, target, allowedSwaps);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1722, MinimizeHammingDistanceAfterSwapOperations,
                           example_2) {
  auto                solution     = MakeSolution();
  vector<int>         source       = {1, 2, 3, 4};
  vector<int>         target       = {1, 3, 2, 4};
  vector<vector<int>> allowedSwaps = {};
  int                 expect       = 2;
  int actual = solution->minimumHammingDistance(source, target, allowedSwaps);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps =
//  [[0,4],[4,2],[1,3],[1,4]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1722, MinimizeHammingDistanceAfterSwapOperations,
                           example_3) {
  auto                solution     = MakeSolution();
  vector<int>         source       = {5, 1, 2, 4, 3};
  vector<int>         target       = {1, 5, 4, 2, 3};
  vector<vector<int>> allowedSwaps = {
      {0, 4},
      {4, 2},
      {1, 3},
      {1, 4}
  };
  int expect = 0;
  int actual = solution->minimumHammingDistance(source, target, allowedSwaps);
  LCD_EXPECT_EQ(expect, actual);
}
