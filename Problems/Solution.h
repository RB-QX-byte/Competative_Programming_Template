#ifndef SOLUTION_H
#define SOLUTION_H

#include "headers.h"

// ==============================================
//  SOLUTION - Write your code below
// ==============================================

class Solution {
public:
  int minRemoval(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int i = 0;
    int res = 0;
    for (int j = 0; j < n; j++) {
      while ((long long)nums[j] > k * (long long)nums[i]) {
        i++;
      }
      res = max(res, j - i + 1);
    }

    return n - res;
  }
  void solve() {
    // Your solution here
    TimeSpace::ScopedTimer timer("Solution");
    int n, k;
    cin >> n >> k;
    vi a(n);
    read(a);
    PRINT_CONTAINER(a); // Print space usage of input array
    cout << minRemoval(a, k) << "\n";
  }
};

// Driver wrapper - called by driver.cpp
inline void solve() {
  Solution sol;
  sol.solve();
}

#endif // SOLUTION_H
