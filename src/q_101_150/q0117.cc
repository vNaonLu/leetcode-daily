#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 117.
 *      Populating Next Right Pointers in Each Node II
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a binary
 *   struct Node
 *     int
 *     Node
 *     Node
 *     Node
 *   Populate each next pointer to point to its next right node. If there
 *   is no next right node, the next pointer should be set to ‘NULL’
 *   Initially, all next pointers are set to ‘NULL’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the tree is in the range ‘[0, 6000]’ .
 *   • ‘-100 ≤ Node.val ≤ 100’
 *   • You may only use constant extra space.
 *   • The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem.
 *
 */

struct q117 : public ::testing::Test {
  // Leetcode answer here
  class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
  };
  class Solution {
   private:
    void helper(vector<vector<Node*>>& r, Node* p, int level = 0) {
      if (p == nullptr) return;
      if (level >= r.size()) r.resize(level + 1);
      r[level].push_back(p);
      helper(r, p->left, level + 1);
      helper(r, p->right, level + 1);
    }
   public:
    Node* connect(Node* root) {
      vector<vector<Node*>> level_map;
      helper(level_map, root);
      for (auto levels : level_map) {
        for (int i = 0; i < levels.size() - 1; ++i) {
          levels[i]->next = levels[i + 1];
        }
      }
      return root;
    }
  };

  class Solution *solution;
};

TEST_F(q117, NOT_IMPLEMENT) {
   EXPECT_TRUE("NOT IMPLEMENT");
}