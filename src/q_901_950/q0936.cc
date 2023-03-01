// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Stamping The Sequence
//
// https://leetcode.com/problems/stamping-the-sequence/
//
// Question ID: 936
// Difficult  : Hard
// Solve Date : 2022/08/21 14:48

#include <iosfwd>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |936. Stamping The Sequence|:
//
// You are given two strings |stamp| and |target|. Initially, there is a string
// |s| of length |target.length| with all |s[i] == '?'|. In one turn, you can
// place |stamp| over |s| and replace every letter in the |s| with the
// corresponding letter from |stamp|.
//
//  • For example, if |stamp = "abc"| and |target = "abcba"|, then |s| is
//  |"?????"| initially. In one turn you can:
//
//
//    • place |stamp| at index |0| of |s| to obtain |"abc??"|,
//
//    • place |stamp| at index |1| of |s| to obtain |"?abc?"|, or
//
//    • place |stamp| at index |2| of |s| to obtain |"??abc"|.
//
// 	Note that |stamp| must be fully contained in the boundaries of |s| in
// order to stamp (i.e., you cannot place |stamp| at index |3| of |s|). We want
// to convert |s| to |target| using at most |10 * target.length| turns. Return
// an array of the index of the left-most letter being stamped at each turn. If
// we cannot obtain |target| from |s| within |10 * target.length| turns, return
// an empty array.
//

LEETCODE_BEGIN_RESOLVING(936, StampingTheSequence, Solution);

class Solution {
private:
  struct Node {
    unordered_set<int> made, todo;
  };

public:
  vector<int> movesToStamp(string stamp, string target) {
    auto m    = static_cast<int>(stamp.size());
    auto n    = static_cast<int>(target.size());
    auto q    = queue<int>();
    auto done = vector<bool>(n, false);
    auto res  = vector<int>();
    auto lst  = vector<Node>();

    for (int i = 0; i <= n - m; ++i) {
      auto made = unordered_set<int>();
      auto todo = unordered_set<int>();

      for (int j = 0; j < m; ++j) {
        if (target[i + j] == stamp[j]) {
          made.emplace(i + j);
        } else {
          todo.emplace(i + j);
        }
      }

      if (todo.empty()) {
        res.emplace_back(i);
        for (int j = i; j < i + m; ++j) {
          if (!done[j]) {
            q.emplace(j);
            done[j] = true;
          }
        }
      }
      lst.emplace_back(Node{move(made), move(todo)});
    }

    while (!q.empty()) {
      auto i = q.front();
      q.pop();

      for (int j = max(i - m + 1, 0); j <= min(n - m, i); ++j) {
        auto &node = lst[j];
        auto &todo = node.todo;

        auto find = todo.find(i);
        if (find != todo.end()) {
          todo.erase(find);
          if (todo.empty()) {
            res.emplace_back(j);
            for (auto x : node.made) {
              if (!done[x]) {
                q.emplace(x);
                done[x] = true;
              }
            }
          }
        }
      }
    }

    for (auto b : done) {
      if (!b) {
        return vector<int>();
      }
    }

    reverse(res.begin(), res.end());

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= stamp.length <= target.length <= 1000|
// * |stamp| and |target| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: stamp = "abc", target = "ababc"
// Output: [0,2]
//
// Initially s = "?????".
// - Place stamp at index 0 to get "abc??".
// - Place stamp at index 2 to get "ababc".
// [1,0,2] would also be accepted as an answer, as well as some other answers.

LEETCODE_SOLUTION_UNITTEST(936, StampingTheSequence, example_1) {
  auto        solution = MakeSolution();
  string      stamp    = "abc";
  string      target   = "ababc";
  vector<int> expect   = {1, 0, 2};
  vector<int> actual   = solution->movesToStamp(stamp, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: stamp = "abca", target = "aabcaca"
// Output: [3,0,1]
//
// Initially s = "???????".
// - Place stamp at index 3 to get "???abca".
// - Place stamp at index 0 to get "abcabca".
// - Place stamp at index 1 to get "aabcaca".

LEETCODE_SOLUTION_UNITTEST(936, StampingTheSequence, example_2) {
  auto        solution = MakeSolution();
  string      stamp    = "abca";
  string      target   = "aabcaca";
  vector<int> expect   = {2, 3, 0, 1};
  vector<int> actual   = solution->movesToStamp(stamp, target);
  LCD_EXPECT_EQ(expect, actual);
}
