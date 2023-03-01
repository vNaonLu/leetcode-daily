// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reduce Array Size to The Half
//
// https://leetcode.com/problems/reduce-array-size-to-the-half/
//
// Question ID: 1338
// Difficult  : Medium
// Solve Date : 2022/08/18 18:23

#include <iosfwd>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1338. Reduce Array Size to The Half|:
//
// You are given an integer array |arr|. You can choose a set of integers and
// remove all the occurrences of these integers in the array. Return the minimum
// size of the set so that at least half of the integers of the array are
// removed.
//

LEETCODE_BEGIN_RESOLVING(1338, ReduceArraySizeToTheHalf, Solution);

class Solution {
public:
  int minSetSize(vector<int> &arr) {
    auto cnt    = unordered_map<int, int>();
    auto target = arr.size() / 2;
    for (auto &x : arr) {
      ++cnt[x];
    }

    auto pq = priority_queue<int>();
    for (auto &[n, num] : cnt) {
      pq.emplace(num);
    }

    auto res  = 0;
    auto curr = 0;
    while (!pq.empty()) {
      ++res;
      curr += pq.top();
      pq.pop();

      if (curr >= target) {
        break;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= arr.length <= 10⁵|
// * |arr.length| is even.
// * |1 <= arr[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [3,3,3,3,5,5,5,2,2,7]
// Output: 2
//
// Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5 (i.e
// equal to half of the size of the old array). Possible sets of size 2 are
// {3,5},{3,2},{5,2}. Choosing set {2,7} is not possible as it will make the new
// array [3,3,3,3,5,5,5] which has a size greater than half of the size of the
// old array.

LEETCODE_SOLUTION_UNITTEST(1338, ReduceArraySizeToTheHalf, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 3, 3, 3, 5, 5, 5, 2, 2, 7};
  int         expect   = 2;
  int         actual   = solution->minSetSize(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [7,7,7,7,7,7]
// Output: 1
//
// The only possible set you can choose is {7}. This will make the new array
// empty.

LEETCODE_SOLUTION_UNITTEST(1338, ReduceArraySizeToTheHalf, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {7, 7, 7, 7, 7, 7};
  int         expect   = 1;
  int         actual   = solution->minSetSize(arr);
  LCD_EXPECT_EQ(expect, actual);
}
