#include "leetcode/list_node.h"
#include "leetcode/tree_node.h"
#include "test_helper.h"
#include <list>
#include <unordered_map>

#include "leetcode/testing/solution_test_helper.h"

using namespace lcd;
using namespace std;

SOLUTION_BEGIN(q1_sample, Solution);

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> memo;
    auto                    beg = nums.begin();
    vector<int>             res = {-1, -1};
    while (beg != nums.end()) {
      auto idx = distance(nums.begin(), beg);
      auto inv = memo.find(target - *beg);
      if (inv != memo.end()) {
        res[0] = inv->second;
        res[1] = idx;
        break;
      }
      memo.emplace(*beg++, idx);
    }
    return res;
  }
};

SOLUTION_END(q1_sample, Solution);

SOLUTION_TESTCASE(q1_sample, sameple_1) {
  auto        solution = GetSolution();
  vector<int> nums     = {2, 7, 11, 15};
  int         target   = 9;
  vector<int> expect   = {0, 1};
  vector<int> actual   = solution->twoSum(nums, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// =====

SOLUTION_BEGIN(q146_sample, LRUCache);
class LRUCache {
private:
  unordered_map<int, list<pair<int, int>>::iterator> memos;
  list<pair<int, int>>                               cache;
  int                                                cap;

  void remove(int key) {
    auto it = memos.find(key);
    if (it != memos.end()) {
      cache.erase(it->second);
      memos.erase(key);
    }
  }

  void add(int key, int value) {
    remove(key);
    if (memos.size() == cap) {
      remove(cache.back().first);
    }
    cache.emplace_front(key, value);
    memos.emplace(key, cache.begin());
  }

public:
  LRUCache(int capacity) : cap{capacity} {}

  int get(int key) {
    auto it = memos.find(key);
    if (it != memos.end()) {
      int res = (*it->second).second;
      add(key, res);
      return res;
    }
    return -1;
  }

  void put(int key, int value) { add(key, value); }
};

SOLUTION_END(q146_sample, LRUCache);

SOLUTION_TESTCASE(q146_sample, sample_1) {
  int  capacity  = 2;
  auto lru_cache = GetLRUCache(capacity);
  lru_cache->put(1, 1);
  lru_cache->put(2, 2);
  EXPECT_EQ(lru_cache->get(1), 1);
  lru_cache->put(3, 3);
  EXPECT_EQ(lru_cache->get(2), -1);
  lru_cache->put(4, 4);
  EXPECT_EQ(lru_cache->get(1), -1);
  EXPECT_EQ(lru_cache->get(3), 3);
  EXPECT_EQ(lru_cache->get(4), 4);
}

// =====

SOLUTION_BEGIN(q234_sample, Solution);
class Solution {
public:
  bool isPalindrome(ListNode *head) {
    auto v = vector<decltype(ListNode::val)>();
    while (nullptr != head) {
      v.emplace_back(head->val);
      head = head->next;
    }

    int lo = 0;
    int hi = v.size() - 1;

    while (lo < hi) {
      if (v[lo++] != v[hi--]) {
        return false;
      }
    }

    return true;
  }
};
SOLUTION_END(q234_sample, Solution);

SOLUTION_TESTCASE(q234_sample, sample_1) {
  auto      solution = GetSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 2, 1});
  bool      exp      = true;
  bool      act      = solution->isPalindrome(head);
  EXPECT_EQ(act, exp);
  ListNode::Release(head);
}

SOLUTION_BEGIN(q783_sample, Solution);
class Solution {
private:
  void solve(TreeNode *p, int &prev, int &res) {
    if (nullptr != p) {
      solve(p->left, prev, res);
      if (prev != -1) {
        res = min(res, p->val - prev);
      }
      prev = p->val;
      solve(p->right, prev, res);
    }
  }

public:
  int minDiffInBST(TreeNode *root) {
    auto res  = numeric_limits<int>::max();
    auto prev = -1;
    solve(root, prev, res);
    return res;
  }
};
SOLUTION_END(q783_sample, Solution);

SOLUTION_TESTCASE(q783_sample, sample_1) {
  auto      solution = GetSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 6, 1, 3});
  int       exp      = 1;
  int       act      = solution->minDiffInBST(root);
  EXPECT_EQ(act, exp);
  TreeNode::Release(root);
}