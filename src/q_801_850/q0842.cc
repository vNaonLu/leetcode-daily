// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Split Array into Fibonacci Sequence
//
// https://leetcode.com/problems/split-array-into-fibonacci-sequence/
//
// Question ID: 842
// Difficult  : Medium
// Solve Date : 2024/08/23 23:47

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |842. Split Array into Fibonacci Sequence|:
//
// You are given a string of digits |num|, such as |"123456579"|. We can split
// it into a Fibonacci-like sequence |[123, 456, 579]|. Formally, a
// Fibonacci-like sequence is a list |f| of non-negative integers such that:
//
//  • |0 <= f[i] < 2³¹|, (that is, each integer fits in a 32-bit signed integer
//  type),
//
//  • |f.length >= 3|, and
//
//  • |f[i] + f[i + 1] == f[i + 2]| for all |0 <= i < f.length - 2|.
// Note that when splitting the string into pieces, each piece must not have
// extra leading zeroes, except if the piece is the number |0| itself. Return
// any Fibonacci-like sequence split from |num|, or return |[]| if it cannot be
// done.
//
//

LEETCODE_BEGIN_RESOLVING(842, SplitArrayIntoFibonacciSequence, Solution);

class Solution {
public:
  vector<int> splitIntoFibonacci(string num) {
    vector<int> ds;
    helper(0, ds, num);
    return ds;
  }

private:
  bool helper(int ind, vector<int> &ds, string &numStr) {
    if (ind == numStr.size() && ds.size() > 2) {
      return true;
    }
    for (int i = 1; i <= 10 && ind + i <= numStr.size(); i++) {
      string  temp = numStr.substr(ind, i);
      int64_t num  = stoll(temp);
      if ((temp.size() > 1) && (temp[0] == '0'))
        break;
      if (num > numeric_limits<int>::max())
        break;
      if ((ds.size() < 2) ||
          ((int64_t)ds[ds.size() - 1] + (int64_t)ds[ds.size() - 2] == num)) {
        ds.push_back(num);
        if (helper(ind + i, ds, numStr))
          return true;
        ds.pop_back();
      } else if (((int64_t)ds[ds.size() - 1] + (int64_t)ds[ds.size() - 2]) <
                 num)
        break;
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= num.length <= 200|
// * |num| contains only digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = "1101111"
// Output: [11,0,11,11]
//

LEETCODE_SOLUTION_UNITTEST(842, SplitArrayIntoFibonacciSequence, example_1) {
  auto        solution = MakeSolution();
  string      num      = "1101111";
  vector<int> expect   = {11, 0, 11, 11};
  vector<int> actual   = solution->splitIntoFibonacci(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = "112358130"
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(842, SplitArrayIntoFibonacciSequence, example_2) {
  auto        solution = MakeSolution();
  string      num      = "112358130";
  vector<int> expect   = {};
  vector<int> actual   = solution->splitIntoFibonacci(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = "0123"
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(842, SplitArrayIntoFibonacciSequence, example_3) {
  auto        solution = MakeSolution();
  string      num      = "0123";
  vector<int> expect   = {};
  vector<int> actual   = solution->splitIntoFibonacci(num);
  LCD_EXPECT_EQ(expect, actual);
}
