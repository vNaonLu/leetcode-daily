// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Online Election
//
// https://leetcode.com/problems/online-election/
//
// Question ID: 911
// Difficult  : Medium
// Solve Date : 2022/08/02 18:30

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |911. Online Election|:
//
// You are given two integer arrays |persons| and |times|. In an election, the
// |iᵗʰ| vote was cast for |persons[i]| at time |times[i]|. For each query at a
// time |t|, find the person that was leading the election at time |t|. Votes
// cast at time |t| will count towards our query. In the case of a tie, the most
// recent vote (among tied candidates) wins. Implement the |TopVotedCandidate|
// class:
//
//  • |TopVotedCandidate(int[] persons, int[] times)| Initializes the object
//  with the |persons| and |times| arrays.
//
//  • |int q(int t)| Returns the number of the person that was leading the
//  election at time |t| according to the mentioned rules.
//

LEETCODE_BEGIN_RESOLVING(911, OnlineElection, TopVotedCandidate);

class TopVotedCandidate {
private:
  vector<pair<int, int>> leading; // person, time
public:
  TopVotedCandidate(vector<int> &persons, vector<int> &times) {
    auto cnt    = unordered_map<int, int>();
    auto leader = -1;
    auto curr   = 0;

    for (int i = 0; i < persons.size(); ++i) {
      auto p = persons[i];
      auto t = times[i];

      auto &c = ++cnt[p];

      if (c >= curr) {
        if (p != leader) {
          leader = p;
          leading.emplace_back(leader, t);
        }

        curr = c;
      }
    }
  }

  int q(int t) {
    auto find = upper_bound(leading.begin(), leading.end(), t,
                            [](auto x, auto y) { return x < y.second; });

    return find == leading.begin() ? -1 : (*--find).first;
  }
};

LEETCODE_END_RESOLVING(TopVotedCandidate);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= persons.length <= 5000|
// * |times.length == persons.length|
// * |0 <= persons[i] < persons.length|
// * |0 <= times[i] <= 10⁹|
// * |times| is sorted in a strictly increasing order.
// * |times[0] <= t <= 10⁹|
// * At most |10⁴| calls will be made to |q|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["TopVotedCandidate", "q", "q", "q", "q", "q", "q"]
// [[[0, 1, 1, 0, 0, 1, 0], [0, 5, 10, 15, 20, 25, 30]], [3], [12], [25], [15],
// [24], [8]] Output: [null, 0, 1, 1, 0, 0, 1]
//
// TopVotedCandidate topVotedCandidate = new TopVotedCandidate([0, 1, 1, 0, 0,
// 1, 0], [0, 5, 10, 15, 20, 25, 30]); topVotedCandidate.q(3); // return 0, At
// time 3, the votes are [0], and 0 is leading. topVotedCandidate.q(12); //
// return 1, At time 12, the votes are [0,1,1], and 1 is leading.
// topVotedCandidate.q(25); // return 1, At time 25, the votes are
// [0,1,1,0,0,1], and 1 is leading (as ties go to the most recent vote.)
// topVotedCandidate.q(15); // return 0
// topVotedCandidate.q(24); // return 0
// topVotedCandidate.q(8); // return 1

LEETCODE_SOLUTION_UNITTEST(911, OnlineElection, example_1) {
  vector<int> s0_persons          = {0, 1, 1, 0, 0, 1, 0};
  vector<int> s0_times            = {0, 5, 10, 15, 20, 25, 30};
  auto        top_voted_candidate = MakeTopVotedCandidate(s0_persons, s0_times);
  int         s1_t                = 3;
  int         s1_expect           = 0;
  int         s1_actual           = top_voted_candidate->q(s1_t);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_t      = 12;
  int s2_expect = 1;
  int s2_actual = top_voted_candidate->q(s2_t);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_t      = 25;
  int s3_expect = 1;
  int s3_actual = top_voted_candidate->q(s3_t);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_t      = 15;
  int s4_expect = 0;
  int s4_actual = top_voted_candidate->q(s4_t);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_t      = 24;
  int s5_expect = 0;
  int s5_actual = top_voted_candidate->q(s5_t);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_t      = 8;
  int s6_expect = 1;
  int s6_actual = top_voted_candidate->q(s6_t);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
