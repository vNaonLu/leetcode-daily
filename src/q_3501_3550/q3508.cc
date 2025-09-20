// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Implement Router
//
// https://leetcode.com/problems/implement-router/
//
// Question ID: 3508
// Difficult  : Medium
// Solve Date : 2025/09/20 11:04

#include <deque>
#include <iosfwd>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3508. Implement Router|:
//
//

LEETCODE_BEGIN_RESOLVING(3508, ImplementRouter, Router);

class Router {
public:
  using int3 = array<int, 3>;
  deque<int3>                    q;
  unordered_map<int, deque<int>> byDest;
  unordered_set<long long>       seen;
  size_t                         memoryLimit;

  Router(size_t memoryLimit) : memoryLimit(memoryLimit) {}

  long long pack(int x, int y) { return ((long long)x << 32) | y; }

  bool addPacket(int source, int destination, int timestamp) {
    if (!q.empty() && timestamp == q.back()[0]) {
      long long key = pack(source, destination);
      if (seen.count(key))
        return 0;
    } else
      seen.clear();
    if (q.size() == memoryLimit) {
      auto old = q.front();
      q.pop_front();

      auto &qq = byDest[old[2]];
      if (!qq.empty())
        qq.pop_front();

      if (old[0] == timestamp)
        seen.erase(pack(old[1], old[2]));
    }

    q.push_back({timestamp, source, destination});
    byDest[destination].push_back(timestamp);
    seen.insert(pack(source, destination));
    return 1;
  }

  vector<int> forwardPacket() {
    if (q.empty())
      return {};
    auto x = q.front();
    q.pop_front();

    auto &qq = byDest[x[2]];
    if (!qq.empty())
      qq.pop_front();

    if (q.back()[0] == x[0])
      seen.erase(pack(x[1], x[2]));

    return {x[1], x[2], x[0]};
  }

  int getCount(int destination, int startTime, int endTime) {
    auto &qq  = byDest[destination];
    auto  itL = lower_bound(qq.begin(), qq.end(), startTime);
    auto  itR = upper_bound(qq.begin(), qq.end(), endTime);
    return itR - itL;
  }
};
LEETCODE_END_RESOLVING(Router);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= memoryLimit <= 10⁵|
// * |1 <= source, destination <= 2 * 10⁵|
// * |1 <= timestamp <= 10⁹|
// * |1 <= startTime <= endTime <= 10⁹|
// * At most |10⁵| calls will be made to |addPacket|, |forwardPacket|, and
// |getCount| methods altogether.
// * queries for |addPacket| will be made in increasing order of |timestamp|.
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3508, ImplementRouter, example_1) {
  int  memory_limit = 3;
  auto router       = MakeRouter(memory_limit);
  LCD_EXPECT_EQ(true, router->addPacket(1, 4, 90));
  LCD_EXPECT_EQ(true, router->addPacket(2, 5, 90));
  LCD_EXPECT_EQ(false, router->addPacket(1, 4, 90));
  LCD_EXPECT_EQ(true, router->addPacket(3, 5, 95));
  LCD_EXPECT_EQ(true, router->addPacket(4, 5, 105));
  vector<int> expected_1 = {2, 5, 90};
  LCD_EXPECT_EQ(expected_1, router->forwardPacket());
  LCD_EXPECT_EQ(true, router->addPacket(5, 1, 105));
  LCD_EXPECT_EQ(1, router->getCount(5, 100, 110));
}

LEETCODE_SOLUTION_UNITTEST(3508, ImplementRouter, example_2) {
  int  memory_limit = 2;
  auto router       = MakeRouter(memory_limit);
  LCD_EXPECT_EQ(true, router->addPacket(7, 4, 90));
  vector<int> expected_1 = {7, 4, 90};
  LCD_EXPECT_EQ(expected_1, router->forwardPacket());
  vector<int> expected_2 = {};
  LCD_EXPECT_EQ(expected_2, router->forwardPacket());
}

// [Extra Testcase #1]
//  Input: ["Router","addPacket","getCount"]
// [[3],[1,4,6],[4,1,4]]
// Output: [null,true,0]
//

LEETCODE_SOLUTION_UNITTEST(3508, ImplementRouter, extra_testcase_1) {
  int  s0_memoryLimit = 3;
  auto router         = MakeRouter(s0_memoryLimit);
  int  s1_source      = 1;
  int  s1_destination = 4;
  int  s1_timestamp   = 6;
  bool s1_expect      = true;
  bool s1_actual = router->addPacket(s1_source, s1_destination, s1_timestamp);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_destination = 4;
  int s2_startTime   = 1;
  int s2_endTime     = 4;
  int s2_expect      = 0;
  int s2_actual = router->getCount(s2_destination, s2_startTime, s2_endTime);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
}
