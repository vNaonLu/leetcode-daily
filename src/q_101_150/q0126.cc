// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Word Ladder II
//
// https://leetcode.com/problems/word-ladder-ii/
//
// Question ID: 126
// Difficult  : Hard
// Solve Date : 2022/08/14 14:35

#include <deque>
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |126. Word Ladder II|:
//
// A transformation sequence from word |beginWord| to word |endWord| using a
// dictionary |wordList| is a sequence of words |beginWord -> s₁ -> s₂ -> ... ->
// sₖ| such that:
//
//  • Every adjacent pair of words differs by a single letter.
//
//  • Every |sᵢ| for |1 <= i <= k| is in |wordList|. Note that |beginWord| does
//  not need to be in |wordList|.
//
//  • |sₖ == endWord|
// Given two words, |beginWord| and |endWord|, and a dictionary |wordList|,
// return all the shortest transformation sequences from |beginWord| to
// |endWord|, or an empty list if no such sequence exists. Each sequence should
// be returned as a list of the words |[beginWord, s₁, s₂, ..., sₖ]|.
//

LEETCODE_BEGIN_RESOLVING(126, WordLadderII, Solution);

class Solution {
private:
  vector<vector<string>> ans;

  class node {
  public:
    char              data;
    map<char, node *> h; // if a in h then it has its address
    node(char d) { data = d; }
  };

  class Trie {
    node *root;

  public:
    Trie() {
      root = new node(
          '\0'); // initial root which will contain map of first charachter
    }

    void insert(string &word) {
      node *temp = root;
      for (int i = 0; i < word.size(); i++) {
        char ch = word[i];
        if (temp->h.count(ch) ==
            0) { // if this character not present in previous charachter map
          node *child = new node(ch);
          temp->h[ch] = child;
        }
        temp = temp->h[ch];
      }
    }

    bool isPresent(string &word) {
      node *temp = root;
      for (int i = 0; i < word.size(); i++) {
        char ch = word[i];
        if (temp->h.count(ch))
          temp = temp->h[ch];
        else
          return 0;
      }
      return 1;
    }
  };

  void bfs(string &a, map<string, vector<string>> &parent, Trie &s) {
    map<string, int> dis;
    dis[a]            = 1;
    deque<string> que = {a};
    parent[a]         = {a};
    int l             = a.size();
    while (!que.empty()) {
      string v = que[0];
      int    d = dis[v];
      string e = que[0];
      que.pop_front();
      for (int i = 0; i < l; i++) {
        char cur = v[i];
        for (int j = 0; j < 26; j++) {
          v[i] = j + 'a';
          if (v[i] == cur)
            continue;
          if (s.isPresent(v)) {
            if (dis.count(v) == 0 || dis[v] > d + 1) {
              dis[v] = d + 1;
              parent[v].emplace_back(e);
              que.emplace_back(v);
            } else if (dis[v] == d + 1) {
              parent[v].emplace_back(e);
            }
          }
        }
        v[i] = cur;
      }
    }
  }

  void getAnswer(string &a, map<string, vector<string>> &parent,
                 deque<string> &store) {
    if (parent[a][0] == a) {
      vector<string> v(store.begin(), store.end());
      ans.emplace_back(v);
      return;
    }
    for (auto &i : parent[a]) {
      store.emplace_front(i);
      getAnswer(i, parent, store);
      store.pop_front();
    }
  }

public:
  vector<vector<string>> findLadders(string start, string end,
                                     vector<string> &dict) {
    ans = {};
    Trie s;
    for (auto &i : dict) {
      s.insert(i);
    }
    map<string, vector<string>> parent;
    bfs(start, parent, s);
    if (parent.count(end) == 0) {
      return {};
    }
    deque<string> store = {end};
    getAnswer(end, parent, store);
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= beginWord.length <= 5|
// * |endWord.length == beginWord.length|
// * |1 <= wordList.length <= 500|
// * |wordList[i].length == beginWord.length|
// * |beginWord|, |endWord|, and |wordList[i]| consist of lowercase English
// letters.
// * |beginWord != endWord|
// * All the words in |wordList| are unique.
// * The sum of all shortest transformation sequences does not exceed |10⁵|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: beginWord = "hit", endWord = "cog", wordList =
//  ["hot","dot","dog","lot","log","cog"]
// Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
//
// There are 2 shortest transformation sequences:
// "hit" -> "hot" -> "dot" -> "dog" -> "cog"
// "hit" -> "hot" -> "lot" -> "log" -> "cog"

LEETCODE_SOLUTION_UNITTEST(126, WordLadderII, example_1) {
  auto                   solution  = MakeSolution();
  string                 beginWord = "hit";
  string                 endWord   = "cog";
  vector<string>         wordList  = {"hot", "dot", "dog", "lot", "log", "cog"};
  vector<vector<string>> expect    = {
      {"hit", "hot", "dot", "dog", "cog"},
      {"hit", "hot", "lot", "log", "cog"}
  };
  vector<vector<string>> actual =
      solution->findLadders(beginWord, endWord, wordList);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: beginWord = "hit", endWord = "cog", wordList =
//  ["hot","dot","dog","lot","log"]
// Output: []
//
// The endWord "cog" is not in wordList, therefore there is no valid
// transformation sequence.

LEETCODE_SOLUTION_UNITTEST(126, WordLadderII, example_2) {
  auto                   solution  = MakeSolution();
  string                 beginWord = "hit";
  string                 endWord   = "cog";
  vector<string>         wordList  = {"hot", "dot", "dog", "lot", "log"};
  vector<vector<string>> expect    = {};
  vector<vector<string>> actual =
      solution->findLadders(beginWord, endWord, wordList);
  LCD_EXPECT_EQ(expect, actual);
}
