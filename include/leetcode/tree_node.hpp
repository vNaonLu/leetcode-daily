
#ifndef TREE_NODE_H__
#define TREE_NODE_H__
#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class TreeNode final {
 public:
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

 private:
  static unordered_map<TreeNode *, set<TreeNode *>> memory_;

  static TreeNode *generate_(vector<TreeNode *> &v, int current) {
    if (current >= v.size() || v[current] == nullptr)
      return nullptr;
    v[current]->left = generate_(v, 2 * current + 1);
    v[current]->right = generate_(v, 2 * current + 2);
    return v[current];
  }

  inline static void cut_(TreeNode *p, set<TreeNode *> &map) {
    if (p == nullptr) return;
    cut_(p->left, map);
    cut_(p->right, map);
    map.insert(p);
  }

 public:
  static bool equal(TreeNode *p, TreeNode *q) {
    if (p == nullptr && q == nullptr)
      return true;
    else if (p == nullptr)
      return false;
    else if (q == nullptr)
      return false;
    else {
      return p->val == q->val && equal(p->left, q->left) && equal(p->right, q->right);
    }
  }

  static TreeNode *generate(const vector<int> &v, const int &null) {
    vector<TreeNode *> dummy_nodes(v.size(), nullptr);
    set<TreeNode *> tree_map;
    for (int i = 0; i < v.size(); ++i) {
      if (v[i] != null) {
        dummy_nodes[i] = new TreeNode(v[i]);
        tree_map.insert(dummy_nodes[i]);
      }
    }
    TreeNode *p = generate_(dummy_nodes, 0);
    if (p != nullptr) memory_[p] = tree_map;
    return p;
  }

  inline static void release(TreeNode *p) {
    cut_(p, memory_[p]);

    for (auto it = memory_[p].begin(); it != memory_[p].end(); ++it) {
      delete *it;
    }

    memory_.erase(p);
  }
};

unordered_map<TreeNode *, set<TreeNode *>> TreeNode::memory_;

#endif
