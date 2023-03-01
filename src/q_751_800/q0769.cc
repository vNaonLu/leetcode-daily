// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Max Chunks To Make Sorted
//
// https://leetcode.com/problems/max-chunks-to-make-sorted/
//
// Question ID: 769
// Difficult  : Medium
// Solve Date : 2022/01/24 18:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |769. Max Chunks To Make Sorted|:
//
// You are given an integer array |arr| of length |n| that represents a
// permutation of the integers in the range |[0, n - 1]|. We split |arr| into
// some number of chunks (i.e., partitions), and individually sort each chunk.
// After concatenating them, the result should equal the sorted array. Return
// the largest number of chunks we can make to sort the array.  
//

LEETCODE_BEGIN_RESOLVING(769, MaxChunksToMakeSorted, Solution);

class Solution {
public:
  int maxChunksToSorted(vector<int> &arr) {
    int res = 0, cur = -1;
    for (int i = 0; i < arr.size(); ++i) {
      cur = max({cur, i, arr[i]});
      if (cur <= i)
        ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == arr.length|
// * |1 <= n <= 10|
// * |0 <= arr[i] < n|
// * All the elements of |arr| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [4,3,2,1,0]
// Output: 1
//
// Splitting into two or more chunks will not return the required result.
// For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2],
// which isn't sorted.

LEETCODE_SOLUTION_UNITTEST(769, MaxChunksToMakeSorted, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {4, 3, 2, 1, 0};
  int         expect   = 1;
  int         actual   = solution->maxChunksToSorted(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,0,2,3,4]
// Output: 4
//
// We can split into two chunks, such as [1, 0], [2, 3, 4].
// However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks
// possible.

LEETCODE_SOLUTION_UNITTEST(769, MaxChunksToMakeSorted, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 0, 2, 3, 4};
  int         expect   = 4;
  int         actual   = solution->maxChunksToSorted(arr);
  LCD_EXPECT_EQ(expect, actual);
}
