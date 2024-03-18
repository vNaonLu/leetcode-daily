// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Mini Parser
//
// https://leetcode.com/problems/mini-parser/
//
// Question ID: 385
// Difficult  : Medium
// Solve Date : 2024/03/15 21:07

#include <algorithm>
#include <cctype>
#include <iosfwd>
#include <optional>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |385. Mini Parser|:
//
// Given a string s represents the serialization of a nested list, implement a
// parser to deserialize it and return the deserialized |NestedInteger|. Each
// element is either an integer or a list whose elements may also be integers or
// other lists.
//
//

namespace {
class NestedInteger {
public:
  NestedInteger() : val{nullopt} {}
  NestedInteger(int value) : val{value} {}
  bool isInteger() const { return val != nullopt; }
  int  getInteger() const { return *val; }
  void setInteger(int value) { val = value; }
  void add(const NestedInteger &ni) { v.emplace_back(ni); }
  const vector<NestedInteger> &getList() const { return v; }

private:
  vector<NestedInteger> v;
  optional<int>         val;
};
} // namespace

LEETCODE_BEGIN_RESOLVING(385, MiniParser, Solution);

class Solution {
public:
  NestedInteger deserialize(string s) {
    stack<NestedInteger> res;
    res.emplace(NestedInteger());
    for (auto it = s.begin(); it != s.end();) {
      if (isNumber(*it)) {
        auto end = find_if_not(it, s.end(), isNumber);
        res.top().add(NestedInteger(stoi(string(it, end))));
        it = end;
      } else {
        if (*it == '[') {
          res.emplace(NestedInteger());
        } else if (*it == ']') {
          NestedInteger ni = std::move(res.top());
          res.pop();
          res.top().add(std::move(ni));
        }
        ++it;
      }
    }
    return res.top().getList().front();
  }

private:
  static bool isNumber(char c) { return c == '-' || isdigit(c); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 5 * 10⁴|
// * |s| consists of digits, square brackets |"[]"|, negative sign |'-'|, and
// commas |','|.
// * |s| is the serialization of valid |NestedInteger|.
// * All the values in the input are in the range |[-10⁶, 10⁶]|.
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(385, MiniParser, example_1) {
  auto          solution = MakeSolution();
  string        s        = "324";
  NestedInteger actual   = solution->deserialize(s);
  ASSERT_TRUE(actual.isInteger());
  EXPECT_EQ(actual.getInteger(), 324);
}

LEETCODE_SOLUTION_UNITTEST(385, MiniParser, example_2) {
  auto          solution = MakeSolution();
  string        s        = "[123,[456,[789]]]";
  NestedInteger actual   = solution->deserialize(s);
  ASSERT_TRUE(!actual.isInteger());
  auto &v1 = actual.getList();
  ASSERT_EQ(v1.size(), 2);
  ASSERT_TRUE(v1[0].isInteger());
  EXPECT_EQ(v1[0].getInteger(), 123);
  ASSERT_TRUE(!v1[1].isInteger());
  auto &v2 = v1[1].getList();
  ASSERT_EQ(v2.size(), 2);
  ASSERT_TRUE(v2[0].isInteger());
  EXPECT_EQ(v2[0].getInteger(), 456);
  ASSERT_TRUE(!v2[1].isInteger());
  auto &v3 = v2[1].getList();
  ASSERT_EQ(v3.size(), 1);
  ASSERT_TRUE(v3[0].isInteger());
  EXPECT_EQ(v3[0].getInteger(), 789);
}
