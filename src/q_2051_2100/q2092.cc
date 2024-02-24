// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find All People With Secret
//
// https://leetcode.com/problems/find-all-people-with-secret/
//
// Question ID: 2092
// Difficult  : Hard
// Solve Date : 2024/02/24 11:21

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2092. Find All People With Secret|:
//
// You are given an integer |n| indicating there are |n| people numbered from
// |0| to |n - 1|. You are also given a 0-indexed 2D integer array |meetings|
// where |meetings[i] = [xᵢ, yᵢ, timeᵢ]| indicates that person |xᵢ| and person
// |yᵢ| have a meeting at |timeᵢ|. A person may attend multiple meetings at the
// same time. Finally, you are given an integer |firstPerson|. Person |0| has a
// secret and initially shares the secret with a person |firstPerson| at time
// |0|. This secret is then shared every time a meeting takes place with a
// person that has the secret. More formally, for every meeting, if a person
// |xᵢ| has the secret at |timeᵢ|, then they will share the secret with person
// |yᵢ|, and vice versa. The secrets are shared instantaneously. That is, a
// person may receive the secret and share it with people in other meetings
// within the same time frame. Return a list of all the people that have the
// secret after all the meetings have taken place. You may return the answer in
// any order.
//
//

LEETCODE_BEGIN_RESOLVING(2092, FindAllPeopleWithSecret, Solution);

class Solution {
public:
  vector<int> findAllPeople(int n, vector<vector<int>> &meetings,
                            int firstPerson) {
    sort(meetings.begin(), meetings.end(),
         [](auto &a, auto &b) { return a[2] < b[2]; });
    UnionFind uf(n);
    uf.connect(0, firstPerson);
    vector<int> ppl;
    for (int i = 0, M = meetings.size(); i < M;) {
      ppl.clear();
      int time = meetings[i][2];
      for (; i < M && meetings[i][2] == time; ++i) {
        uf.connect(meetings[i][0], meetings[i][1]);
        ppl.emplace_back(meetings[i][0]);
        ppl.emplace_back(meetings[i][1]);
      }
      for (auto x : ppl) {
        if (!uf.connected(0, x)) {
          uf.reset(x);
        }
      }
    }
    vector<int> res;
    for (int i = 0; i < n; ++i) {
      if (uf.connected(0, i)) {
        res.emplace_back(i);
      }
    }
    return res;
  }

private:
  class UnionFind {
  public:
    UnionFind(int n) : id(n) { iota(begin(id), end(id), 0); }
    int  find(int a) { return id[a] == a ? a : (id[a] = find(id[a])); }
    void connect(int a, int b) { id[find(b)] = find(a); }
    bool connected(int a, int b) { return find(a) == find(b); }
    void reset(int a) { id[a] = a; }

  private:
    vector<int> id;
  };
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |1 <= meetings.length <= 10⁵|
// * |meetings[i].length == 3|
// * |0 <= xᵢ, y_{i }<= n - 1|
// * |xᵢ != yᵢ|
// * |1 <= timeᵢ <= 10⁵|
// * |1 <= firstPerson <= n - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
// Output: [0,1,2,3,5]
// Explanation:
// At time 0, person 0 shares the secret with person 1.
// At time 5, person 1 shares the secret with person 2.
// At time 8, person 2 shares the secret with person 3.
// At time 10, person 1 shares the secret with person 5.​​​​
// Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.
//

LEETCODE_SOLUTION_UNITTEST(2092, FindAllPeopleWithSecret, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 6;
  vector<vector<int>> meetings = {
      {1, 2,  5},
      {2, 3,  8},
      {1, 5, 10}
  };
  int         firstPerson = 1;
  vector<int> expect      = {0, 1, 2, 3, 5};
  vector<int> actual      = solution->findAllPeople(n, meetings, firstPerson);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
// Output: [0,1,3]
//
// At time 0, person 0 shares the secret with person 3.
// At time 2, neither person 1 nor person 2 know the secret.
// At time 3, person 3 shares the secret with person 0 and person 1.
// Thus, people 0, 1, and 3 know the secret after all the meetings.

LEETCODE_SOLUTION_UNITTEST(2092, FindAllPeopleWithSecret, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> meetings = {
      {3, 1, 3},
      {1, 2, 2},
      {0, 3, 3}
  };
  int         firstPerson = 3;
  vector<int> expect      = {0, 1, 3};
  vector<int> actual      = solution->findAllPeople(n, meetings, firstPerson);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
// Output: [0,1,2,3,4]
//
// At time 0, person 0 shares the secret with person 1.
// At time 1, person 1 shares the secret with person 2, and person 2 shares the
// secret with person 3. Note that person 2 can share the secret at the same
// time as receiving it. At time 2, person 3 shares the secret with person 4.
// Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.

LEETCODE_SOLUTION_UNITTEST(2092, FindAllPeopleWithSecret, example_3) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> meetings = {
      {3, 4, 2},
      {1, 2, 1},
      {2, 3, 1}
  };
  int         firstPerson = 1;
  vector<int> expect      = {0, 1, 2, 3, 4};
  vector<int> actual      = solution->findAllPeople(n, meetings, firstPerson);
  EXPECT_ANYORDER_EQ(expect, actual);
}
