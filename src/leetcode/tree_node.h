#ifndef LEETCODE_TREE_NODE_H_
#define LEETCODE_TREE_NODE_H_

#ifdef TESTING_SOLUTION_HELPER_H_
#error tree_node.h must be included before solution_test_helper.h
#endif

#include "leetcode/leetcode_helper.h"
#include <cstdint>
#include <ostream>
#include <vector>

namespace lcd {

class TreeNode;

class TreeNode : public AllocationCounted<TreeNode> {
public:
  TreeNode();
  explicit TreeNode(int32_t x);
  TreeNode(int32_t x, TreeNode *left, TreeNode *right);
  ~TreeNode() override;

public:
  int32_t   val;
  TreeNode *left;
  TreeNode *right;

public:
  void Reset() noexcept;
  static TreeNode           *
  FromVector(std::vector<Optional<int32_t>> const &args) noexcept;
  TreeNode *GetChild(size_t preorder_idx) noexcept;
  std::vector<TreeNode *> GetChildren() noexcept;
  bool                    operator==(TreeNode const &rhs) const noexcept;
  bool                    operator<(TreeNode const &rhs) const noexcept;
};

// Google test print
void          PrintTo(TreeNode *value, ::std::ostream *os);
std::ostream &operator<<(std::ostream        &stream,
                         lcd::TreeNode const &node) noexcept;

} // namespace lcd

#endif // LEETCODE_TREE_NODE_H_
