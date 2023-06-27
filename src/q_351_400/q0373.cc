// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find K Pairs with Smallest Sums
//
// https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
//
// Question ID: 373
// Difficult  : Medium
// Solve Date : 2023/06/27 20:42

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |373. Find K Pairs with Smallest Sums|:
//
// You are given two integer arrays |nums1| and |nums2| sorted in ascending
// order and an integer |k|. Define a pair |(u, v)| which consists of one
// element from the first array and one element from the second array. Return
// the |k| pairs |(u₁, v₁), (u₂, v₂), ..., (uₖ, vₖ)| with the smallest sums.
//
//

LEETCODE_BEGIN_RESOLVING(373, FindKPairsWithSmallestSums, Solution);

class Solution {
public:
  vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2,
                                     int k) {
    vector<vector<int>>                       res;
    priority_queue<pair<int, pair<int, int>>> pq;
    for (auto n1 : nums1) {
      for (auto n2 : nums2) {
        if (pq.size() < k) {
          pq.emplace(n1 + n2, make_pair(n1, n2));
        } else if (pq.top().first > n1 + n2) {
          pq.pop();
          pq.emplace(n1 + n2, make_pair(n1, n2));
        } else {
          break;
        }
      }
    }
    while (!pq.empty()) {
      res.emplace_back(
          vector<int>{pq.top().second.first, pq.top().second.second});
      pq.pop();
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 10⁵|
// * |-10⁹ <= nums1[i], nums2[i] <= 10⁹|
// * |nums1| and |nums2| both are sorted in ascending order.
// * |1 <= k <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
// Output: [[1,2],[1,4],[1,6]]
//
// The first 3 pairs are returned from the sequence:
// [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

LEETCODE_SOLUTION_UNITTEST(373, FindKPairsWithSmallestSums, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums1    = {1, 7, 11};
  vector<int>         nums2    = {2, 4, 6};
  int                 k        = 3;
  vector<vector<int>> expect   = {
      {1, 2},
      {1, 4},
      {1, 6}
  };
  vector<vector<int>> actual = solution->kSmallestPairs(nums1, nums2, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
// Output: [[1,1],[1,1]]
//
// The first 2 pairs are returned from the sequence:
// [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

LEETCODE_SOLUTION_UNITTEST(373, FindKPairsWithSmallestSums, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums1    = {1, 1, 2};
  vector<int>         nums2    = {1, 2, 3};
  int                 k        = 2;
  vector<vector<int>> expect   = {
      {1, 1},
      {1, 1}
  };
  vector<vector<int>> actual = solution->kSmallestPairs(nums1, nums2, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: nums1 = [1,2], nums2 = [3], k = 3
// Output: [[1,3],[2,3]]
//
// All possible pairs are returned from the sequence: [1,3],[2,3]

LEETCODE_SOLUTION_UNITTEST(373, FindKPairsWithSmallestSums, example_3) {
  auto                solution = MakeSolution();
  vector<int>         nums1    = {1, 2};
  vector<int>         nums2    = {3};
  int                 k        = 3;
  vector<vector<int>> expect   = {
      {1, 3},
      {2, 3}
  };
  vector<vector<int>> actual = solution->kSmallestPairs(nums1, nums2, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}
