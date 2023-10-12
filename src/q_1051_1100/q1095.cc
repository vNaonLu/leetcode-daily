// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find in Mountain Array
//
// https://leetcode.com/problems/find-in-mountain-array/
//
// Question ID: 1095
// Difficult  : Hard
// Solve Date : 2023/10/12 21:41

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1095. Find in Mountain Array|:
//
// (This problem is an interactive problem.)
// You may recall that an array |arr| is a mountain array if and only if:
//
//  • |arr.length >= 3|
//
//  • There exists some |i| with |0 < i < arr.length - 1| such that:
//
//
//    • |arr[0] < arr[1] < ... < arr[i - 1] < arr[i]|
//
//    • |arr[i] > arr[i + 1] > ... > arr[arr.length - 1]|
//
//
// Given a mountain array |mountainArr|, return the minimum |index| such that
// |mountainArr.get(index) == target|. If such an |index| does not exist, return
// |-1|. You cannot access the mountain array directly. You may only access the
// array using a |MountainArray| interface:
//
//  • |MountainArray.get(k)| returns the element of the array at index |k|
//  (0-indexed).
//
//  • |MountainArray.length()| returns the length of the array.
// Submissions making more than |100| calls to |MountainArray.get| will be
// judged Wrong Answer. Also, any solutions that attempt to circumvent the judge
// will result in disqualification.
//
//

// just mock struct
class MountainArray {
public:
  int get(int index) { return index; }
  int length() { return 0; }
};

LEETCODE_BEGIN_RESOLVING(1095, FindInMountainArray, Solution);

class Solution {
public:
  int findInMountainArray(int target, MountainArray &mountainArr) {
    int n = mountainArr.length();
    int l = 1, r = n - 2, m, peak;
    while (l < r) {
      m      = l + (r - l) / 2;
      int xl = mountainArr.get(m - 1), x = mountainArr.get(m),
          xr = mountainArr.get(m + 1);
      if (xl < x && x > xr) {
        peak = m;
        break;
      } else if (x < xr)
        l = m + 1;
      else
        r = m - 1;
    }
    peak = r;
    l = 0, r = peak;
    while (l < r) {
      m     = l + (r - l) / 2;
      int x = mountainArr.get(m);
      if (x == target)
        return m;
      else if (x < target)
        l = m + 1;
      else
        r = m;
    }
    l = peak, r = n;
    while (l < r) {
      m     = l + (r - l) / 2;
      int x = mountainArr.get(m);
      if (x == target)
        return m;
      else if (x > target)
        l = m + 1;
      else
        r = m;
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= mountain_arr.length() <= 10⁴|
// * |0 <= target <= 10⁹|
// * |0 <= mountain_arr.get(index) <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: array = [1,2,3,4,5,3,1], target = 3
// Output: 2
//
// 3 exists in the array, at index=2 and index=5. Return the minimum index,
// which is 2.

LEETCODE_SOLUTION_UNITTEST(1095, FindInMountainArray, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: array = [0,1,2,4,2,1], target = 3
// Output: -1
//
// 3 does not exist in |the array,| so we return -1.

LEETCODE_SOLUTION_UNITTEST(1095, FindInMountainArray, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}
