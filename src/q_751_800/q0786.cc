// Copyright 2024 Naon Lu
//
// This file describes the solution of
// K-th Smallest Prime Fraction
//
// https://leetcode.com/problems/k-th-smallest-prime-fraction/
//
// Question ID: 786
// Difficult  : Medium
// Solve Date : 2024/05/10 18:17

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |786. K-th Smallest Prime Fraction|:
//
// You are given a sorted integer array |arr| containing |1| and prime numbers,
// where all the integers of |arr| are unique. You are also given an integer
// |k|. For every |i| and |j| where |0 <= i < j < arr.length|, we consider the
// fraction |arr[i] / arr[j]|. Return the |kᵗʰ| smallest fraction considered.
// Return your answer as an array of integers of size |2|, where |answer[0] ==
// arr[i]| and |answer[1] == arr[j]|.
//
//

LEETCODE_BEGIN_RESOLVING(786, KThSmallestPrimeFraction, Solution);

class Solution {
public:
  vector<int> kthSmallestPrimeFraction(vector<int> &arr, int k) {
    int                                          n = arr.size();
    priority_queue<pair<double, pair<int, int>>> pq;

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        double x = arr[i] / (1.0 * arr[j]);
        if (pq.size() == k) {
          if (x < pq.top().first) {
            pq.pop();
            pq.push({
                x, {arr[i], arr[j]}
            });
          }
        } else {
          pq.push({
              x, {arr[i], arr[j]}
          });
        }
      }
    }

    return {pq.top().second.first, pq.top().second.second};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= arr.length <= 1000|
// * |1 <= arr[i] <= 3 * 10⁴|
// * |arr[0] == 1|
// * |arr[i]| is a prime number for |i > 0|.
// * All the numbers of |arr| are unique and sorted in strictly increasing
// order.
// * |1 <= k <= arr.length * (arr.length - 1) / 2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,3,5], k = 3
// Output: [2,5]
//

LEETCODE_SOLUTION_UNITTEST(786, KThSmallestPrimeFraction, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 5};
  int         k        = 3;
  vector<int> expect   = {2, 5};
  vector<int> actual   = solution->kthSmallestPrimeFraction(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,7], k = 1
// Output: [1,7]
//

LEETCODE_SOLUTION_UNITTEST(786, KThSmallestPrimeFraction, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 7};
  int         k        = 1;
  vector<int> expect   = {1, 7};
  vector<int> actual   = solution->kthSmallestPrimeFraction(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}
