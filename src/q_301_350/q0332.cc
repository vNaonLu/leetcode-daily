// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reconstruct Itinerary
//
// https://leetcode.com/problems/reconstruct-itinerary/
//
// Question ID: 332
// Difficult  : Hard
// Solve Date : 2023/09/14 20:25

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |332. Reconstruct Itinerary|:
//
// You are given a list of airline |tickets| where |tickets[i] = [fromᵢ, toᵢ]|
// represent the departure and the arrival airports of one flight. Reconstruct
// the itinerary in order and return it. All of the tickets belong to a man who
// departs from |"JFK"|, thus, the itinerary must begin with |"JFK"|. If there
// are multiple valid itineraries, you should return the itinerary that has the
// smallest lexical order when read as a single string.
//
//  • For example, the itinerary |["JFK", "LGA"]| has a smaller lexical order
//  than |["JFK", "LGB"]|.
// You may assume all tickets form at least one valid itinerary. You must use
// all the tickets once and only once.
//
//

LEETCODE_BEGIN_RESOLVING(332, ReconstructItinerary, Solution);

class Solution {
public:
  vector<string> findItinerary(vector<vector<string>> &tickets) {
    unordered_map<string, multiset<string>> adj;
    for (auto &t : tickets) {
      adj[t[0]].insert(t[1]);
    }
    vector<string> res;
    dfs(&adj, &res, "JFK");
    reverse(res.begin(), res.end());
    return res;
  }

private:
  void dfs(unordered_map<string, multiset<string>> *adj, vector<string> *res,
           string s) {
    while ((*adj)[s].size()) {
      string v = *((*adj)[s].begin());
      (*adj)[s].erase((*adj)[s].begin());
      dfs(adj, res, v);
    }
    res->emplace_back(std::move(s));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= tickets.length <= 300|
// * |tickets[i].length == 2|
// * |fromᵢ.length == 3|
// * |toᵢ.length == 3|
// * |fromᵢ| and |toᵢ| consist of uppercase English letters.
// * |fromᵢ != toᵢ|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
// Output: ["JFK","MUC","LHR","SFO","SJC"]
//

LEETCODE_SOLUTION_UNITTEST(332, ReconstructItinerary, example_1) {
  auto                   solution = MakeSolution();
  vector<vector<string>> tickets  = {
      {"MUC", "LHR"},
      {"JFK", "MUC"},
      {"SFO", "SJC"},
      {"LHR", "SFO"}
  };
  vector<string> expect = {"JFK", "MUC", "LHR", "SFO", "SJC"};
  vector<string> actual = solution->findItinerary(tickets);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tickets =
//  [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
// Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
//
// Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but
// it is larger in lexical order.

LEETCODE_SOLUTION_UNITTEST(332, ReconstructItinerary, example_2) {
  auto                   solution = MakeSolution();
  vector<vector<string>> tickets  = {
      {"JFK", "SFO"},
      {"JFK", "ATL"},
      {"SFO", "ATL"},
      {"ATL", "JFK"},
      {"ATL", "SFO"}
  };
  vector<string> expect = {"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"};
  vector<string> actual = solution->findItinerary(tickets);
  LCD_EXPECT_EQ(expect, actual);
}
