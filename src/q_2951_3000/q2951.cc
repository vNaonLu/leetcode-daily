// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Peaks
//
// https://leetcode.com/problems/find-the-peaks/
//
// Question ID: 2951
// Difficult  : Easy
// Solve Date : 2024/02/08 09:43

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2951. Find the Peaks|:
//
// You are given a 0-indexed array |mountain|. Your task is to find all the
// peaks in the |mountain| array. Return an array that consists of indices of
// peaks in the given array in any order. Notes:
//
//  • A peak is defined as an element that is strictly greater than its
//  neighboring elements.
//
//  • The first and last elements of the array are not a peak.
//
//

LEETCODE_BEGIN_RESOLVING(2951, FindThePeaks, Solution);

class Solution {
public:
  vector<int> findPeaks(vector<int> &mountain) {
    vector<int> res;
    for (int i = 1; i < mountain.size() - 1; ++i) {
      if (mountain[i] > mountain[i - 1] && mountain[i] > mountain[i + 1]) {
        res.emplace_back(i);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= mountain.length <= 100|
// * |1 <= mountain[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mountain = [2,4,4]
// Output: []
//
// mountain[0] and mountain[2] can not be a peak because they are first and last
// elements of the array. mountain[1] also can not be a peak because it is not
// strictly greater than mountain[2]. So the answer is [].

LEETCODE_SOLUTION_UNITTEST(2951, FindThePeaks, example_1) {
  auto        solution = MakeSolution();
  vector<int> mountain = {2, 4, 4};
  vector<int> expect   = {};
  vector<int> actual   = solution->findPeaks(mountain);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: mountain = [1,4,3,8,5]
// Output: [1,3]
//
// mountain[0] and mountain[4] can not be a peak because they are first and last
// elements of the array. mountain[2] also can not be a peak because it is not
// strictly greater than mountain[3] and mountain[1]. But mountain [1] and
// mountain[3] are strictly greater than their neighboring elements. So the
// answer is [1,3].

LEETCODE_SOLUTION_UNITTEST(2951, FindThePeaks, example_2) {
  auto        solution = MakeSolution();
  vector<int> mountain = {1, 4, 3, 8, 5};
  vector<int> expect   = {1, 3};
  vector<int> actual   = solution->findPeaks(mountain);
  EXPECT_ANYORDER_EQ(expect, actual);
}
