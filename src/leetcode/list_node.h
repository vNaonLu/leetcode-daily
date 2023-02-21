#ifndef LEETCODE_LIST_NODE_H_
#define LEETCODE_LIST_NODE_H_

#include "leetcode/leetcode_helper.h"
#include <cstdint>
#include <unordered_set>
#include <utility>
#include <vector>

namespace lcd {

class ListNode;

class ListNode : public MemoryChecker<ListNode> {
public:
  ListNode();
  explicit ListNode(int32_t x);
  ListNode(int32_t x, ListNode *next);
  ~ListNode() = default;

public:
  mutable ListNode *next;
  int32_t           val;

public:
  ListNode *FromVector(const std::vector<int32_t> &args,
                       Optional<int>               repeat_to = null) noexcept;

  bool operator==(const ListNode &rhs) const noexcept;

  ListNode *GetChild(size_t idx) noexcept;
};

} // namespace lcd

#endif // LEETCODE_LIST_NODE_H_
