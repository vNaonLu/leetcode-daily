// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Ways to Divide a Long Corridor
//
// https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/
//
// Question ID: 2147
// Difficult  : Hard
// Solve Date : 2023/11/28 17:42

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2147. Number of Ways to Divide a Long Corridor|:
//
// Along a long library corridor, there is a line of seats and decorative
// plants. You are given a 0-indexed string |corridor| of length |n| consisting
// of letters |'S'| and |'P'| where each |'S'| represents a seat and each |'P'|
// represents a plant. One room divider has already been installed to the left
// of index |0|, and another to the right of index |n - 1|. Additional room
// dividers can be installed. For each position between indices |i - 1| and |i|
// ( |1 <= i <= n - 1|), at most one divider can be installed. Divide the
// corridor into non-overlapping sections, where each section has exactly two
// seats with any number of plants. There may be multiple ways to perform the
// division. Two ways are different if there is a position with a room divider
// installed in the first way but not in the second way. Return the number of
// ways to divide the corridor. Since the answer may be very large, return it
// modulo |10⁹ + 7|. If there is no way, return |0|.
//
//

LEETCODE_BEGIN_RESOLVING(2147, NumberOfWaysToDivideALongCorridor, Solution);

class Solution {
public:
  int numberOfWays(string corridor) {
    int64_t res   = 1;
    int     seat  = 0;
    int     plant = 0;
    for (auto c : corridor) {
      if (c == 'S') {
        ++seat;
      } else if (seat == 2) {
        plant += 1;
      }

      if (seat == 3) {
        res   = (res * (plant + 1)) % kMod;
        seat  = 1;
        plant = 0;
      }
    }

    return seat != 2 ? 0 : res;
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == corridor.length|
// * |1 <= n <= 10⁵|
// * |corridor[i]| is either |'S'| or |'P'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: corridor = "SSPPSPS"
// Output: 3
//
// There are 3 different ways to divide the corridor.
// The black bars in the above image indicate the two room dividers already
// installed. Note that in each of the ways, each section has exactly two seats.

LEETCODE_SOLUTION_UNITTEST(2147, NumberOfWaysToDivideALongCorridor, example_1) {
  auto   solution = MakeSolution();
  string corridor = "SSPPSPS";
  int    expect   = 3;
  int    actual   = solution->numberOfWays(corridor);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: corridor = "PPSPSP"
// Output: 1
//
// There is only 1 way to divide the corridor, by not installing any additional
// dividers. Installing any would create some section that does not have exactly
// two seats.

LEETCODE_SOLUTION_UNITTEST(2147, NumberOfWaysToDivideALongCorridor, example_2) {
  auto   solution = MakeSolution();
  string corridor = "PPSPSP";
  int    expect   = 1;
  int    actual   = solution->numberOfWays(corridor);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: corridor = "S"
// Output: 0
//
// There is no way to divide the corridor because there will always be a section
// that does not have exactly two seats.

LEETCODE_SOLUTION_UNITTEST(2147, NumberOfWaysToDivideALongCorridor, example_3) {
  auto   solution = MakeSolution();
  string corridor = "S";
  int    expect   = 0;
  int    actual   = solution->numberOfWays(corridor);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input:
//  "PPPPPPPSPPPSPPPPSPPPSPPPPPSPPPSPPSPPSPPPPPSPSPPPPPSPPSPPPPPSPPSPPSPPPSPPPPSPPPPSPPPPPSPSPPPPSPSPPPSPPPPSPPPPPSPSPPSPPPPSPPSPPSPPSPPPSPPSPSPPSSSS"
// Output: 18335643
//

LEETCODE_SOLUTION_UNITTEST(2147, NumberOfWaysToDivideALongCorridor,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string corridor = "PPPPPPPSPPPSPPPPSPPPSPPPPPSPPPSPPSPPSPPPPPSPSPPPPPSPPSPPPP"
                    "PSPPSPPSPPPSPPPPSPPPPSPPPPPSPSPPPPSPSPPPSPPPPSPPPPPSPSPPSP"
                    "PPPSPPSPPSPPSPPPSPPSPSPPSSSS";
  int    expect   = 18335643;
  int    actual   = solution->numberOfWays(corridor);
  LCD_EXPECT_EQ(expect, actual);
}
