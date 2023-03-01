// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Construct the Rectangle
//
// https://leetcode.com/problems/construct-the-rectangle/
//
// Question ID: 492
// Difficult  : Easy
// Solve Date : 2022/02/13 21:46

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |492. Construct the Rectangle|:
//
// A web developer needs to know how to design a web page's size. So, given a
// specific rectangular web page’s area, your job by now is to design a
// rectangular web page, whose length L and width W satisfy the following
// requirements:
//
//  1. The area of the rectangular web page you designed must equal to the given
//  target area.
//
//  2. The width |W| should not be larger than the length |L|, which means |L >=
//  W|.
//
//  3. The difference between length |L| and width |W| should be as small as
//  possible.
// Return an array |[L, W]| where |L| and |W| are the length and width of
// the web page you designed in sequence.  
//

LEETCODE_BEGIN_RESOLVING(492, ConstructTheRectangle, Solution);

class Solution {
public:
  vector<int> constructRectangle(int area) {
    int l = sqrt(area);
    while (area % l != 0) {
      --l;
    }
    return {area / l, l};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= area <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: area = 4
// Output: [2,2]
//
// The target area is 4, and all the possible ways to construct it are [1,4],
// [2,2], [4,1]. But according to requirement 2, [1,4] is illegal; according to
// requirement 3, [4,1] is not optimal compared to [2,2]. So the length L is 2,
// and the width W is 2.

LEETCODE_SOLUTION_UNITTEST(492, ConstructTheRectangle, example_1) {
  auto        solution = MakeSolution();
  int         area     = 4;
  vector<int> expect   = {2, 2};
  vector<int> actual   = solution->constructRectangle(area);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: area = 37
// Output: [37,1]
//

LEETCODE_SOLUTION_UNITTEST(492, ConstructTheRectangle, example_2) {
  auto        solution = MakeSolution();
  int         area     = 37;
  vector<int> expect   = {37, 1};
  vector<int> actual   = solution->constructRectangle(area);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: area = 122122
// Output: [427,286]
//

LEETCODE_SOLUTION_UNITTEST(492, ConstructTheRectangle, example_3) {
  auto        solution = MakeSolution();
  int         area     = 122122;
  vector<int> expect   = {427, 286};
  vector<int> actual   = solution->constructRectangle(area);
  LCD_EXPECT_EQ(expect, actual);
}
