// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Average Salary Excluding the Minimum and Maximum Salary
//
// https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/
//
// Question ID: 1491
// Difficult  : Easy
// Solve Date : 2022/04/14 18:40

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1491. Average Salary Excluding the Minimum and Maximum
// Salary|:
//
// You are given an array of unique integers |salary| where |salary[i]| is the
// salary of the |iᵗʰ| employee. Return the average salary of employees
// excluding the minimum and maximum salary. Answers within |10⁻⁵| of the actual
// answer will be accepted.  
//

LEETCODE_BEGIN_RESOLVING(1491, AverageSalaryExcludingTheMinimumAndMaximumSalary,
                         Solution);

class Solution {
public:
  double average(vector<int> &salary) {
    int  mx = salary.front(), mn = salary.front(), sum = salary.front();
    auto beg = salary.begin() + 1;
    while (beg != salary.end()) {
      mx = max(mx, *beg);
      mn = min(mn, *beg);
      sum += *(beg++);
    }

    return double(sum - mx - mn) / (salary.size() - 2);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= salary.length <= 100|
// * |1000 <= salary[i] <= 10⁶|
// * All the integers of |salary| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: salary = [4000,3000,1000,2000]
// Output: 2500.00000
//
// Minimum salary and maximum salary are 1000 and 4000 respectively.
// Average salary excluding minimum and maximum salary is (2000+3000) / 2 = 2500

LEETCODE_SOLUTION_UNITTEST(1491,
                           AverageSalaryExcludingTheMinimumAndMaximumSalary,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> salary   = {4000, 3000, 1000, 2000};
  double      expect   = 2500.00000;
  double      actual   = solution->average(salary);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: salary = [1000,2000,3000]
// Output: 2000.00000
//
// Minimum salary and maximum salary are 1000 and 3000 respectively.
// Average salary excluding minimum and maximum salary is (2000) / 1 = 2000

LEETCODE_SOLUTION_UNITTEST(1491,
                           AverageSalaryExcludingTheMinimumAndMaximumSalary,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> salary   = {1000, 2000, 3000};
  double      expect   = 2000.00000;
  double      actual   = solution->average(salary);
  LCD_EXPECT_EQ(expect, actual);
}
