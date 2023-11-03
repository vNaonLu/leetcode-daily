// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Build an Array With Stack Operations
//
// https://leetcode.com/problems/build-an-array-with-stack-operations/
//
// Question ID: 1441
// Difficult  : Medium
// Solve Date : 2023/11/03 19:46

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1441. Build an Array With Stack Operations|:
//
// You are given an integer array |target| and an integer |n|.
// You have an empty stack with the two following operations:
//
//  • |"Push"|: pushes an integer to the top of the stack.
//
//  • |"Pop"|: removes the integer on the top of the stack.
// You also have a stream of the integers in the range |[1, n]|.
// Use the two stack operations to make the numbers in the stack (from the
// bottom to the top) equal to |target|. You should follow the following rules:
//
//  • If the stream of the integers is not empty, pick the next integer from the
//  stream and push it to the top of the stack.
//
//  • If the stack is not empty, pop the integer at the top of the stack.
//
//  • If, at any moment, the elements in the stack (from the bottom to the top)
//  are equal to |target|, do not read new integers from the stream and do not
//  do more operations on the stack.
// Return the stack operations needed to build |target| following the mentioned
// rules. If there are multiple valid answers, return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(1441, BuildAnArrayWithStackOperations, Solution);

class Solution {
public:
  vector<string> buildArray(vector<int> &target, int n) {
    vector<string> res;
    int            cur = 1;
    for (int i = 0; i < target.size(); ++i) {
      while (cur++ != target[i]) {
        res.emplace_back("Push");
        res.emplace_back("Pop");
      }
      res.emplace_back("Push");
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= target.length <= 100|
// * |1 <= n <= 100|
// * |1 <= target[i] <= n|
// * |target| is strictly increasing.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: target = [1,3], n = 3
// Output: ["Push","Push","Pop","Push"]
//
// Initially the stack s is empty. The last element is the top of the stack.
// Read 1 from the stream and push it to the stack. s = [1].
// Read 2 from the stream and push it to the stack. s = [1,2].
// Pop the integer on the top of the stack. s = [1].
// Read 3 from the stream and push it to the stack. s = [1,3].

LEETCODE_SOLUTION_UNITTEST(1441, BuildAnArrayWithStackOperations, example_1) {
  auto           solution = MakeSolution();
  vector<int>    target   = {1, 3};
  int            n        = 3;
  vector<string> expect   = {"Push", "Push", "Pop", "Push"};
  vector<string> actual   = solution->buildArray(target, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: target = [1,2,3], n = 3
// Output: ["Push","Push","Push"]
//
// Initially the stack s is empty. The last element is the top of the stack.
// Read 1 from the stream and push it to the stack. s = [1].
// Read 2 from the stream and push it to the stack. s = [1,2].
// Read 3 from the stream and push it to the stack. s = [1,2,3].

LEETCODE_SOLUTION_UNITTEST(1441, BuildAnArrayWithStackOperations, example_2) {
  auto           solution = MakeSolution();
  vector<int>    target   = {1, 2, 3};
  int            n        = 3;
  vector<string> expect   = {"Push", "Push", "Push"};
  vector<string> actual   = solution->buildArray(target, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: target = [1,2], n = 4
// Output: ["Push","Push"]
//
// Initially the stack s is empty. The last element is the top of the stack.
// Read 1 from the stream and push it to the stack. s = [1].
// Read 2 from the stream and push it to the stack. s = [1,2].
// Since the stack (from the bottom to the top) is equal to target, we stop the
// stack operations. The answers that read integer 3 from the stream are not
// accepted.

LEETCODE_SOLUTION_UNITTEST(1441, BuildAnArrayWithStackOperations, example_3) {
  auto           solution = MakeSolution();
  vector<int>    target   = {1, 2};
  int            n        = 4;
  vector<string> expect   = {"Push", "Push"};
  vector<string> actual   = solution->buildArray(target, n);
  LCD_EXPECT_EQ(expect, actual);
}
