// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Accounts Merge
//
// https://leetcode.com/problems/accounts-merge/
//
// Question ID: 721
// Difficult  : Medium
// Solve Date : 2021/11/29 18:07

#include <algorithm>
#include <iosfwd>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |721. Accounts Merge|:
//
// Given a list of |accounts| where each element |accounts[i]| is a list of
// strings, where the first element |accounts[i][0]| is a name, and the rest of
// the elements are emails representing emails of the account. Now, we would
// like to merge these accounts. Two accounts definitely belong to the same
// person if there is some common email to both accounts. Note that even if two
// accounts have the same name, they may belong to different people as people
// could have the same name. A person can have any number of accounts initially,
// but all of their accounts definitely have the same name. After merging the
// accounts, return the accounts in the following format: the first element of
// each account is the name, and the rest of the elements are emails in sorted
// order. The accounts themselves can be returned in any order.  
//

LEETCODE_BEGIN_RESOLVING(721, AccountsMerge, Solution);

class Solution {
private:
  int find(int x, vector<int> &parent) {
    while (x != parent[x]) {
      parent[x] = parent[parent[x]];
      x         = parent[x];
    }
    return x;
  }
  void merge(int x, int y, vector<int> &parent) {
    int parX     = find(x, parent);
    int parY     = find(y, parent);
    parent[parY] = parX;
  }

public:
  vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
    int                        sz = accounts.size();
    unordered_map<string, int> isEmailPresent;
    vector<int>                parent(sz, 0);
    for (int i = 0; i < sz; i++) {
      parent[i] = i;
    }
    for (int id = 0; id < sz; id++) {
      int listSize = accounts[id].size();
      for (int j = 1; j < listSize; j++) {
        string email = accounts[id][j];
        if (isEmailPresent.find(email) != isEmailPresent.end()) {
          int accountID = isEmailPresent[email];
          merge(accountID, id, parent);
        } else {
          isEmailPresent[email] = id;
        }
      }
    }
    unordered_map<int, vector<int>>           mergedAccounts;
    unordered_map<int, vector<int>>::iterator itr;
    vector<vector<string>>                    answer;
    for (int i = 0; i < sz; i++) {
      mergedAccounts[find(i, parent)].push_back(i);
    }
    for (itr = mergedAccounts.begin(); itr != mergedAccounts.end(); itr++) {
      vector<int> allAccounts = itr->second;
      set<string> tmpSet;
      for (int j = 0; j < allAccounts.size(); j++) {
        int id = allAccounts[j];
        for (int i = 1; i < accounts[id].size(); i++) {
          tmpSet.insert(accounts[id][i]);
        }
      }
      vector<string> tmpAns;
      string         accountName = accounts[allAccounts[0]][0];
      tmpAns.push_back(accountName);
      set<string>::iterator itr = tmpSet.begin();
      while (itr != tmpSet.end()) {
        tmpAns.push_back(*itr);
        itr++;
      }
      sort(tmpAns.begin() + 1, tmpAns.end());
      answer.push_back(tmpAns);
    }
    return answer;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= accounts.length <= 1000|
// * |2 <= accounts[i].length <= 10|
// * |1 <= accounts[i][j].length <= 30|
// * |accounts[i][0]| consists of English letters.
// * |accounts[i][j] (for j > 0)| is a valid email.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: accounts =
//  [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
// Output:
// [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
//
// The first and second John's are the same person as they have the common email
// "johnsmith@mail.com". The third John and Mary are different people as none of
// their email addresses are used by other accounts. We could return these lists
// in any order, for example the answer [['Mary', 'mary@mail.com'], ['John',
// 'johnnybravo@mail.com'],
// ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']]
// would still be accepted.

LEETCODE_SOLUTION_UNITTEST(721, AccountsMerge, example_1) {
  auto                   solution = MakeSolution();
  vector<vector<string>> accounts = {
      {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
      {"John", "johnsmith@mail.com", "john00@mail.com"},
      {"Mary", "mary@mail.com"},
      {"John", "johnnybravo@mail.com"}
  };
  vector<vector<string>> expect = {
      {"John", "john00@mail.com", "john_newyork@mail.com",
       "johnsmith@mail.com"},
      {"Mary", "mary@mail.com"},
      {"John", "johnnybravo@mail.com"}
  };
  vector<vector<string>> actual = solution->accountsMerge(accounts);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: accounts =
//  [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
// Output:
// [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]
//

LEETCODE_SOLUTION_UNITTEST(721, AccountsMerge, example_2) {
  auto                   solution = MakeSolution();
  vector<vector<string>> accounts = {
      { "Gabe",  "Gabe0@m.co",  "Gabe3@m.co",  "Gabe1@m.co"},
      {"Kevin", "Kevin3@m.co", "Kevin5@m.co", "Kevin0@m.co"},
      {"Ethan", "Ethan5@m.co", "Ethan4@m.co", "Ethan0@m.co"},
      {"Hanzo", "Hanzo3@m.co", "Hanzo1@m.co", "Hanzo0@m.co"},
      { "Fern",  "Fern5@m.co",  "Fern1@m.co",  "Fern0@m.co"}
  };
  vector<vector<string>> expect = {
      {"Ethan", "Ethan0@m.co", "Ethan4@m.co", "Ethan5@m.co"},
      { "Gabe",  "Gabe0@m.co",  "Gabe1@m.co",  "Gabe3@m.co"},
      {"Hanzo", "Hanzo0@m.co", "Hanzo1@m.co", "Hanzo3@m.co"},
      {"Kevin", "Kevin0@m.co", "Kevin3@m.co", "Kevin5@m.co"},
      { "Fern",  "Fern0@m.co",  "Fern1@m.co",  "Fern5@m.co"}
  };
  vector<vector<string>> actual = solution->accountsMerge(accounts);
  EXPECT_ANYORDER_EQ(expect, actual);
}
