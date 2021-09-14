
#ifndef TREE_NODE_H__
#define TREE_NODE_H__
#include <algorithm>
#include <iostream>
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
  static vector<vector<TreeNode *>> memory_;

  static TreeNode *generate_(vector<TreeNode *> &v, int current) {
    if (current >= v.size() || v[current] == nullptr)
      return nullptr;
    v[current]->left = generate_(v, 2 * current + 1);
    v[current]->right = generate_(v, 2 * current + 2);
    return v[current];
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
    for (int i = 0; i < v.size(); ++i) {
      if (v[i] != null)
        dummy_nodes[i] = new TreeNode(v[i]);
    }
    memory_.push_back(dummy_nodes);
    return generate_(dummy_nodes, 0);
  }

  inline static void release(TreeNode *p) {
    for (auto mem = memory_.begin(); mem != memory_.end(); ++mem) {
      auto find = std::find((*mem).begin(), (*mem).end(), p);
      if (find != (*mem).end()) {
        for (auto it = (*mem).begin(); it != (*mem).end(); ++it) {
          if (*it != nullptr)
            delete *it;
        }
        memory_.erase(mem);
        break;
      }
    }
  }
};

vector<vector<TreeNode *>> TreeNode::memory_ = {};

#endif
