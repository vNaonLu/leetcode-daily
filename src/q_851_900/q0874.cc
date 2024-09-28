// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Walking Robot Simulation
//
// https://leetcode.com/problems/walking-robot-simulation/
//
// Question ID: 874
// Difficult  : Medium
// Solve Date : 2024/09/04 21:03

#include <iosfwd>
#include <set>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |874. Walking Robot Simulation|:
//
// A robot on an infinite XY-plane starts at point |(0, 0)| facing north. The
// robot can receive a sequence of these three possible types of |commands|:
//
//  • |-2|: Turn left |90| degrees.
//
//  • |-1|: Turn right |90| degrees.
//
//  • |1 <= k <= 9|: Move forward |k| units, one unit at a time.
// Some of the grid squares are |obstacles|. The |iᵗʰ| obstacle is at grid point
// |obstacles[i] = (xᵢ, yᵢ)|. If the robot runs into an obstacle, then it will
// instead stay in its current location and move on to the next command. Return
// the maximum Euclidean distance that the robot ever gets from the origin
// squared (i.e. if the distance is |5|, return |25|). Note:
//
//  • North means +Y direction.
//
//  • East means +X direction.
//
//  • South means -Y direction.
//
//  • West means -X direction.
//
//  • There can be obstacle in [0,0].
//
//

LEETCODE_BEGIN_RESOLVING(874, WalkingRobotSimulation, Solution);

class Solution {
public:
  int robotSim(vector<int> &commands, vector<vector<int>> &obstacles) {
    unordered_map<int, set<int>> xobs;
    unordered_map<int, set<int>> yobs;
    pair<int, int>               dir{0, 1};
    pair<int, int>               pos{0, 0};
    int                          res = 0;
    for (auto &v : obstacles) {
      xobs[v[0]].emplace(v[1]);
      yobs[v[1]].emplace(v[0]);
    }
    for (auto x : commands) {
      if (x == -1) {
        turnRight(&dir);
      } else if (x == -2) {
        turnLeft(&dir);
      } else {
        if (dir.first) {
          int  dx = dir.first * x + pos.first;
          auto it = yobs.find(pos.second);
          if (it != yobs.end()) {
            pos.first = advanceTo(pos.first, dx, it->second);
          } else {
            pos.first = dx;
          }
        } else {
          int  dy = dir.second * x + pos.second;
          auto it = xobs.find(pos.first);
          if (it != xobs.end()) {
            pos.second = advanceTo(pos.second, dy, it->second);
          } else {
            pos.second = dy;
          }
        }
      }
      res = max(res, pos.first * pos.first + pos.second * pos.second);
    }

    return res;
  }

private:
  void turnLeft(pair<int, int> *d) {
    auto x    = d->first;
    auto y    = d->second;
    d->first  = -y;
    d->second = x;
  }
  void turnRight(pair<int, int> *d) {
    auto x    = d->first;
    auto y    = d->second;
    d->first  = y;
    d->second = -x;
  }
  int advanceTo(int before, int after, set<int> const &o) {
    if (before < after) {
      auto beg = o.upper_bound(before);
      auto end = o.upper_bound(after);
      if (beg == end || end == o.begin() || *--end == before) {
        return after;
      } else {
        return *end - 1;
      }
    } else {
      auto beg = o.lower_bound(before);
      auto end = o.lower_bound(after);
      if (beg == end || beg == o.begin() || *--beg == before) {
        return after;
      } else {
        return *beg + 1;
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= commands.length <= 10⁴|
// * |commands[i]| is either |-2|, |-1|, or an integer in the range |[1, 9]|.
// * |0 <= obstacles.length <= 10⁴|
// * |-3 * 10⁴ <= xᵢ, yᵢ <= 3 * 10⁴|
// * The answer is guaranteed to be less than |2³¹|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: commands = [4,-1,3], obstacles = []
// Output: 25
//

LEETCODE_SOLUTION_UNITTEST(874, WalkingRobotSimulation, example_1) {
  auto                solution  = MakeSolution();
  vector<int>         commands  = {4, -1, 3};
  vector<vector<int>> obstacles = {};
  int                 expect    = 25;
  int                 actual    = solution->robotSim(commands, obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
// Output: 65
//

LEETCODE_SOLUTION_UNITTEST(874, WalkingRobotSimulation, example_2) {
  auto                solution  = MakeSolution();
  vector<int>         commands  = {4, -1, 4, -2, 4};
  vector<vector<int>> obstacles = {
      {2, 4}
  };
  int expect = 65;
  int actual = solution->robotSim(commands, obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: commands = [6,-1,-1,6], obstacles = []
// Output: 36
//

LEETCODE_SOLUTION_UNITTEST(874, WalkingRobotSimulation, example_3) {
  auto                solution  = MakeSolution();
  vector<int>         commands  = {6, -1, -1, 6};
  vector<vector<int>> obstacles = {};
  int                 expect    = 36;
  int                 actual    = solution->robotSim(commands, obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [7,-2,-2,7,5]
// [[-3,2],[-2,1],[0,1],[-2,4],[-1,0],[-2,-3],[0,-3],[4,4],[-3,3],[2,2]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(874, WalkingRobotSimulation, extra_testcase_1) {
  auto                solution  = MakeSolution();
  vector<int>         commands  = {7, -2, -2, 7, 5};
  vector<vector<int>> obstacles = {
      {-3,  2},
      {-2,  1},
      { 0,  1},
      {-2,  4},
      {-1,  0},
      {-2, -3},
      { 0, -3},
      { 4,  4},
      {-3,  3},
      { 2,  2}
  };
  int expect = 4;
  int actual = solution->robotSim(commands, obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [2,2,5,-1,-1]
// [[-3,5],[-2,5],[3,2],[5,0],[-2,0],[-1,5],[5,-3],[0,0],[-4,4],[-3,4]]
// Output: 81
//

LEETCODE_SOLUTION_UNITTEST(874, WalkingRobotSimulation, extra_testcase_2) {
  auto                solution  = MakeSolution();
  vector<int>         commands  = {2, 2, 5, -1, -1};
  vector<vector<int>> obstacles = {
      {-3,  5},
      {-2,  5},
      { 3,  2},
      { 5,  0},
      {-2,  0},
      {-1,  5},
      { 5, -3},
      { 0,  0},
      {-4,  4},
      {-3,  4}
  };
  int expect = 81;
  int actual = solution->robotSim(commands, obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #3]
//  Input:
//  [1,2,-2,5,-1,-2,-1,8,3,-1,9,4,-2,3,2,4,3,9,2,-1,-1,-2,1,3,-2,4,1,4,-1,1,9,-1,-2,5,-1,5,5,-2,6,6,7,7,2,8,9,-1,7,4,6,9,9,9,-1,5,1,3,3,-1,5,9,7,4,8,-1,-2,1,3,2,9,3,-1,-2,8,8,7,5,-2,6,8,4,6,2,7,2,-1,7,-2,3,3,2,-2,6,9,8,1,-2,-1,1,4,7]
// [[-57,-58],[-72,91],[-55,35],[-20,29],[51,70],[-61,88],[-62,99],[52,17],[-75,-32],[91,-22],[54,33],[-45,-59],[47,-48],[53,-98],[-91,83],[81,12],[-34,-90],[-79,-82],[-15,-86],[-24,66],[-35,35],[3,31],[87,93],[2,-19],[87,-93],[24,-10],[84,-53],[86,87],[-88,-18],[-51,89],[96,66],[-77,-94],[-39,-1],[89,51],[-23,-72],[27,24],[53,-80],[52,-33],[32,4],[78,-55],[-25,18],[-23,47],[79,-5],[-23,-22],[14,-25],[-11,69],[63,36],[35,-99],[-24,82],[-29,-98],[-50,-70],[72,95],[80,80],[-68,-40],[65,70],[-92,78],[-45,-63],[1,34],[81,50],[14,91],[-77,-54],[13,-88],[24,37],[-12,59],[-48,-62],[57,-22],[-8,85],[48,71],[12,1],[-20,36],[-32,-14],[39,46],[-41,75],[13,-23],[98,10],[-88,64],[50,37],[-95,-32],[46,-91],[10,79],[-11,43],[-94,98],[79,42],[51,71],[4,-30],[2,74],[4,10],[61,98],[57,98],[46,43],[-16,72],[53,-69],[54,-96],[22,0],[-7,92],[-69,80],[68,-73],[-24,-92],[-21,82],[32,-1],[-6,16],[15,-29],[70,-66],[-85,80],[50,-3],[6,13],[-30,-98],[-30,59],[-67,40],[17,72],[79,82],[89,-100],[2,79],[-95,-46],[17,68],[-46,81],[-5,-57],[7,58],[-42,68],[19,-95],[-17,-76],[81,-86],[79,78],[-82,-67],[6,0],[35,-16],[98,83],[-81,100],[-11,46],[-21,-38],[-30,-41],[86,18],[-68,6],[80,75],[-96,-44],[-19,66],[21,84],[-56,-64],[39,-15],[0,45],[-81,-54],[-66,-93],[-4,2],[-42,-67],[-15,-33],[1,-32],[-74,-24],[7,18],[-62,84],[19,61],[39,79],[60,-98],[-76,45],[58,-98],[33,26],[-74,-95],[22,30],[-68,-62],[-59,4],[-62,35],[-78,80],[-82,54],[-42,81],[56,-15],[32,-19],[34,93],[57,-100],[-1,-87],[68,-26],[18,86],[-55,-19],[-68,-99],[-9,47],[24,94],[92,97],[5,67],[97,-71],[63,-57],[-52,-14],[-86,-78],[-17,92],[-61,-83],[-84,-10],[20,13],[-68,-47],[7,28],[66,89],[-41,-17],[-14,-46],[-72,-91],[4,52],[-17,-59],[-85,-46],[-94,-23],[-48,-3],[-64,-37],[2,26],[76,88],[-8,-46],[-19,-68]]
// Output: 5140
//

LEETCODE_SOLUTION_UNITTEST(874, WalkingRobotSimulation, extra_testcase_3) {
  auto        solution = MakeSolution();
  vector<int> commands = {
      1,  2,  -2, 5,  -1, -2, -1, 8,  3,  -1, 9,  4,  -2, 3,  2,  4,  3,
      9,  2,  -1, -1, -2, 1,  3,  -2, 4,  1,  4,  -1, 1,  9,  -1, -2, 5,
      -1, 5,  5,  -2, 6,  6,  7,  7,  2,  8,  9,  -1, 7,  4,  6,  9,  9,
      9,  -1, 5,  1,  3,  3,  -1, 5,  9,  7,  4,  8,  -1, -2, 1,  3,  2,
      9,  3,  -1, -2, 8,  8,  7,  5,  -2, 6,  8,  4,  6,  2,  7,  2,  -1,
      7,  -2, 3,  3,  2,  -2, 6,  9,  8,  1,  -2, -1, 1,  4,  7};
  vector<vector<int>> obstacles = {
      {-57,  -58},
      {-72,   91},
      {-55,   35},
      {-20,   29},
      { 51,   70},
      {-61,   88},
      {-62,   99},
      { 52,   17},
      {-75,  -32},
      { 91,  -22},
      { 54,   33},
      {-45,  -59},
      { 47,  -48},
      { 53,  -98},
      {-91,   83},
      { 81,   12},
      {-34,  -90},
      {-79,  -82},
      {-15,  -86},
      {-24,   66},
      {-35,   35},
      {  3,   31},
      { 87,   93},
      {  2,  -19},
      { 87,  -93},
      { 24,  -10},
      { 84,  -53},
      { 86,   87},
      {-88,  -18},
      {-51,   89},
      { 96,   66},
      {-77,  -94},
      {-39,   -1},
      { 89,   51},
      {-23,  -72},
      { 27,   24},
      { 53,  -80},
      { 52,  -33},
      { 32,    4},
      { 78,  -55},
      {-25,   18},
      {-23,   47},
      { 79,   -5},
      {-23,  -22},
      { 14,  -25},
      {-11,   69},
      { 63,   36},
      { 35,  -99},
      {-24,   82},
      {-29,  -98},
      {-50,  -70},
      { 72,   95},
      { 80,   80},
      {-68,  -40},
      { 65,   70},
      {-92,   78},
      {-45,  -63},
      {  1,   34},
      { 81,   50},
      { 14,   91},
      {-77,  -54},
      { 13,  -88},
      { 24,   37},
      {-12,   59},
      {-48,  -62},
      { 57,  -22},
      { -8,   85},
      { 48,   71},
      { 12,    1},
      {-20,   36},
      {-32,  -14},
      { 39,   46},
      {-41,   75},
      { 13,  -23},
      { 98,   10},
      {-88,   64},
      { 50,   37},
      {-95,  -32},
      { 46,  -91},
      { 10,   79},
      {-11,   43},
      {-94,   98},
      { 79,   42},
      { 51,   71},
      {  4,  -30},
      {  2,   74},
      {  4,   10},
      { 61,   98},
      { 57,   98},
      { 46,   43},
      {-16,   72},
      { 53,  -69},
      { 54,  -96},
      { 22,    0},
      { -7,   92},
      {-69,   80},
      { 68,  -73},
      {-24,  -92},
      {-21,   82},
      { 32,   -1},
      { -6,   16},
      { 15,  -29},
      { 70,  -66},
      {-85,   80},
      { 50,   -3},
      {  6,   13},
      {-30,  -98},
      {-30,   59},
      {-67,   40},
      { 17,   72},
      { 79,   82},
      { 89, -100},
      {  2,   79},
      {-95,  -46},
      { 17,   68},
      {-46,   81},
      { -5,  -57},
      {  7,   58},
      {-42,   68},
      { 19,  -95},
      {-17,  -76},
      { 81,  -86},
      { 79,   78},
      {-82,  -67},
      {  6,    0},
      { 35,  -16},
      { 98,   83},
      {-81,  100},
      {-11,   46},
      {-21,  -38},
      {-30,  -41},
      { 86,   18},
      {-68,    6},
      { 80,   75},
      {-96,  -44},
      {-19,   66},
      { 21,   84},
      {-56,  -64},
      { 39,  -15},
      {  0,   45},
      {-81,  -54},
      {-66,  -93},
      { -4,    2},
      {-42,  -67},
      {-15,  -33},
      {  1,  -32},
      {-74,  -24},
      {  7,   18},
      {-62,   84},
      { 19,   61},
      { 39,   79},
      { 60,  -98},
      {-76,   45},
      { 58,  -98},
      { 33,   26},
      {-74,  -95},
      { 22,   30},
      {-68,  -62},
      {-59,    4},
      {-62,   35},
      {-78,   80},
      {-82,   54},
      {-42,   81},
      { 56,  -15},
      { 32,  -19},
      { 34,   93},
      { 57, -100},
      { -1,  -87},
      { 68,  -26},
      { 18,   86},
      {-55,  -19},
      {-68,  -99},
      { -9,   47},
      { 24,   94},
      { 92,   97},
      {  5,   67},
      { 97,  -71},
      { 63,  -57},
      {-52,  -14},
      {-86,  -78},
      {-17,   92},
      {-61,  -83},
      {-84,  -10},
      { 20,   13},
      {-68,  -47},
      {  7,   28},
      { 66,   89},
      {-41,  -17},
      {-14,  -46},
      {-72,  -91},
      {  4,   52},
      {-17,  -59},
      {-85,  -46},
      {-94,  -23},
      {-48,   -3},
      {-64,  -37},
      {  2,   26},
      { 76,   88},
      { -8,  -46},
      {-19,  -68}
  };
  int expect = 5140;
  int actual = solution->robotSim(commands, obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #4]
//  Input: [-2,-1,-2,3,7]
// [[1,-3],[2,-3],[4,0],[-2,5],[-5,2],[0,0],[4,-4],[-2,-5],[-1,-2],[0,2]]
// Output: 100
//

LEETCODE_SOLUTION_UNITTEST(874, WalkingRobotSimulation, extra_testcase_4) {
  auto                solution  = MakeSolution();
  vector<int>         commands  = {-2, -1, -2, 3, 7};
  vector<vector<int>> obstacles = {
      { 1, -3},
      { 2, -3},
      { 4,  0},
      {-2,  5},
      {-5,  2},
      { 0,  0},
      { 4, -4},
      {-2, -5},
      {-1, -2},
      { 0,  2}
  };
  int expect = 100;
  int actual = solution->robotSim(commands, obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #5]
//  Input: [1,-1,1,-1,1,-1,6]
// [[0,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(874, WalkingRobotSimulation, extra_testcase_5) {
  auto                solution  = MakeSolution();
  vector<int>         commands  = {1, -1, 1, -1, 1, -1, 6};
  vector<vector<int>> obstacles = {
      {0, 0}
  };
  int expect = 2;
  int actual = solution->robotSim(commands, obstacles);
  LCD_EXPECT_EQ(expect, actual);
}
