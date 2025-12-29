// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Kth Smallest Product of Two Sorted Arrays
//
// https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/
//
// Question ID: 2040
// Difficult  : Hard
// Solve Date : 2025/06/25 20:46

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2040. Kth Smallest Product of Two Sorted Arrays|:
//
// Given two sorted 0-indexed integer arrays |nums1| and |nums2| as well as an
// integer |k|, return the |kᵗʰ| (1-based) smallest product of |nums1[i] *
// nums2[j]| where |0 <= i < nums1.length| and |0 <= j < nums2.length|.
//
//

LEETCODE_BEGIN_RESOLVING(2040, KthSmallestProductOfTwoSortedArrays, Solution);

class Solution {
public:
  long long kthSmallestProduct(vector<int> &nums1, vector<int> &nums2,
                               long long k) {
    int64_t left  = -1e10;
    int64_t right = 1e10;
    while (left < right) {
      auto mid = left + (right - left) / 2;
      if (count(nums1, nums2, mid) < k) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
  }

private:
  int64_t count(auto nums1, auto nums2, int64_t target) {
    int64_t res = 0;
    for (auto x : nums1) {
      if (x == 0) {
        if (target >= 0) {
          res += nums2.size();
        }
        continue;
      }
      int low = 0, high = nums2.size();
      while (low < high) {
        int       mid  = (low + high) / 2;
        long long prod = 1LL * x * nums2[mid];
        if (prod <= target) {
          if (x > 0)
            low = mid + 1;
          else
            high = mid;
        } else {
          if (x > 0)
            high = mid;
          else
            low = mid + 1;
        }
      }

      res += (x > 0) ? low : (nums2.size() - low);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 5 * 10⁴|
// * |-10⁵ <= nums1[i], nums2[j] <= 10⁵|
// * |1 <= k <= nums1.length * nums2.length|
// * |nums1| and |nums2| are sorted.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [2,5], nums2 = [3,4], k = 2
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(2040, KthSmallestProductOfTwoSortedArrays,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 5};
  vector<int> nums2    = {3, 4};
  long long   k        = 2;
  long long   expect   = 8;
  long long   actual   = solution->kthSmallestProduct(nums1, nums2, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2040, KthSmallestProductOfTwoSortedArrays,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {-4, -2, 0, 3};
  vector<int> nums2    = {2, 4};
  long long   k        = 6;
  long long   expect   = 0;
  long long   actual   = solution->kthSmallestProduct(nums1, nums2, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
// Output: -6
//

LEETCODE_SOLUTION_UNITTEST(2040, KthSmallestProductOfTwoSortedArrays,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {-2, -1, 0, 1, 2};
  vector<int> nums2    = {-3, -1, 2, 4, 5};
  long long   k        = 3;
  long long   expect   = -6;
  long long   actual   = solution->kthSmallestProduct(nums1, nums2, k);
  LCD_EXPECT_EQ(expect, actual);
}
