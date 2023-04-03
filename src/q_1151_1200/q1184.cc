// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Distance Between Bus Stops
//
// https://leetcode.com/problems/distance-between-bus-stops/
//
// Question ID: 1184
// Difficult  : Easy
// Solve Date : 2023/03/28 19:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1184. Distance Between Bus Stops|:
//
// A bus has |n| stops numbered from |0| to |n - 1| that form a circle. We know
// the distance between all pairs of neighboring stops where |distance[i]| is
// the distance between the stops number |i| and |(i + 1) % n|.
//
// The bus goes along both directions i.e. clockwise and counterclockwise.
//
// Return the shortest distance between the given |start| and |destination|
// stops.
//
//
//

LEETCODE_BEGIN_RESOLVING(1184, DistanceBetweenBusStops, Solution);

class Solution {
public:
  int distanceBetweenBusStops(vector<int> &distance, int start,
                              int destination) {
    vector<int> sum(distance.size() + 1, 0);
    if (start > destination) {
      swap(start, destination);
    }
    for (int i = 1; i < sum.size(); ++i) {
      sum[i] = distance[i - 1] + sum[i - 1];
    }
    return min(sum[destination] - sum[start],
               sum.back() - sum[destination] + sum[start]);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10^4|
// * |distance.length == n|
// * |0 <= start, destination < n|
// * |0 <= distance[i] <= 10^4|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: distance = [1,2,3,4], start = 0, destination = 1
// Output: 1
//
// Distance between 0 and 1 is 1 or 9, minimum is 1.

LEETCODE_SOLUTION_UNITTEST(1184, DistanceBetweenBusStops, example_1) {
  auto        solution    = MakeSolution();
  vector<int> distance    = {1, 2, 3, 4};
  int         start       = 0;
  int         destination = 1;
  int         expect      = 1;
  int actual = solution->distanceBetweenBusStops(distance, start, destination);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: distance = [1,2,3,4], start = 0, destination = 2
// Output: 3
//
// Distance between 0 and 2 is 3 or 7, minimum is 3.

LEETCODE_SOLUTION_UNITTEST(1184, DistanceBetweenBusStops, example_2) {
  auto        solution    = MakeSolution();
  vector<int> distance    = {1, 2, 3, 4};
  int         start       = 0;
  int         destination = 2;
  int         expect      = 3;
  int actual = solution->distanceBetweenBusStops(distance, start, destination);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: distance = [1,2,3,4], start = 0, destination = 3
// Output: 4
//
// Distance between 0 and 3 is 6 or 4, minimum is 4.

LEETCODE_SOLUTION_UNITTEST(1184, DistanceBetweenBusStops, example_3) {
  auto        solution    = MakeSolution();
  vector<int> distance    = {1, 2, 3, 4};
  int         start       = 0;
  int         destination = 3;
  int         expect      = 4;
  int actual = solution->distanceBetweenBusStops(distance, start, destination);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [7,10,1,12,11,14,5,0]
// 7
// 2
// Output: 17
//

LEETCODE_SOLUTION_UNITTEST(1184, DistanceBetweenBusStops, extra_testcase_1) {
  auto        solution    = MakeSolution();
  vector<int> distance    = {7, 10, 1, 12, 11, 14, 5, 0};
  int         start       = 7;
  int         destination = 2;
  int         expect      = 17;
  int actual = solution->distanceBetweenBusStops(distance, start, destination);
  LCD_EXPECT_EQ(expect, actual);
}
