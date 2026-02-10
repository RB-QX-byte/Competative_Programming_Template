#ifndef SOLUTION_H
#define SOLUTION_H

#include "headers.h"

// ==============================================
//  SOLUTION - Write your code below
// ==============================================

class Solution {
public:
  void segregate0and1(vector<int> &arr){
    
  }
  void solve() {
    // Your solution here
    TimeSpace::ScopedTimer timer("Solution");
    int n;
    cin >> n;
    vi arr(n);
    read(arr);
    segregate0and1(arr);
    for(auto &num : arr){
      cout<<num<<" ";
    }
  }
};

// Driver wrapper - called by driver.cpp
inline void solve() {
  Solution sol;
  sol.solve();
}

#endif // SOLUTION_H
