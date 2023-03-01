// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Fizz Buzz
//
// https://leetcode.com/problems/fizz-buzz/
//
// Question ID: 412
// Difficult  : Easy
// Solve Date : 2022/08/31 18:11

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |412. Fizz Buzz|:
//
// Given an integer |n|, return a string array |answer| (1-indexed) where:
//
//  • |answer[i] == "FizzBuzz"| if |i| is divisible by |3| and |5|.
//
//  • |answer[i] == "Fizz"| if |i| is divisible by |3|.
//
//  • |answer[i] == "Buzz"| if |i| is divisible by |5|.
//
//  • |answer[i] == i| (as a string) if none of the above conditions are true.
//

LEETCODE_BEGIN_RESOLVING(412, FizzBuzz, Solution);

class Solution {
public:
  vector<string> fizzBuzz(int n) {
    auto res = vector<string>();
    res.reserve(n);
    while (n) {
      if (n % 15 == 0) {
        res.emplace_back("FizzBuzz");
      } else if (n % 5 == 0) {
        res.emplace_back("Buzz");
      } else if (n % 3 == 0) {
        res.emplace_back("Fizz");
      } else {
        res.emplace_back(to_string(n));
      }
      --n;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: ["1","2","Fizz"]
//

LEETCODE_SOLUTION_UNITTEST(412, FizzBuzz, example_1) {
  auto           solution = MakeSolution();
  int            n        = 3;
  vector<string> expect   = {"1", "2", "Fizz"};
  vector<string> actual   = solution->fizzBuzz(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5
// Output: ["1","2","Fizz","4","Buzz"]
//

LEETCODE_SOLUTION_UNITTEST(412, FizzBuzz, example_2) {
  auto           solution = MakeSolution();
  int            n        = 5;
  vector<string> expect   = {"1", "2", "Fizz", "4", "Buzz"};
  vector<string> actual   = solution->fizzBuzz(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 15
// Output:
// ["1","2","Fizz","4","Buzz","Fizz","7","8","Fizz","Buzz","11","Fizz","13","14","FizzBuzz"]
//

LEETCODE_SOLUTION_UNITTEST(412, FizzBuzz, example_3) {
  auto           solution = MakeSolution();
  int            n        = 15;
  vector<string> expect   = {"1",    "2",    "Fizz", "4",    "Buzz",
                             "Fizz", "7",    "8",    "Fizz", "Buzz",
                             "11",   "Fizz", "13",   "14",   "FizzBuzz"};
  vector<string> actual   = solution->fizzBuzz(n);
  LCD_EXPECT_EQ(expect, actual);
}
