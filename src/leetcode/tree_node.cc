#include "leetcode/tree_node.h"
#include <ostream>
#include <queue>
#include <string>
#include <vector>

namespace lcd {

TreeNode::TreeNode() : val{0}, left{nullptr}, right{nullptr} {}

TreeNode::TreeNode(int32_t x) : val{x}, left{nullptr}, right{nullptr} {}

TreeNode::TreeNode(int32_t x, TreeNode *node1, TreeNode *node2)
    : val{x}, left{node1}, right{node2} {}

TreeNode::~TreeNode() = default;

void TreeNode::Reset() noexcept {
  if (CheckValid(this)) {
    if (left) {
      auto *ptr = left;
      left      = nullptr;
      ptr->Reset();
    }

    if (right) {
      auto *ptr = right;
      right     = nullptr;
      ptr->Reset();
    }
  }
}

TreeNode *
TreeNode::FromVector(const std::vector<Optional<int32_t>> &args) noexcept {
  std::vector<TreeNode *> nodes;
  for (auto &opt : args) {
    nodes.emplace_back(opt ? new TreeNode(opt.value()) : nullptr);
  }

  if (nodes.empty()) {
    return nullptr;
  }

  auto                   current = nodes.begin();
  std::queue<TreeNode *> que;
  que.emplace(*current);

  while (!que.empty() && current != nodes.end()) {
    auto *node = que.front();
    que.pop();

    assert(node);

    if (current + 1 != nodes.end() && *(++current)) {
      que.emplace(*current);
      node->left = *current;
    }

    if (current + 1 != nodes.end() && *(++current)) {
      que.emplace(*current);
      node->right = *current;
    }
  }

  return nodes.front();
}

namespace {

template <typename T>
void PreOrderImpl(T *node, std::vector<T *> *view) {
  if (node && T::CheckValid(node)) {
    view->push_back(node);
    PreOrderImpl<T>(node->left, view);
    PreOrderImpl<T>(node->right, view);
  }
}

} // namespace

template <typename T>
std::vector<T *> PreOrder(T *node) {
  std::vector<T *> res;
  PreOrderImpl<T>(node, &res);
  return res;
}

TreeNode *TreeNode::GetChild(size_t preorder_idx) noexcept {
  auto pre_order = PreOrder(this);

  return preorder_idx < pre_order.size() ? pre_order[preorder_idx] : nullptr;
}

std::vector<TreeNode *> TreeNode::GetChildren() noexcept {
  auto res = PreOrder(this);
  return std::vector<TreeNode *>(res.begin() + 1, res.end());
}

bool TreeNode::operator==(TreeNode const &rhs) const noexcept {
  auto this_pre_order = PreOrder(this);
  auto rhs_pre_order  = PreOrder(&rhs);

  if (this_pre_order.size() != rhs_pre_order.size()) {
    return false;
  }

  for (size_t i = 0; i < this_pre_order.size(); ++i) {
    if (this_pre_order[i]->val != rhs_pre_order[i]->val) {
      return false;
    }
  }

  return true;
}

bool TreeNode::operator<(TreeNode const &rhs) const noexcept {
  auto lhs_vec = PreOrder(this);
  auto rhs_vec = PreOrder(&rhs);

  if (lhs_vec.size() != rhs_vec.size()) {
    return lhs_vec.size() < rhs_vec.size();
  }

  auto lb = lhs_vec.begin();
  auto rb = rhs_vec.begin();
  while (lb != lhs_vec.end() && rb != rhs_vec.end()) {
    if ((*lb)->val != (*rb)->val) {
      return (*lb)->val < (*rb)->val;
    }
    ++lb;
    ++rb;
  }

  return true;
}

void PrintTo(TreeNode *value, ::std::ostream *os) {
  if (!value) {
    *os << "nullptr";
  } else {
    std::queue<TreeNode const *> que;
    std::vector<std::string>     text;

    que.emplace(value);
    while (!que.empty()) {
      auto *current = que.front();
      que.pop();
      if (current) {
        que.emplace(current->left);
        que.emplace(current->right);
        text.emplace_back(std::to_string(current->val));
      } else {
        text.emplace_back("null");
      }
    }

    // Slice the tail null
    while (!text.empty() && text.back() == "null") {
      text.pop_back();
    }

    bool is_first = true;
    *os << "{";
    for (auto &s : text) {
      if (!is_first) {
        *os << ", ";
      }
      is_first = false;
      *os << std::move(s);
    }
    *os << "}";
  }
}

std::ostream &operator<<(std::ostream        &stream,
                         lcd::TreeNode const &node) noexcept {
  std::queue<TreeNode const *> que;
  std::vector<std::string>     text;

  que.emplace(&node);
  while (!que.empty()) {
    auto *current = que.front();
    que.pop();
    if (current) {
      que.emplace(current->left);
      que.emplace(current->right);
      text.emplace_back(std::to_string(current->val));
    } else {
      text.emplace_back("null");
    }
  }

  // Slice the tail null
  while (!text.empty() && text.back() == "null") {
    text.pop_back();
  }

  bool is_first = true;
  stream << "{";
  for (auto &s : text) {
    if (!is_first) {
      stream << ", ";
    }
    is_first = false;
    stream << std::move(s);
  }
  stream << "}";

  return stream;
}

} // namespace lcd
