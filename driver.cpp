#include "Problems/Solution.h"

#define FAST_IO                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)

int main() {
  FAST_IO;

#ifndef ONLINE_JUDGE
  freopen("I_and_O\\input.txt", "r", stdin);
  freopen("I_and_O\\output.txt", "w", stdout);
  freopen("I_and_O\\error.txt", "w", stderr);
#endif

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
