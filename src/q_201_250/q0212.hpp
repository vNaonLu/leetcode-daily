
#ifndef LEETCODE_Q212_H__
#define LEETCODE_Q212_H__
#include <iostream>
#include <vector>

namespace l212 {
using namespace std;

/**
  * This file is generated by leetcode_add.py
  *
  * 212.
  *      Word Search II
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   Given an ‘m x n’  ‘board’ of characters and a list of strings ‘words’
  *   , return “all words on the board”.
  *   
  *   Each word must be constructed from letters of sequentially adjacent
  *   cells, where “adjacent cells” are horizontally or vertically
  *   neighboring. The same letter cell may not be used more than once in a
  *   word.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘m = board.length’
  *   • ‘n = board[i].length’
  *   • ‘1 ≤ m, n ≤ 12’
  *   • ‘board[i][j]’ is a lowercase English letter.
  *   • ‘1 ≤ words.length ≤ 3 × 10⁴’
  *   • ‘1 ≤ words[i].length ≤ 10’
  *   • ‘words[i]’ consists of lowercase English letters.
  *   • All the strings of ‘words’ are unique.
  *
*/

class Solution {
 private:
  vector<vector<char>> b;
  vector<string> res;
  int m = 0;
  int n = 0;
  char mask = ' ';

  class TrieNode {
   private:
    vector<TrieNode*> next;
    bool is_end;

   public:
    bool inserted;
    TrieNode() {
      next.resize(26, nullptr);
      is_end = false;
      inserted = false;
    }
    ~TrieNode() {
      for (auto& it : next) {
        if (it != nullptr) {
          delete it;
          it = nullptr;
        }
      }
    }

    inline bool has(const char& c) const {
      return next[c - 'a'] != nullptr;
    }
    inline TrieNode* get(const char& c) {
      if (!has(c))
        next[c - 'a'] = new TrieNode();
      return next[c - 'a'];
    }
    inline bool end() const {
      return is_end;
    }
    inline void setEnd() {
      is_end = true;
    }
  }* root = new TrieNode();

  inline void insert(const string& s) {
    TrieNode* node = root;
    for (const char& c : s)
      node = node->get(c);
    node->setEnd();
  }

  void dfs(int i, int j, TrieNode* p, string& word) {
    if (p == nullptr || i < 0 || i >= m || j < 0 || j >= n) return;
    char ori = b[i][j];
    if (ori == mask || !p->has(ori)) return;
    p = p->get(ori);
    b[i][j] = mask;
    word.push_back(ori);
    if (p->end() && !p->inserted) {
      p->inserted = true;
      res.push_back(word);
    }
    dfs(i - 1, j, p, word);
    dfs(i + 1, j, p, word);
    dfs(i, j - 1, p, word);
    dfs(i, j + 1, p, word);
    b[i][j] = ori;
    word.pop_back();
  }

 public:
  ~Solution() {
    delete root;
  }
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    b = board, m = b.size(), n = b[0].size();
    for (const string& s : words)
      insert(s);
    string tmp = "";
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (root->has(b[i][j])) {
          dfs(i, j, root, tmp);
        }
      }
    }
    return res;
  }
};
}  // namespace l212

#endif