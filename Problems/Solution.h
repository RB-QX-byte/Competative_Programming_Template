#ifndef SOLUTION_H
#define SOLUTION_H

#include "headers.h"

// ==============================================
//  SOLUTION - Write your code below
// ==============================================

class Solution {
public:
  void solve() {
    // Your solution here
    int x, m;
    cin >> x >> m;

    cout << (x - x % m) / m << "\n";
    cout << x % m << "\n";
  }
};

// Driver wrapper - called by driver.cpp
inline void solve() {
  Solution sol;
  sol.solve();
}

#endif // SOLUTION_H
