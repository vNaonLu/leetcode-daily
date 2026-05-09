// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Separate Squares II
//
// https://leetcode.com/problems/separate-squares-ii/
//
// Question ID: 3454
// Difficult  : Hard
// Solve Date : 2026/01/14 19:11

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3454. Separate Squares II|:
//
// You are given a 2D integer array |squares|. Each |squares[i] = [xᵢ, yᵢ, lᵢ]|
// represents the coordinates of the bottom-left point and the side length of a
// square parallel to the x-axis. Find the minimum y-coordinate value of a
// horizontal line such that the total area covered by squares above the line
// equals the total area covered by squares below the line. Answers within
// |10⁻⁵| of the actual answer will be accepted. Note: Squares may overlap.
// Overlapping areas should be counted only once in this version.
//
//

LEETCODE_BEGIN_RESOLVING(3454, SeparateSquaresII, Solution);

class Solution {
public:
  double separateSquares(vector<vector<int>> &squares) {
    struct Event {
      int y;
      int type;
      int xStart;
      int xEnd;

      bool operator<(const Event &other) const { return y < other.y; }
    };

    struct Strip {
      int    y;
      int    height;
      double unionWidth;
    };

    vector<Event> sweepEvents;
    for (const auto &sq : squares) {
      int x = sq[0];
      int y = sq[1];
      int l = sq[2];
      sweepEvents.push_back({y, 1, x, x + l});
      sweepEvents.push_back({y + l, -1, x, x + l});
    }

    sort(sweepEvents.begin(), sweepEvents.end());

    vector<pair<int, int>> activeIntervals;
    vector<Strip>          processedStrips;
    double                 totalArea = 0;
    int                    prevY     = sweepEvents[0].y;

    for (const auto &event : sweepEvents) {
      if (event.y > prevY) {
        double width  = getUnionWidth(activeIntervals);
        int    height = event.y - prevY;

        if (width > 0) {
          processedStrips.push_back({prevY, height, width});
          totalArea += (double)height * width;
        }
      }

      if (event.type == 1) {
        activeIntervals.push_back({event.xStart, event.xEnd});
      } else {
        for (auto it = activeIntervals.begin(); it != activeIntervals.end();
             ++it) {
          if (it->first == event.xStart && it->second == event.xEnd) {
            activeIntervals.erase(it);
            break;
          }
        }
      }
      prevY = event.y;
    }

    double targetArea      = totalArea / 2.0;
    double accumulatedArea = 0;

    for (const auto &strip : processedStrips) {
      double stripArea = strip.height * strip.unionWidth;

      if (accumulatedArea + stripArea >= targetArea) {
        double areaNeeded = targetArea - accumulatedArea;
        return strip.y + (areaNeeded / strip.unionWidth);
      }
      accumulatedArea += stripArea;
    }

    return 0.0;
  }

private:
  double getUnionWidth(vector<pair<int, int>> intervals) {
    if (intervals.empty())
      return 0;

    sort(intervals.begin(), intervals.end());

    double unionLength = 0;
    double currentEnd  = -1e18;

    for (const auto &interval : intervals) {
      double start = interval.first;
      double end   = interval.second;

      if (start >= currentEnd) {
        unionLength += (end - start);
        currentEnd = end;
      } else if (end > currentEnd) {
        unionLength += (end - currentEnd);
        currentEnd = end;
      }
    }
    return unionLength;
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
// * The total area of all the squares will not exceed |10¹⁵|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: squares = [[0,0,1],[2,2,1]]
// Output: 1.00000
//

LEETCODE_SOLUTION_UNITTEST(3454, SeparateSquaresII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> squares  = {
      {0, 0, 1},
      {2, 2, 1}
  };
  double expect = 1.00000;
  double actual = solution->separateSquares(squares);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: squares = [[0,0,2],[1,1,1]]
// Output: 1.00000
//

LEETCODE_SOLUTION_UNITTEST(3454, SeparateSquaresII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> squares  = {
      {0, 0, 2},
      {1, 1, 1}
  };
  double expect = 1.00000;
  double actual = solution->separateSquares(squares);
  LCD_EXPECT_EQ(expect, actual);
}
