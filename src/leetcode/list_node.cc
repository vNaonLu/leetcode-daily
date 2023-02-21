#include "leetcode/list_node.h"

namespace lcd {

ListNode::ListNode() : val{0}, next{nullptr} {}

ListNode::ListNode(int32_t x) : val{x}, next{nullptr} {}

ListNode::ListNode(int32_t x, ListNode *next) : val{x}, next{nullptr} {}

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
    nodes.back()->next = nodes[repeat_to.value()];
  }

  return nodes.front();
}

bool ListNode::operator==(const ListNode &rhs) const noexcept {
  if (val != rhs.val) {
    return false;
  }

  if (!next && !rhs.next) {
    return true;
  } else if (!next || !rhs.next) {
    return false;
  }

  auto *this_next = next;
  auto *rhs_next  = rhs.next;

  // break link to avoid repeat
  next        = nullptr;
  rhs.next    = nullptr;
  auto result = *this_next == *rhs_next;
  next        = this_next;
  rhs.next    = rhs_next;

  return result;
}

ListNode *ListNode::GetChild(size_t idx) noexcept {
  std::unordered_set<ListNode *> avoid_dup;
  auto                          *ptr = this;
  while (!ptr && idx--) {
    if (!avoid_dup.emplace(ptr).second) {
      assert(false);
      return nullptr;
    }
    ptr = ptr->next;
  }
  return ptr;
}

} // namespace lcd
