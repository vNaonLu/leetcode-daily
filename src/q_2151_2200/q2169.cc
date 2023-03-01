// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Operations to Obtain Zero
//
// https://leetcode.com/problems/count-operations-to-obtain-zero/
//
// Question ID: 2169
// Difficult  : Easy
// Solve Date : 2023/02/16 18:40

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2169. Count Operations to Obtain Zero|:
//
// You are given two non-negative integers |num1| and |num2|.
// In one operation, if |num1 >= num2|, you must subtract |num2| from |num1|,
// otherwise subtract |num1| from |num2|.
//
//  • For example, if |num1 = 5| and |num2 = 4|, subtract |num2| from |num1|,
//  thus obtaining |num1 = 1| and |num2 = 4|. However, if |num1 = 4| and |num2 =
//  5|, after one operation, |num1 = 4| and |num2 = 1|.
// Return the number of operations required to make either |num1 = 0| or |num2 =
// 0|.
//

LEETCODE_BEGIN_RESOLVING(2169, CountOperationsToObtainZero, Solution);

class Solution {
public:
  int countOperations(int num1, int num2) {
    if (num1 == 0 || num2 == 0) {
      return 0;
    }
    return 1 + countOperations(min(num1, num2), abs(num1 - num2));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= num1, num2 <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num1 = 2, num2 = 3
// Output: 3
//
// - Operation 1: num1 = 2, num2 = 3. Since num1 < num2, we subtract num1 from
// num2 and get num1 = 2, num2 = 3 - 2 = 1.
// - Operation 2: num1 = 2, num2 = 1. Since num1 > num2, we subtract num2 from
// num1.
// - Operation 3: num1 = 1, num2 = 1. Since num1 == num2, we subtract num2 from
// num1. Now num1 = 0 and num2 = 1. Since num1 == 0, we do not need to perform
// any further operations. So the total number of operations required is 3.

LEETCODE_SOLUTION_UNITTEST(2169, CountOperationsToObtainZero, example_1) {
  auto solution = MakeSolution();
  int  num1     = 2;
  int  num2     = 3;
  int  expect   = 3;
  int  actual   = solution->countOperations(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num1 = 10, num2 = 10
// Output: 1
//
// - Operation 1: num1 = 10, num2 = 10. Since num1 == num2, we subtract num2
// from num1 and get num1 = 10 - 10 = 0. Now num1 = 0 and num2 = 10. Since num1
// == 0, we are done. So the total number of operations required is 1.

LEETCODE_SOLUTION_UNITTEST(2169, CountOperationsToObtainZero, example_2) {
  auto solution = MakeSolution();
  int  num1     = 10;
  int  num2     = 10;
  int  expect   = 1;
  int  actual   = solution->countOperations(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}
