// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Grumpy Bookstore Owner
//
// https://leetcode.com/problems/grumpy-bookstore-owner/
//
// Question ID: 1052
// Difficult  : Medium
// Solve Date : 2024/06/21 23:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1052. Grumpy Bookstore Owner|:
//
// There is a bookstore owner that has a store open for |n| minutes. Every
// minute, some number of customers enter the store. You are given an integer
// array |customers| of length |n| where |customers[i]| is the number of the
// customer that enters the store at the start of the |iᵗʰ| minute and all those
// customers leave after the end of that minute. On some minutes, the bookstore
// owner is grumpy. You are given a binary array grumpy where |grumpy[i]| is |1|
// if the bookstore owner is grumpy during the |iᵗʰ| minute, and is |0|
// otherwise. When the bookstore owner is grumpy, the customers of that minute
// are not satisfied, otherwise, they are satisfied. The bookstore owner knows a
// secret technique to keep themselves not grumpy for |minutes| consecutive
// minutes, but can only use it once. Return the maximum number of customers
// that can be satisfied throughout the day.
//
//

LEETCODE_BEGIN_RESOLVING(1052, GrumpyBookstoreOwner, Solution);

class Solution {
public:
  int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes) {
    int init = 0;
    int mx   = 0;
    int curr = 0;

    for (int i = 0; i < customers.size(); ++i) {
      if (grumpy[i] == 0) {
        init += customers[i];
      } else if (i < minutes) {
        curr += customers[i];
      }
    }

    mx = curr;

    for (int i = minutes; i < customers.size(); ++i) {
      curr += customers[i] * grumpy[i];
      curr -= customers[i - minutes] * grumpy[i - minutes];
      mx = max(mx, curr);
    }

    return init + mx;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == customers.length == grumpy.length|
// * |1 <= minutes <= n <= 2 * 10⁴|
// * |0 <= customers[i] <= 1000|
// * |grumpy[i]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes =
//  3
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(1052, GrumpyBookstoreOwner, example_1) {
  auto        solution  = MakeSolution();
  vector<int> customers = {1, 0, 1, 2, 1, 1, 7, 5};
  vector<int> grumpy    = {0, 1, 0, 1, 0, 1, 0, 1};
  int         minutes   = 3;
  int         expect    = 16;
  int         actual    = solution->maxSatisfied(customers, grumpy, minutes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: customers = [1], grumpy = [0], minutes = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1052, GrumpyBookstoreOwner, example_2) {
  auto        solution  = MakeSolution();
  vector<int> customers = {1};
  vector<int> grumpy    = {0};
  int         minutes   = 1;
  int         expect    = 1;
  int         actual    = solution->maxSatisfied(customers, grumpy, minutes);
  LCD_EXPECT_EQ(expect, actual);
}
