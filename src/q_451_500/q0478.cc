// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Generate Random Point in a Circle
//
// https://leetcode.com/problems/generate-random-point-in-a-circle/
//
// Question ID: 478
// Difficult  : Medium
// Solve Date : 2024/04/16 21:13

#include <cmath>
#include <iosfwd>
#include <numbers>
#include <random>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |478. Generate Random Point in a Circle|:
//
// Given the radius and the position of the center of a circle, implement the
// function |randPoint| which generates a uniform random point inside the
// circle. Implement the |Solution| class:
//
//  • |Solution(double radius, double x_center, double y_center)| initializes
//  the object with the radius of the circle |radius| and the position of the
//  center |(x_center, y_center)|.
//
//  • |randPoint()| returns a random point inside the circle. A point on the
//  circumference of the circle is considered to be in the circle. The answer is
//  returned as an array |[x, y]|.
//
//

LEETCODE_BEGIN_RESOLVING(478, GenerateRandomPointInACircle, Solution);

class Solution {
public:
  Solution(double radius, double x_center, double y_center)
      : rd_{}, rng_{rd_()}, rand_{0, 1}, radius_{radius}, center_{x_center,
                                                                  y_center} {}

  vector<double> randPoint() {
    vector<double> ret = center_;
    double         ang = rand_(rng_) * 2 * numbers::pi;
    double         r   = sqrt(rand_(rng_)) * radius_;
    ret[0] += r * cos(ang);
    ret[1] += r * sin(ang);
    return ret;
  }

private:
  random_device                     rd_;
  mt19937                           rng_;
  uniform_real_distribution<double> rand_;
  double                            radius_;
  vector<double>                    center_;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 < radius <= 10⁸|
// * |-10⁷ <= x_center, y_center <= 10⁷|
// * At most |3 * 10⁴| calls will be made to |randPoint|.
///////////////////////////////////////////////////////////////////////////////

static bool CheckIsInCircle(double r, double c_x, double c_y,
                            vector<double> const &p) {
  return pow(p[0] - c_x, 2) + pow(p[1] - c_y, 2) <= r * r;
}

// [Example #1]
//  Input: ["Solution", "randPoint", "randPoint", "randPoint"]
// [[1.0, 0.0, 0.0], [], [], []]
// Output: [null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]
//

LEETCODE_SOLUTION_UNITTEST(478, GenerateRandomPointInACircle, example_1) {
  double s0_radius   = 1.0;
  double s0_x_center = 0.0;
  double s0_y_center = 0.0;
  auto   solution    = MakeSolution(s0_radius, s0_x_center, s0_y_center);
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
}

// [Extra Testcase #1]
//  Input: ["Solution","randPoint","randPoint","randPoint"]
// [[10.0,5.0,-7.5],[],[],[]]
// Output: [null,[-2.30114,-3.02803],[5.39970,-6.76300],[3.58822,1.37507]]
//

LEETCODE_SOLUTION_UNITTEST(478, GenerateRandomPointInACircle,
                           extra_testcase_1) {
  double s0_radius   = 10.0;
  double s0_x_center = 5.0;
  double s0_y_center = -7.5;
  auto   solution    = MakeSolution(s0_radius, s0_x_center, s0_y_center);
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
}

LEETCODE_SOLUTION_UNITTEST(478, GenerateRandomPointInACircle,
                           extra_testcase_2) {
  double s0_radius   = 0.001;
  double s0_x_center = 535436546.30;
  double s0_y_center = -734436.6345;
  auto   solution    = MakeSolution(s0_radius, s0_x_center, s0_y_center);
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
  EXPECT_TRUE(CheckIsInCircle(s0_radius, s0_x_center, s0_y_center,
                              solution->randPoint()));
}
