
#ifndef LEETCODE_Q997_H__
#define LEETCODE_Q997_H__
#include <iostream>
#include <vector>

namespace l997 {
using namespace std;

/**
  * This file is generated by leetcode_add.py
  *
  * 997.
  *      Find the Town Judge
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   In a town, there are ‘n’ people labeled from ‘1’ to ‘n’ . There is a
  *   rumor that one of these people is secretly the town judge.
  *   
  *   If the town judge exists,.
  *   
  *   - The town judge trusts nobody.
  *   
  *   - Everybody (except for the town judge) trusts the town judge.
  *   
  *   - There is exactly one person that satisfies properties “1” and “2”.
  *   
  *   You are given an array ‘trust’ where ‘trust[i] = [aᵢ, bᵢ]’
  *   representing that the person labeled ‘aᵢ’ trusts the person labeled
  *   ‘bᵢ’.
  *   
  *   Return “the label of the town judge if the town judge exists and can
  *   be identified, or return ” ‘-1’ “ otherwise”.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘1 ≤ n ≤ 1000’
  *   • ‘0 ≤ trust.length ≤ 10⁴’
  *   • ‘trust[i].length = 2’
  *   • All the pairs of ‘trust’ are “unique” .
  *   • ‘aᵢ ≠ bᵢ’
  *   • ‘1 ≤ aᵢ, bᵢ ≤ n’
  *
*/

class Solution {
 public:
  int findJudge(int n, vector<vector<int>>& trust) {
    vector<pair<int, int>> trust_map(n, make_pair(0, 0));
    for (const auto& t : trust) {
      ++trust_map[t[0] - 1].first;
      ++trust_map[t[1] - 1].second;
    }
    for (int i = 0; i < trust_map.size(); ++i)
      if (trust_map[i].first == 0 && trust_map[i].second == n - 1)
        return i + 1;
    return -1;
  }
};
}  // namespace l997

#endif