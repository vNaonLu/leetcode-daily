
#ifndef LEETCODE_Q1629_H__
#define LEETCODE_Q1629_H__

#include <algorithm>
#include <iostream>
#include <vector>

namespace l1629 {
using namespace std;
class Solution {
 public:
  char slowestKey(vector<int>& releaseTimes, string keysPressed) {
    if (keysPressed.size() < 1) return '\0';
    char res = keysPressed[0];
    int longest = releaseTimes[0];
    for (int i = 1; i < releaseTimes.size(); ++i) {
      int cur = releaseTimes[i] - releaseTimes[i - 1];
      if (cur > longest) {
        longest = cur;
        res = keysPressed[i];
      } else if (cur == longest) {
        res = max(res, keysPressed[i]);
      }
    }
    return res;
  }
};
}  // namespace leetcode

#endif
