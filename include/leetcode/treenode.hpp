#ifndef __TREE_NODE_H_
#define __TREE_NODE_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <optional>
#include <queue>
#include <type_traits>
#include <unordered_set>
#include <vector>

using namespace std;
struct TreeNode;

template <typename... _type>
using enable_if_treenode_t = std::enable_if_t<(... && std::is_same_v<_type, TreeNode *>), size_t>;

#define NULL_TREENODE nullopt

struct TreeNode final {
  /// for leetcode usage
  int val;
  TreeNode *left, *right;
  TreeNode() : val(0), left(nullptr),right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr),right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  ~TreeNode() {}

  /// for project usage

  inline static TreeNode *_build_tree(vector<TreeNode*> &v) noexcept {
    if (v.empty()) return nullptr;
    auto _v_ptr = v.begin();
    queue<TreeNode *> q;
    q.emplace(*_v_ptr);
    while (!q.empty() && _v_ptr != v.end()) {
      TreeNode *node = q.front(); q.pop();
      if (_v_ptr + 1 != v.end() && nullptr != *(++_v_ptr)) {
        q.emplace(*_v_ptr);
        node->left = *_v_ptr;
      }
      if (_v_ptr + 1 != v.end() && nullptr != *(++_v_ptr)) {
        q.emplace(*_v_ptr);
        node->right = *_v_ptr;
      }
    }
    return v.front();
  }

  static TreeNode *generate(const vector<optional<int>> &v) {
    vector<TreeNode*> dummy;
    for(const auto &x : v)
      dummy.emplace_back(x.has_value() ? new TreeNode(x.value())
                                       : nullptr);
    return _build_tree(dummy);
  }

  template <typename... _type> static
  enable_if_treenode_t<_type...> release(_type... nodes) noexcept {
    vector<TreeNode *> _variadic_nodes = {nodes...};
    unordered_set<TreeNode *> _cand_to_del;
    for(auto node : _variadic_nodes) {
      if (nullptr == node) continue;
      queue<TreeNode *> travel; travel.emplace(node);
      while(!travel.empty()) {
        auto cur = travel.front(); travel.pop();
        if (_cand_to_del.count(cur)) continue;
        _cand_to_del.insert(cur);
        if (nullptr != cur->left) travel.emplace(cur->left);
        if (nullptr != cur->right) travel.emplace(cur->right);
      }
    }
    for (auto it = _cand_to_del.begin(); it != _cand_to_del.end(); ++it)
      delete *it;
    return _cand_to_del.size();
  }
};

inline bool
operator==(const TreeNode &lhs, const TreeNode &rhs) noexcept {
  return lhs.val == rhs.val &&
         (lhs.left == nullptr ? rhs.left == nullptr 
                              : (rhs.left == nullptr ? false 
                                                     : *(rhs.left) == *(lhs.left))) &&
         (lhs.right == nullptr ? rhs.right == nullptr 
                               : (rhs.right == nullptr ? false
                                                       : *(rhs.right) == *(lhs.right)));
}

#ifdef EXPECT_EQ
#define EXPECT_TREENODE_EQ(val1, val2)        \
{                                             \
  TreeNode *tval1 = val1, *tval2 = val2;      \
  if (tval1 != nullptr && tval2 != nullptr) { \
    EXPECT_EQ(*tval1, *tval2);                \
  } else {                                    \
    EXPECT_EQ(tval1, tval2);                  \
  }                                           \
}
#endif

#endif
