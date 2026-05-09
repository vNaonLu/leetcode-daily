// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Separate Squares I
//
// https://leetcode.com/problems/separate-squares-i/
//
// Question ID: 3453
// Difficult  : Medium
// Solve Date : 2026/01/13 20:03

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3453. Separate Squares I|:
//
// You are given a 2D integer array |squares|. Each |squares[i] = [xᵢ, yᵢ, lᵢ]|
// represents the coordinates of the bottom-left point and the side length of a
// square parallel to the x-axis. Find the minimum y-coordinate value of a
// horizontal line such that the total area of the squares above the line equals
// the total area of the squares below the line. Answers within |10⁻⁵| of the
// actual answer will be accepted. Note: Squares may overlap. Overlapping areas
// should be counted multiple times.
//
//

LEETCODE_BEGIN_RESOLVING(3453, SeparateSquaresI, Solution);

class Solution {
public:
  double separateSquares(vector<vector<int>> &squares) {
    vector<pair<int, int>> S;
    for (auto s : squares) {
      S.push_back({s[1], s[2]});
    }
    sort(S.begin(), S.end());

    double total_area = 0;
    for (auto [_, l] : S) {
      total_area += (double)l * (double)l;
    }

    auto area_below_line = [&](const double &yline) -> double {
      double area = 0;
      for (auto [y, l] : S) {
        if (y > yline)
          break;
        area += min((double)l, yline - y) * l;
      }
      return area;
    };

    double target = total_area / 2;
    double low    = 0;
    double hig    = 1e9;
    while ((hig - low) > 1e-5) {
      double mid = (low + hig) / 2;
      if (area_below_line(mid) < target) {
        low = mid;
      } else {
        hig = mid;
      }
    }
    return low;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= squares.length <= 5 * 10⁴|
// * |squares[i] = [xᵢ, yᵢ, lᵢ]|
// * |squares[i].length == 3|
// * |0 <= xᵢ, yᵢ <= 10⁹|
// * |1 <= lᵢ <= 10⁹|
// * The total area of all the squares will not exceed |10¹²|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: squares = [[0,0,1],[2,2,1]]
// Output: 1.00000
//

LEETCODE_SOLUTION_UNITTEST(3453, SeparateSquaresI, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> squares  = {
      {0, 0, 1},
      {2, 2, 1}
  };
  double expect = 1.00000;
  double actual = solution->separateSquares(squares);
  EXPECT_NEAR(expect, actual, 1e-5);
}

// [Example #2]
//  Input: squares = [[0,0,2],[1,1,1]]
// Output: 1.16667
//

LEETCODE_SOLUTION_UNITTEST(3453, SeparateSquaresI, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> squares  = {
      {0, 0, 2},
      {1, 1, 1}
  };
  double expect = 1.16667;
  double actual = solution->separateSquares(squares);
  EXPECT_NEAR(expect, actual, 1e-5);
}
