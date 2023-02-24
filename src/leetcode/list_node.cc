#include "leetcode/list_node.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace lcd {

ListNode::ListNode() : val{0}, next{nullptr} {}

ListNode::ListNode(int32_t x) : val{x}, next{nullptr} {}

ListNode::ListNode(int32_t x, ListNode *next) : val{x}, next{next} {}

ListNode::~ListNode() = default;

ListNode *ListNode::FromVector(const std::vector<int32_t> &args,
                               Optional<int>               repeat_to) noexcept {
  std::vector<ListNode *> nodes;
  for (auto v : args) {
    nodes.emplace_back(new ListNode(v));
  }

  if (nodes.empty()) {
    return nullptr;
  }

  auto next = ++nodes.begin();
  while (next != nodes.end()) {
    (*(next - 1))->next = *next;
    ++next;
  }

  if (repeat_to) {
    assert(repeat_to.value() < nodes.size());
    nodes.back()->next = nodes[repeat_to.value()];
  }

  return nodes.front();
}

std::vector<std::pair<ListNode const *, size_t>>
ToVector(ListNode const *node) {
  size_t                                           idx       = 0;
  bool                                             is_repeat = false;
  std::unordered_map<ListNode const *, size_t>     avoid_loop;
  std::vector<std::pair<ListNode const *, size_t>> list_vector;

  while (!is_repeat && node) {
    is_repeat = !avoid_loop.emplace(node, idx++).second;
    list_vector.emplace_back(node, avoid_loop[node]);
    node = node->next;
  }

  return list_vector;
}

ListNode *ListNode::GetChild(size_t idx) noexcept {
  std::unordered_set<ListNode *> avoid_dup;
  auto                          *ptr       = this;
  bool                           is_repeat = false;
  while (ptr && idx--) {
    if (!avoid_dup.emplace(ptr).second) {
      return nullptr;
    }
    ptr = ptr->next;
  }
  return avoid_dup.emplace(ptr).second ? ptr : nullptr;
}

std::vector<ListNode *> ListNode::GetChildren() const {
  std::unordered_set<ListNode *> avoid_dup;
  auto                          *ptr = this->next;
  while (ptr && CheckValid(ptr)) {
    if (!avoid_dup.emplace(ptr).second) {
      break;
    }
    ptr = ptr->next;
  }
  return std::vector<ListNode *>(avoid_dup.begin(), avoid_dup.end());
}

bool ListNode::operator==(ListNode const &rhs) const noexcept {
  auto this_vec = ToVector(this);
  auto rhs_vec  = ToVector(&rhs);

  if (this_vec.size() != rhs_vec.size()) {
    return false;
  }

  for (size_t i = 0; i < this_vec.size(); ++i) {
    if (this_vec[i].first->val != rhs_vec[i].first->val ||
        this_vec[i].second != rhs_vec[i].second) {
      return false;
    }
  }

  return true;
}

bool ListNode::operator<(ListNode const &rhs) const noexcept {
  auto lhs_vec = ToVector(this);
  auto rhs_vec = ToVector(&rhs);

  if (lhs_vec.size() != rhs_vec.size()) {
    return lhs_vec.size() < rhs_vec.size();
  }

  auto lb = lhs_vec.begin();
  auto rb = rhs_vec.begin();
  while (lb != lhs_vec.end() && rb != rhs_vec.end()) {
    if (lb->first->val != rb->first->val) {
      return lb->first->val < rb->first->val;
    }
    ++lb;
    ++rb;
  }
  return true;
}

void PrintTo(ListNode *node, ::std::ostream *os) {
  if (!node) {
    *os << "nullptr";
  } else {
    auto vec        = ToVector(node);
    bool first_elem = true;

    *os << "{";
    for (auto [node, idx] : vec) {
      if (!first_elem) {
        *os << ", ";
      }
      first_elem = false;
      *os << node->val;
    }

    if (!vec.empty()) {
      if (vec.back().second != vec.size() - 1) {
        // Loop List
        *os << "(Loop to index-" << vec.back().second << ")";
      }
    }

    *os << "}";
  }
}

std::ostream &operator<<(std::ostream &stream, ListNode const &node) noexcept {
  auto vec        = ToVector(&node);
  bool first_elem = true;

  stream << "{";
  for (auto [node, idx] : vec) {
    if (!first_elem) {
      stream << ", ";
    }
    first_elem = false;
    stream << node->val;
  }

  if (!vec.empty()) {
    if (vec.back().second != vec.size() - 1) {
      // Loop List
      stream << "(Loop to index-" << vec.back().second << ")";
    }
  }

  stream << "}";

  return stream;
}

} // namespace lcd
