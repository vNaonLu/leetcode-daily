// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Implement Rand10() Using Rand7()
//
// https://leetcode.com/problems/implement-rand10-using-rand7/
//
// Question ID: 470
// Difficult  : Medium
// Solve Date : 2024/04/11 19:05

#include <iosfwd>
#include <random>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

LEETCODE_SOLUTION_NAMESPACE(470, ImplementRand10UsingRand7) {
  int rand7() {
    random_device              rd;
    mt19937                    gen(rd());
    uniform_int_distribution<> d(1, 7);
    return d(gen);
  }
}

// Description of |470. Implement Rand10() Using Rand7()|:
//
// Given the API |rand7()| that generates a uniform random integer in the range
// |[1, 7]|, write a function |rand10()| that generates a uniform random integer
// in the range |[1, 10]|. You can only call the API |rand7()|, and you
// shouldn't call any other API. Please do not use a language's built-in random
// API. Each test case will have one internal argument |n|, the number of times
// that your implemented function |rand10()| will be called while testing. Note
// that this is not an argument passed to |rand10()|.
//
//

LEETCODE_BEGIN_RESOLVING(470, ImplementRand10UsingRand7, Solution);

class Solution {
public:
  int rand10() {
    int res = rand7();
    int m   = 7;
    while (res > 5) {
      m   = res - 5;
      res = rand7();
    }
    while (m == 7) {
      m = rand7();
    }
    return (m % 2 ? 5 : 0) + res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * What is the [expected value] for the number of calls to |rand7()| function?
// * Could you minimize the number of calls to |rand7()|?
///////////////////////////////////////////////////////////////////////////////

static bool CheckValid(int x) { return x >= 1 && x <= 10; }

// [Example #1]
//  Input: n = 1
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(470, ImplementRand10UsingRand7, example_1) {
  auto solution = MakeSolution();
  int  actual   = solution->rand10();
  EXPECT_TRUE(CheckValid(actual));
}

// [Example #2]
//  Input: n = 2
// Output: [2,8]
//

LEETCODE_SOLUTION_UNITTEST(470, ImplementRand10UsingRand7, example_2) {
  auto solution = MakeSolution();
  int  actual   = solution->rand10();
  EXPECT_TRUE(CheckValid(actual));
}

// [Example #3]
//  Input: n = 3
// Output: [3,8,10]
//

LEETCODE_SOLUTION_UNITTEST(470, ImplementRand10UsingRand7, example_3) {
  auto solution = MakeSolution();
  int  actual   = solution->rand10();
  EXPECT_TRUE(CheckValid(actual));
}
