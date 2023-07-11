# LeetCode Daily in C++

[![gccbuild](https://github.com/vNaonLu/Daily_LeetCode/actions/workflows/gcc.yml/badge.svg)](https://github.com/vNaonLu/leetcode-daily/actions) [![msvcbuild](https://github.com/vNaonLu/Daily_LeetCode/actions/workflows/msvc.yml/badge.svg)](https://github.com/vNaonLu/leetcode-daily/actions)

This repository collects some of my LeetCode solutions in C++ for **free** questions since 2021/09/06. The remain questions is still being solved so the current project may not contain the solutions you are looking for. Please check the chapter [Getting Started](#getting-started) for more details.

Here is my [LeetCode account](https://leetcode.com/naon/) if you are interested.

## Getting Started

See [Activity](#activity) to check the recent solution resolution status, including the historical statistics and the recent submissions.
All solved solutions are stored in `src` and more information can be found at [Find Solution](#finding-solution).
See [Installation](#installation) if you are interested in how to build the project or add some testcases for some solutions.

More information about solved solution can be found at [docs/solved_solutions.md](./docs/solved_solutions.md) and unsolved questions can be found at [docs/unsolved_solutions.md](./docs/unsolved_solutions.md).

## Activity

![progress](./docs/assets/progress.svg)
![activity](./docs/assets/recent_activity.svg)

More information about full activities can be found at:

- All submissions in 2023: [docs/2023.md](./docs/2023.md)
- All submissions in 2022: [docs/2022.md](./docs/2022.md)
- All submissions in 2021: [docs/2021.md](./docs/2021.md)

## Finding Solution

All solved solution information can be found at [docs/solved_solutions.md](./docs/solved_solutions.md) and all solutions are in the directory of [src](./src) corresponding to their LeetCode frontend ID. For instance, the solution for [1. Two Sum](https://leetcode.com/problems/two-sum/) is stored in [src/q_1_50/q0001.cc](./src/q_1_50/q0001.cc). In addition, the solution fragment always appear between `LEETCODE_BEGIN_RESOLVING` and `LEETCODE_END_RESOLVING`, e.g.

```cpp
// ...
LEETCODE_BEGIN_RESOLVING(1, TwoSum, Solution);

class Solution {
public:
  vector<int> twoSum(vector<int> &nums, int target) {
    auto memo = unordered_map<int, int>();
    for (int i = 0; i < nums.size(); ++i) {
      auto find = memo.find(target - nums[i]);
      if (find != memo.end()) {
        return vector<int>{find->second, i};
      }
      memo.emplace(nums[i], i);
    }
    return vector<int>{-1, -1};
  }
};

LEETCODE_END_RESOLVING(Solution);
// ...
```
 Or you can simply use the script `ldt` to cat the specific solution via:
```sh
# in the project root
$ ./ldt cat <question id>
```
But the script probably won't work as it is very rough currently.

## Installation
It is not necessary to build or install this project if you just want to find specific solutions, but you can still build and run this project. 
There has a script named `ldt` in the root, which is a tool to automatically add/delete the solution in this project, generate the solution template or update the readme or log. However the script may too rough to use since I haven't tested it in other environment.

Before running to build project, please check below dependencies:
 - C++20 supported Compiler.
 - CMake above `3.20`.

Then you can build the project manually by

``` sh
$ git clone https://github.com/vNaonLu/leetcode-daily.git
$ cd leetcode-daily
$ cmake -S . -B build -DENABLE_LEETCODE_TEST=ON
$ cmake --build build
# Run the unittests
$ ./build/leetcode_test
```

