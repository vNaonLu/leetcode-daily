// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Greatest Common Divisor Traversal
//
// https://leetcode.com/problems/greatest-common-divisor-traversal/
//
// Question ID: 2709
// Difficult  : Hard
// Solve Date : 2024/02/25 14:59

#include <algorithm>
#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2709. Greatest Common Divisor Traversal|:
//
// You are given a 0-indexed integer array |nums|, and you are allowed to
// traverse between its indices. You can traverse between index |i| and index
// |j|, |i != j|, if and only if |gcd(nums[i], nums[j]) > 1|, where |gcd| is the
// greatest common divisor. Your task is to determine if for every pair of
// indices |i| and |j| in nums, where |i < j|, there exists a sequence of
// traversals that can take us from |i| to |j|. Return |true| if it is possible
// to traverse between all such pairs of indices, or |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(2709, GreatestCommonDivisorTraversal, Solution);

class Solution {
public:
  bool canTraverseAllPairs(vector<int> &nums) {
    int n = nums.size();
    if (n == 1) {
      return true;
    }
    Graph                   g(n);
    unordered_map<int, int> seen;
    for (int i = 0; i < n; ++i) {
      if (nums[i] == 1) {
        return false;
      }
      vector<int> f = getFactor(nums[i]);
      for (int x : f) {
        if (seen.find(x) != seen.end()) {
          g.add(i, seen[x]);
        } else {
          seen[x] = i;
        }
      }
    }
    return g.isConnected();
  }

private:
  vector<int> getFactor(int x) {
    vector<int> res;
    for (int i = 2; i * i <= x; ++i) {
      if (x % i == 0) {
        res.emplace_back(i);
        while (x % i == 0) {
          x /= i;
        }
      }
    }
    if (x != 1) {
      res.emplace_back(x);
    }
    return res;
  }
  class Graph {
  public:
    Graph(int n = 0) : n{n}, edges(n) {}
    void add(int x, int y) {
      edges[x].emplace_back(y);
      edges[y].emplace_back(x);
    }
    bool isConnected() {
      vector<bool> v(n, false);
      traverse(0, &v);
      return count(v.begin(), v.end(), true) == n;
    }

  private:
    int                 n;
    vector<vector<int>> edges;

    void traverse(int x, vector<bool> *v) {
      (*v)[x] = true;
      for (auto y : edges[x]) {
        if (!(*v)[y]) {
          traverse(y, v);
        }
      }
    }
  };
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,6]
// Output: true
//
// In this example, there are 3 possible pairs of indices: (0, 1), (0, 2), and
// (1, 2). To go from index 0 to index 1, we can use the sequence of traversals
// 0 -> 2 -> 1, where we move from index 0 to index 2 because gcd(nums[0],
// nums[2]) = gcd(2, 6) = 2 > 1, and then move from index 2 to index 1 because
// gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1. To go from index 0 to index 2, we
// can just go directly because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1.
// Likewise, to go from index 1 to index 2, we can just go directly because
// gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.

LEETCODE_SOLUTION_UNITTEST(2709, GreatestCommonDivisorTraversal, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 6};
  bool        expect   = true;
  bool        actual   = solution->canTraverseAllPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,9,5]
// Output: false
//
// No sequence of traversals can take us from index 0 to index 2 in this
// example. So, we return false.

LEETCODE_SOLUTION_UNITTEST(2709, GreatestCommonDivisorTraversal, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 9, 5};
  bool        expect   = false;
  bool        actual   = solution->canTraverseAllPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [4,3,12,8]
// Output: true
//
// There are 6 possible pairs of indices to traverse between: (0, 1), (0, 2),
// (0, 3), (1, 2), (1, 3), and (2, 3). A valid sequence of traversals exists for
// each pair, so we return true.

LEETCODE_SOLUTION_UNITTEST(2709, GreatestCommonDivisorTraversal, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 12, 8};
  bool        expect   = true;
  bool        actual   = solution->canTraverseAllPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}
