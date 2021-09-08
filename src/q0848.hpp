
#ifndef LEETCODE_Q848_H__
#define LEETCODE_Q848_H__

#include <iostream>
#include <string>
#include <vector>

namespace l848 {
using namespace std;
class Solution {
 public:
  string shiftingLetters(string s, vector<int>& shifts) {
    for (auto it = shifts.rbegin(); it != shifts.rend(); ++it) {
      if (it == shifts.rbegin())
        *it %= 26;
      else
        *it = (*it + *(it - 1)) % 26;
    }

    for (int i = 0; i < shifts.size(); ++i) {
      s[i] = (s[i] - 'a' + shifts[i]) % 26 + 'a';
    }

    return s;
  }
};
}  // namespace l848

#endif