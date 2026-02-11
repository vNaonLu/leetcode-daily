// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Longest Balanced Subarray II
//
// https://leetcode.com/problems/longest-balanced-subarray-ii/
//
// Question ID: 3721
// Difficult  : Hard
// Solve Date : 2026/02/11 19:19

#include <bitset>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3721. Longest Balanced Subarray II|:
//
// You are given an integer array |nums|.
// A subarray is called balanced if the number of distinct even numbers in the
// subarray is equal to the number of distinct odd numbers. Return the length of
// the longest balanced subarray.
//
//

LEETCODE_BEGIN_RESOLVING(3721, LongestBalancedSubarrayII, Solution);

class Solution {
public:
  int longestBalanced0(vector<int> &nums) {
    const int n   = nums.size();
    int       len = 0;
    for (int l = 0; l < n; l++) {
      if (l > n - len)
        break;
      int diff = 0;
      for (int r = l; r < n; r++) {
        const int x = nums[r];
        if (!seen[x]) {
          diff += (1 - (x & 1) * 2), seen[x] = 1;
        }
        if (diff == 0)
          len = max(len, r - l + 1);
      }
      for (int i = l; i < n; i++)
        seen[nums[i]] = 0;
    }
    return len;
  }

  int longestBalanced(vector<int> &nums) {
    const int n = nums.size();
    if (n <= 2000)
      return longestBalanced0(nums);

    const int   M = *max_element(nums.begin(), nums.end());
    vector<int> last(M + 1, n);
    vector<int> nextPos(n, n);
    for (int i = n - 1; i >= 0; i--) {
      const int x = nums[i];
      nextPos[i]  = last[x];
      last[x]     = i;
    }

    // Compute prefix sums
    vector<int> prefix(n);
    int         sum = 0;
    for (int i = 0; i < n; i++) {
      const int x = nums[i];
      if (!seen[x]) {
        sum += (x & 1) ? 1 : -1;
        seen[x] = 1;
      }
      prefix[i] = sum;
    }
    // reset for the next testcase
    for (int i = 0; i < n; i++)
      seen[nums[i]] = 0;

    SegmentTree seg(prefix);

    int ans = seg.findLast0(1, 0, n - 1) + 1;

    for (int i = 0; i < n - 1; i++) {
      int r = nextPos[i] - 1;
      // Only update if the range is valid
      if (i + 1 <= r) {
        int val = (nums[i] & 1) ? -1 : 1;
        seg.updateRange(i + 1, r, 1, 0, n - 1, val);
      }

      // Only search if a better answer is possible
      if (i + ans + 1 < n) { // this check saves half of time
        int right = seg.findLast0(1, 0, n - 1);
        if (right != -1)
          ans = max(ans, right - i);
      }
    }
    return ans;
  }

private:
  struct Node {
    short min, max, lazy;
    Node()
        : min(numeric_limits<short>::max()), max(numeric_limits<short>::max()),
          lazy(0) {}
    Node(int x) : min(x), max(x), lazy(0) {}
  };

  class SegmentTree {
  public:
    vector<Node> segTree;
    unsigned     n;

    SegmentTree(vector<int> &arr) {
      n = arr.size();
      // 1-indexed segment tree
      segTree.assign(n << 2, Node());
      buildTree(1, 0, n - 1, arr);
    }

    // Pulls values from children up to the parent
    void pull(int i) {
      segTree[i].min = min(segTree[2 * i].min, segTree[2 * i + 1].min);
      segTree[i].max = max(segTree[2 * i].max, segTree[2 * i + 1].max);
    }

    void buildTree(int i, int l, int r, vector<int> &arr) {
      if (l == r) {
        segTree[i] = Node(arr[l]);
        return;
      }
      int m = (l + r) >> 1;
      buildTree(2 * i, l, m, arr);
      buildTree(2 * i + 1, m + 1, r, arr);
      pull(i);
    }

    void apply(int i, int l, int r) {
      if (segTree[i].lazy == 0)
        return;
      segTree[i].min += segTree[i].lazy;
      segTree[i].max += segTree[i].lazy;
      if (l < r) {
        segTree[2 * i].lazy += segTree[i].lazy;
        segTree[2 * i + 1].lazy += segTree[i].lazy;
      }
      segTree[i].lazy = 0;
    }

    void updateRange(int start, int end, int i, int l, int r, int val) {
      apply(i, l, r);
      if (l > end || r < start)
        return;

      if (l >= start && r <= end) {
        segTree[i].lazy += val;
        apply(i, l, r);
        return;
      }

      int m = (l + r) >> 1;
      updateRange(start, end, 2 * i, l, m, val);
      updateRange(start, end, 2 * i + 1, m + 1, r, val);
      pull(i);
    }

    int findLast0(int i, int l, int r) {
      apply(i, l, r);
      // if 0 isn't within [min, max], no 0
      if (segTree[i].min > 0 || segTree[i].max < 0)
        return -1;

      if (l == r)
        return l;

      int m = (l + r) >> 1;
      // To find the index for the last 0,
      // search the right child first
      int right = findLast0(2 * i + 1, m + 1, r);
      if (right != -1)
        return right;
      return findLast0(2 * i, l, m);
    }
  };

  static constexpr int N    = 1e5 + 1;
  bitset<N>            seen = 0;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,4,3]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3721, LongestBalancedSubarrayII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 4, 3};
  int         expect   = 4;
  int         actual   = solution->longestBalanced(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,2,5,4]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3721, LongestBalancedSubarrayII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 2, 5, 4};
  int         expect   = 5;
  int         actual   = solution->longestBalanced(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,2]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3721, LongestBalancedSubarrayII, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 2};
  int         expect   = 3;
  int         actual   = solution->longestBalanced(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [38,33,44]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3721, LongestBalancedSubarrayII, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {38, 33, 44};
  int         expect   = 2;
  int         actual   = solution->longestBalanced(nums);
  LCD_EXPECT_EQ(expect, actual);
}
