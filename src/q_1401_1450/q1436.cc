// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Destination City
//
// https://leetcode.com/problems/destination-city/
//
// Question ID: 1436
// Difficult  : Easy
// Solve Date : 2023/08/15 17:31

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1436. Destination City|:
//
// You are given the array |paths|, where |paths[i] = [cityAᵢ, cityBᵢ]| means
// there exists a direct path going from |cityAᵢ| to |cityBᵢ|. Return the
// destination city, that is, the city without any path outgoing to another
// city. It is guaranteed that the graph of paths forms a line without any loop,
// therefore, there will be exactly one destination city.
//
//

LEETCODE_BEGIN_RESOLVING(1436, DestinationCity, Solution);

class Solution {
public:
  string destCity(vector<vector<string>> &paths) {
    unordered_map<string, vector<string>> graph;
    for (auto &v : paths) {
      graph[v[0]].emplace_back(v[1]);
      graph[v[1]]; // just emplace.
    }
    for (auto &[from, to] : graph) {
      if (to.empty()) {
        return from;
      }
    }
    return "";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= paths.length <= 100|
// * |paths[i].length == 2|
// * |1 <= cityAᵢ.length, cityBᵢ.length <= 10|
// * |cityAᵢ != cityBᵢ|
// * All strings consist of lowercase and uppercase English letters and the
// space character.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao
//  Paulo"]]
// Output: "Sao Paulo"
//
// Starting at "London" city you will reach "Sao Paulo" city which is the
// destination city. Your trip consist of: "London" -> "New York" -> "Lima" ->
// "Sao Paulo".

LEETCODE_SOLUTION_UNITTEST(1436, DestinationCity, example_1) {
  auto                   solution = MakeSolution();
  vector<vector<string>> paths    = {
      {  "London",  "New York"},
      {"New York",      "Lima"},
      {    "Lima", "Sao Paulo"}
  };
  string expect = "Sao Paulo";
  string actual = solution->destCity(paths);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: paths = [["B","C"],["D","B"],["C","A"]]
// Output: "A"
//
// All possible trips are:
// "D" -> "B" -> "C" -> "A".
// "B" -> "C" -> "A".
// "C" -> "A".
// "A".
// Clearly the destination city is "A".

LEETCODE_SOLUTION_UNITTEST(1436, DestinationCity, example_2) {
  auto                   solution = MakeSolution();
  vector<vector<string>> paths    = {
      {"B", "C"},
      {"D", "B"},
      {"C", "A"}
  };
  string expect = "A";
  string actual = solution->destCity(paths);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: paths = [["A","Z"]]
// Output: "Z"
//

LEETCODE_SOLUTION_UNITTEST(1436, DestinationCity, example_3) {
  auto                   solution = MakeSolution();
  vector<vector<string>> paths    = {
      {"A", "Z"}
  };
  string expect = "Z";
  string actual = solution->destCity(paths);
  LCD_EXPECT_EQ(expect, actual);
}
