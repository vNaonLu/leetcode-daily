#ifndef LEETCODE_LIST_NODE_H_
#define LEETCODE_LIST_NODE_H_

#ifdef TESTING_SOLUTION_HELPER_H_
#error list_node.h must be included before solution_test_helper.h
#endif

#include "leetcode/leetcode_helper.h"
#include <cstdint>
#include <ostream>
#include <vector>

namespace lcd {

class ListNode;

class ListNode : public AllocationCounted<ListNode> {
public:
  ListNode();
  explicit ListNode(int32_t x);
  ListNode(int32_t x, ListNode *next);
  ~ListNode() override;

public:
  ListNode *next;
  int32_t   val;

public:
  static ListNode        *FromVector(std::vector<int32_t> const &args,
                                     Optional<int> repeat_to = null) noexcept;
  ListNode               *GetChild(size_t idx) noexcept;
  std::vector<ListNode *> GetChildren() const;
  bool                    operator==(ListNode const &rhs) const noexcept;
  bool                    operator<(ListNode const &rhs) const noexcept;
};


// Google test print
void          PrintTo(ListNode *value, ::std::ostream *os);
std::ostream &operator<<(std::ostream        &stream,
                         lcd::ListNode const &node) noexcept;

} // namespace lcd


#endif // LEETCODE_LIST_NODE_H_
