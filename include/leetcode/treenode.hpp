
#ifndef TREE_NODE_H__
#define TREE_NODE_H__
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

#define NULL_TREENODE std::numeric_limits<int>::min()

int cnt = 0;
class TreeNode final {
 private:
  bool is_null;
  bool generate_by_test;
  TreeNode(int x, const bool &is_null) : val(x),
                                         left(nullptr),
                                         right(nullptr),
                                         is_null(is_null),
                                         generate_by_test(true) {}

 public:
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0),
               left(nullptr),
               right(nullptr),
               generate_by_test(false),
               is_null(false) {}
  TreeNode(int x) : val(x),
                    left(nullptr),
                    right(nullptr),
                    generate_by_test(false),
                    is_null(false) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x),
                                                     left(left),
                                                     right(right),
                                                     generate_by_test(false),
                                                     is_null(false) {}
  TreeNode(const TreeNode &p) : val(p.val),
                                left(p.left),
                                right(p.right),
                                generate_by_test(p.generate_by_test),
                                is_null(p.is_null) {}
  ~TreeNode() {
    if (left != nullptr && !left->generate_by_test) delete left;
    if (right != nullptr && !right->generate_by_test) delete right;
  }

 private:
  static vector<vector<TreeNode>> keep_;

  static TreeNode *build_tree_(vector<TreeNode> &v, int current = 0) {
    if (current >= v.size() || v[current].is_null) return nullptr;
    v[current].left = build_tree_(v, 2 * current + 1);
    v[current].right = build_tree_(v, 2 * current + 2);
    return &v[current];
  }

 public:
  bool operator==(const TreeNode &rhs) const {
    return val == rhs.val &&
           (left == nullptr ? rhs.left == nullptr : (rhs.left == nullptr ? false : *(rhs.left) == *left)) &&
           (right == nullptr ? rhs.right == nullptr : (rhs.right == nullptr ? false : *(rhs.right) == *right));
  }

  static TreeNode *generate(const vector<int> &v, const int &nil = NULL_TREENODE) {
    keep_.push_back({});
    vector<TreeNode> &dummy = keep_.back();
    for (int i = 0; i < v.size(); ++i)
      dummy.push_back(TreeNode(v[i], v[i] == nil));
    return build_tree_(dummy);
  }

  static void release(initializer_list<TreeNode *> p) {
    for (auto node : p)
      if (node != nullptr && !node->generate_by_test) delete node;
  }
};

vector<vector<TreeNode>> TreeNode::keep_ = {};

#ifdef EXPECT_EQ
#define EXPECT_TREENODE_EQ(val1, val2)        \
  TreeNode *tval1 = val1, *tval2 = val2;      \
  if (tval1 != nullptr && tval2 != nullptr) { \
    EXPECT_EQ(*tval1, *tval2);                \
  } else {                                    \
    EXPECT_EQ(tval1, tval2);                  \
  }                                           \
  TreeNode::release({tval1, tval2});
#endif

#endif
