// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Good Triplets in an Array
//
// https://leetcode.com/problems/count-good-triplets-in-an-array/
//
// Question ID: 2179
// Difficult  : Hard
// Solve Date : 2025/04/15 19:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2179. Count Good Triplets in an Array|:
//
// You are given two 0-indexed arrays |nums1| and |nums2| of length |n|, both of
// which are permutations of |[0, 1, ..., n - 1]|. A good triplet is a set of
// |3| distinct values which are present in increasing order by position both in
// |nums1| and |nums2|. In other words, if we consider |pos1ᵥ| as the index of
// the value |v| in |nums1| and |pos2ᵥ| as the index of the value |v| in
// |nums2|, then a good triplet will be a set |(x, y, z)| where |0 <= x, y, z <=
// n - 1|, such that |pos1ₓ < pos1_{y} < pos1_{z}| and |pos2ₓ < pos2_{y} <
// pos2_{z}|. Return the total number of good triplets.
//
//

LEETCODE_BEGIN_RESOLVING(2179, CountGoodTripletsInAnArray, Solution);

class Solution {
public:
  long long goodTriplets(vector<int> &nums1, vector<int> &nums2) {
    int         n = nums1.size();
    vector<int> position(n, 0), reindex(n, 0);
    for (int i = 0; i < n; i++) {
      position[nums2[i]] = i;
    }
    for (int i = 0; i < n; i++) {
      reindex[i] = position[nums1[i]];
    }
    vector<int> fen_small(n + 1, 0), fen_big(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      update(i, 1, fen_big); // initially all are bigger
    }
    long long result = 0;
    for (int i = 0; i < n; i++) {
      update(reindex[i] + 1, -1, fen_big);
      update(reindex[i] + 1, +1, fen_small);

      int smaller = query(reindex[i], fen_small);
      int bigger  = query(n, fen_big) - query(reindex[i], fen_big);

      result += (long long)smaller *
                bigger; // how many times it contributes to the result,
                        // positions beeing chosen as middle.
    }
    return result;
  }
  void update(int index, int val, vector<int> &fen) {
    int n = fen.size();
    while (index < n) {
      fen[index] += val;
      index += (index & -index);
    }
  }
  int query(int index, vector<int> &fen) {
    int res = 0;
    while (index > 0) {
      res += fen[index];
      index -= (index & -index);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums1.length == nums2.length|
// * |3 <= n <= 10⁵|
// * |0 <= nums1[i], nums2[i] <= n - 1|
// * |nums1| and |nums2| are permutations of |[0, 1, ..., n - 1]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2179, CountGoodTripletsInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 0, 1, 3};
  vector<int> nums2    = {0, 1, 2, 3};
  long long   expect   = 1;
  long long   actual   = solution->goodTriplets(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2179, CountGoodTripletsInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {4, 0, 1, 3, 2};
  vector<int> nums2    = {4, 1, 0, 2, 3};
  long long   expect   = 4;
  long long   actual   = solution->goodTriplets(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}
