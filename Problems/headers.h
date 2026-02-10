/**
 * ==============================================
 *  COMPETITIVE PROGRAMMING HEADER
 *  Ultimate Algorithm Library
 * ==============================================
 *  Optimized for Codeforces, CodeChef, AtCoder
 *  Include this in Solution.h for all utilities
 */

#ifndef HEADERS_H
#define HEADERS_H

// ============ COMPILER OPTIMIZATIONS ============
#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("inline")

#pragma GCC target("avx2")
#pragma GCC target("bmi")
#pragma GCC target("bmi2")
#pragma GCC target("popcnt")
#pragma GCC target("lzcnt")

// ============ STANDARD HEADERS ============
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// TimeSpace utilities
#include "../TimeSpace/Space.h"
#include "../TimeSpace/Time.h"

using namespace std;

// ============ TYPE DEFINITIONS ============
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<string> vs;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
typedef set<int> si;
typedef set<ll> sl;
typedef multiset<int> msi;
typedef multiset<ll> msl;

// ============ CONSTANTS ============
const int MOD = 1e9 + 7;
const int MOD2 = 998244353;
const ll INF = 1e18;
const int NINF = INT_MIN;
const int MAXN = 2e5 + 5;
const ld PI = acos(-1.0);
const ld EPS = 1e-9;

// ============ MACROS ============
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define rrep(i, a, b) for (int i = (a); i >= (b); i--)
#define fore(x, v) for (auto &x : v)
#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())

// ============ VECTOR I/O ============
template <typename T> void read(vector<T> &v) { fore(x, v) cin >> x; }
template <typename T> void print(const vector<T> &v) {
  fore(x, v) cout << x << " ";
  cout << '\n';
}

// ============================================================
//                    MATH UTILITIES
// ============================================================

// Basic GCD and LCM
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Extended Euclidean Algorithm: ax + by = gcd(a,b)
// Returns gcd, sets x and y
inline ll extgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll x1, y1;
  ll g = extgcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return g;
}

// Fast modular exponentiation
inline ll power(ll x, ll y, ll mod = MOD) {
  ll res = 1;
  x %= mod;
  if (x < 0)
    x += mod;
  while (y > 0) {
    if (y & 1)
      res = (res * x) % mod;
    x = (x * x) % mod;
    y >>= 1;
  }
  return res;
}

// Modular inverse using Fermat's little theorem
inline ll modInv(ll x, ll mod = MOD) { return power(x, mod - 2, mod); }

// Modular inverse using Extended GCD (works for any mod)
inline ll modInvExtgcd(ll a, ll mod) {
  ll x, y;
  ll g = extgcd(a, mod, x, y);
  if (g != 1)
    return -1; // inverse doesn't exist
  return (x % mod + mod) % mod;
}

// Binomial coefficient nCr
inline ll nCr(ll n, ll r, ll mod = MOD) {
  if (r > n || r < 0)
    return 0;
  ll num = 1, den = 1;
  rep(i, 0, r) {
    num = (num * ((n - i) % mod)) % mod;
    den = (den * ((i + 1) % mod)) % mod;
  }
  return (num * modInv(den, mod)) % mod;
}

// Factorial with memoization
inline vector<ll> factorials(int n, ll mod = MOD) {
  vector<ll> fact(n + 1);
  fact[0] = 1;
  rep(i, 1, n + 1) fact[i] = (fact[i - 1] * i) % mod;
  return fact;
}

// Inverse factorials for fast nCr queries
inline vector<ll> inverseFactorials(const vector<ll> &fact, ll mod = MOD) {
  int n = sz(fact) - 1;
  vector<ll> invFact(n + 1);
  invFact[n] = modInv(fact[n], mod);
  rrep(i, n - 1, 0) invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
  return invFact;
}

// Fast nCr with precomputed factorials
inline ll nCrFast(int n, int r, const vector<ll> &fact,
                  const vector<ll> &invFact, ll mod = MOD) {
  if (r > n || r < 0)
    return 0;
  return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
}

// Euler's Totient Function
inline ll eulerTotient(ll n) {
  ll result = n;
  for (ll p = 2; p * p <= n; p++) {
    if (n % p == 0) {
      while (n % p == 0)
        n /= p;
      result -= result / p;
    }
  }
  if (n > 1)
    result -= result / n;
  return result;
}

// Chinese Remainder Theorem
// Solves: x ≡ r1 (mod m1), x ≡ r2 (mod m2)
// Returns {x, lcm(m1, m2)} or {-1, -1} if no solution
inline pll crt(ll r1, ll m1, ll r2, ll m2) {
  ll x, y;
  ll g = extgcd(m1, m2, x, y);
  if ((r2 - r1) % g != 0)
    return {-1, -1};
  ll lcm_val = m1 / g * m2;
  ll ans = (r1 + m1 * ((r2 - r1) / g % (m2 / g) * x % (m2 / g))) % lcm_val;
  if (ans < 0)
    ans += lcm_val;
  return {ans, lcm_val};
}

// Miller-Rabin Primality Test
inline ll mulmod(ll a, ll b, ll mod) { return (__int128)a * b % mod; }

inline bool millerRabin(ll n, ll a) {
  if (n % a == 0)
    return n == a;
  ll d = n - 1;
  int r = 0;
  while (d % 2 == 0) {
    d /= 2;
    r++;
  }
  ll x = power(a, d, n);
  if (x == 1 || x == n - 1)
    return true;
  rep(i, 0, r - 1) {
    x = mulmod(x, x, n);
    if (x == n - 1)
      return true;
  }
  return false;
}

inline bool isPrime(ll n) {
  if (n < 2)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0)
    return false;
  // Deterministic for n < 3,317,044,064,679,887,385,961,981
  for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a)
      return true;
    if (!millerRabin(n, a))
      return false;
  }
  return true;
}

// Pollard Rho Factorization
inline ll pollardRho(ll n) {
  if (n % 2 == 0)
    return 2;
  ll x = rand() % (n - 2) + 2;
  ll y = x;
  ll c = rand() % (n - 1) + 1;
  ll d = 1;
  while (d == 1) {
    x = (mulmod(x, x, n) + c) % n;
    y = (mulmod(y, y, n) + c) % n;
    y = (mulmod(y, y, n) + c) % n;
    d = gcd(abs(x - y), n);
  }
  return d;
}

// Get all prime factors
inline vector<ll> factorize(ll n) {
  vector<ll> factors;
  if (n == 1)
    return factors;
  if (isPrime(n)) {
    factors.pb(n);
    return factors;
  }
  ll d = pollardRho(n);
  auto f1 = factorize(d);
  auto f2 = factorize(n / d);
  factors.insert(factors.end(), all(f1));
  factors.insert(factors.end(), all(f2));
  sort(all(factors));
  return factors;
}

// ============ BIT MANIPULATION ============
#define setBit(n, i) ((n) | (1LL << (i)))
#define clearBit(n, i) ((n) & ~(1LL << (i)))
#define toggleBit(n, i) ((n) ^ (1LL << (i)))
#define checkBit(n, i) (((n) >> (i)) & 1)
inline int countSetBits(ll n) { return __builtin_popcountll(n); }
inline int trailingZeros(ll n) { return __builtin_ctzll(n); }
inline int leadingZeros(ll n) { return __builtin_clzll(n); }
inline int highestBit(ll n) { return n ? 63 - __builtin_clzll(n) : -1; }
inline ll nextPowerOf2(ll n) { return 1LL << (highestBit(n - 1) + 1); }

// ============ ARRAY UTILITIES ============
template <typename T> T maxElement(const vector<T> &v) {
  return *max_element(all(v));
}
template <typename T> T minElement(const vector<T> &v) {
  return *min_element(all(v));
}
template <typename T> T sum(const vector<T> &v) {
  return accumulate(all(v), T(0));
}
template <typename T> void sortAsc(vector<T> &v) { sort(all(v)); }
template <typename T> void sortDesc(vector<T> &v) { sort(rall(v)); }
template <typename T> void removeDuplicates(vector<T> &v) {
  sort(all(v));
  v.erase(unique(all(v)), v.end());
}
template <typename T> int lowerBoundIdx(const vector<T> &v, T x) {
  return lower_bound(all(v), x) - v.begin();
}
template <typename T> int upperBoundIdx(const vector<T> &v, T x) {
  return upper_bound(all(v), x) - v.begin();
}

// Coordinate Compression
template <typename T> vector<int> compress(const vector<T> &v) {
  vector<T> sorted = v;
  removeDuplicates(sorted);
  vector<int> result(sz(v));
  rep(i, 0, sz(v)) result[i] = lowerBoundIdx(sorted, v[i]);
  return result;
}

// ============ PAIR UTILITIES ============
template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &p) {
  in >> p.first >> p.second;
  return in;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) {
  out << p.first << " " << p.second;
  return out;
}

// ============================================================
//                    PRIME UTILITIES
// ============================================================

// Sieve of Eratosthenes
inline vector<bool> sieve(int n) {
  vector<bool> isPrimeArr(n + 1, true);
  isPrimeArr[0] = isPrimeArr[1] = false;
  for (int i = 2; i * i <= n; i++) {
    if (isPrimeArr[i]) {
      for (int j = i * i; j <= n; j += i) {
        isPrimeArr[j] = false;
      }
    }
  }
  return isPrimeArr;
}

inline vector<int> getPrimes(int n) {
  auto isPrimeArr = sieve(n);
  vector<int> primes;
  rep(i, 2, n + 1) if (isPrimeArr[i]) primes.pb(i);
  return primes;
}

// Linear Sieve - O(n) with smallest prime factor
inline pair<vector<int>, vector<int>> linearSieve(int n) {
  vector<int> spf(n + 1, 0); // smallest prime factor
  vector<int> primes;
  rep(i, 2, n + 1) {
    if (spf[i] == 0) {
      spf[i] = i;
      primes.pb(i);
    }
    for (int p : primes) {
      if (p > spf[i] || i * p > n)
        break;
      spf[i * p] = p;
    }
  }
  return {primes, spf};
}

// ============================================================
//                  STRING ALGORITHMS
// ============================================================

// KMP Failure Function
inline vi kmpFailure(const string &pattern) {
  int m = sz(pattern);
  vi fail(m, 0);
  int j = 0;
  rep(i, 1, m) {
    while (j > 0 && pattern[i] != pattern[j])
      j = fail[j - 1];
    if (pattern[i] == pattern[j])
      j++;
    fail[i] = j;
  }
  return fail;
}

// KMP Pattern Matching - returns all starting positions
inline vi kmpSearch(const string &text, const string &pattern) {
  vi fail = kmpFailure(pattern);
  vi matches;
  int n = sz(text), m = sz(pattern);
  int j = 0;
  rep(i, 0, n) {
    while (j > 0 && text[i] != pattern[j])
      j = fail[j - 1];
    if (text[i] == pattern[j])
      j++;
    if (j == m) {
      matches.pb(i - m + 1);
      j = fail[j - 1];
    }
  }
  return matches;
}

// Z-Function: z[i] = length of longest common prefix of s and s[i:]
inline vi zFunction(const string &s) {
  int n = sz(s);
  vi z(n, 0);
  int l = 0, r = 0;
  rep(i, 1, n) {
    if (i < r)
      z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      z[i]++;
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}

// Rabin-Karp Rolling Hash
class RollingHash {
public:
  static const ll BASE = 31;
  static const ll MOD1 = 1e9 + 7;
  static const ll MOD2 = 1e9 + 9;

  vector<ll> h1, h2, p1, p2;
  int n;

  RollingHash(const string &s) {
    n = sz(s);
    h1.resize(n + 1);
    h2.resize(n + 1);
    p1.resize(n + 1);
    p2.resize(n + 1);
    p1[0] = p2[0] = 1;
    h1[0] = h2[0] = 0;
    rep(i, 0, n) {
      p1[i + 1] = (p1[i] * BASE) % MOD1;
      p2[i + 1] = (p2[i] * BASE) % MOD2;
      h1[i + 1] = (h1[i] * BASE + s[i]) % MOD1;
      h2[i + 1] = (h2[i] * BASE + s[i]) % MOD2;
    }
  }

  // Get hash of substring [l, r)
  pll getHash(int l, int r) {
    ll hash1 = (h1[r] - h1[l] * p1[r - l] % MOD1 + MOD1) % MOD1;
    ll hash2 = (h2[r] - h2[l] * p2[r - l] % MOD2 + MOD2) % MOD2;
    return {hash1, hash2};
  }
};

// Manacher's Algorithm - Longest Palindromic Substring
inline vi manacher(const string &s) {
  string t = "#";
  for (char c : s) {
    t += c;
    t += '#';
  }
  int n = sz(t);
  vi p(n, 0);
  int c = 0, r = 0;
  rep(i, 0, n) {
    if (i < r)
      p[i] = min(r - i, p[2 * c - i]);
    while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n &&
           t[i - p[i] - 1] == t[i + p[i] + 1])
      p[i]++;
    if (i + p[i] > r) {
      c = i;
      r = i + p[i];
    }
  }
  return p;
}

// Get longest palindromic substring
inline string longestPalindrome(const string &s) {
  vi p = manacher(s);
  int maxLen = 0, center = 0;
  rep(i, 0, sz(p)) {
    if (p[i] > maxLen) {
      maxLen = p[i];
      center = i;
    }
  }
  int start = (center - maxLen) / 2;
  return s.substr(start, maxLen);
}

// Trie Data Structure
class Trie {
public:
  struct Node {
    map<char, int> children;
    bool isEnd = false;
    int count = 0; // words passing through
  };

  vector<Node> nodes;

  Trie() { nodes.push_back(Node()); }

  void insert(const string &word) {
    int cur = 0;
    for (char c : word) {
      if (!present(nodes[cur].children, c)) {
        nodes[cur].children[c] = sz(nodes);
        nodes.push_back(Node());
      }
      cur = nodes[cur].children[c];
      nodes[cur].count++;
    }
    nodes[cur].isEnd = true;
  }

  bool search(const string &word) {
    int cur = 0;
    for (char c : word) {
      if (!present(nodes[cur].children, c))
        return false;
      cur = nodes[cur].children[c];
    }
    return nodes[cur].isEnd;
  }

  bool startsWith(const string &prefix) {
    int cur = 0;
    for (char c : prefix) {
      if (!present(nodes[cur].children, c))
        return false;
      cur = nodes[cur].children[c];
    }
    return true;
  }

  int countPrefix(const string &prefix) {
    int cur = 0;
    for (char c : prefix) {
      if (!present(nodes[cur].children, c))
        return 0;
      cur = nodes[cur].children[c];
    }
    return nodes[cur].count;
  }
};

// Suffix Array (O(n log n))
inline vi suffixArray(const string &s) {
  int n = sz(s);
  vi sa(n), rank_(n), tmp(n);
  rep(i, 0, n) {
    sa[i] = i;
    rank_[i] = s[i];
  }

  for (int k = 1; k < n; k *= 2) {
    auto cmp = [&](int a, int b) {
      if (rank_[a] != rank_[b])
        return rank_[a] < rank_[b];
      int ra = a + k < n ? rank_[a + k] : -1;
      int rb = b + k < n ? rank_[b + k] : -1;
      return ra < rb;
    };
    sort(all(sa), cmp);
    tmp[sa[0]] = 0;
    rep(i, 1, n) tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
    rank_ = tmp;
  }
  return sa;
}

// ============================================================
//                    DATA STRUCTURES
// ============================================================

// Disjoint Set Union (Union-Find)
class DSU {
public:
  vector<int> parent, rank_, size_;
  int components;

  DSU(int n) : components(n) {
    parent.resize(n);
    rank_.resize(n, 0);
    size_.resize(n, 1);
    iota(all(parent), 0);
  }

  int find(int x) {
    if (parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  }

  bool unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py)
      return false;
    if (rank_[px] < rank_[py])
      swap(px, py);
    parent[py] = px;
    size_[px] += size_[py];
    if (rank_[px] == rank_[py])
      rank_[px]++;
    components--;
    return true;
  }

  bool connected(int x, int y) { return find(x) == find(y); }
  int getSize(int x) { return size_[find(x)]; }
  int getComponents() { return components; }
};

// Fenwick Tree (Binary Indexed Tree)
class FenwickTree {
public:
  vector<ll> tree;
  int n;

  FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }

  void update(int idx, ll val) {
    for (; idx <= n; idx += idx & -idx)
      tree[idx] += val;
  }

  ll query(int idx) {
    ll sum = 0;
    for (; idx > 0; idx -= idx & -idx)
      sum += tree[idx];
    return sum;
  }

  ll rangeQuery(int l, int r) { return query(r) - query(l - 1); }

  // Find smallest index with prefix sum >= val
  int lowerBound(ll val) {
    int pos = 0;
    ll sum = 0;
    for (int pw = highestBit(n); pw >= 0; pw--) {
      if (pos + (1 << pw) <= n && sum + tree[pos + (1 << pw)] < val) {
        pos += (1 << pw);
        sum += tree[pos];
      }
    }
    return pos + 1;
  }
};

// 2D Fenwick Tree
class FenwickTree2D {
public:
  vector<vector<ll>> tree;
  int n, m;

  FenwickTree2D(int n, int m) : n(n), m(m) {
    tree.assign(n + 1, vector<ll>(m + 1, 0));
  }

  void update(int x, int y, ll val) {
    for (int i = x; i <= n; i += i & -i)
      for (int j = y; j <= m; j += j & -j)
        tree[i][j] += val;
  }

  ll query(int x, int y) {
    ll sum = 0;
    for (int i = x; i > 0; i -= i & -i)
      for (int j = y; j > 0; j -= j & -j)
        sum += tree[i][j];
    return sum;
  }

  ll rangeQuery(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) +
           query(x1 - 1, y1 - 1);
  }
};

// Segment Tree with Lazy Propagation
class SegmentTree {
public:
  vector<ll> tree, lazy;
  int n;

  SegmentTree(int n) : n(n) {
    tree.assign(4 * n, 0);
    lazy.assign(4 * n, 0);
  }

  void pushDown(int node, int start, int end) {
    if (lazy[node] != 0) {
      tree[node] += (end - start + 1) * lazy[node];
      if (start != end) {
        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
      }
      lazy[node] = 0;
    }
  }

  void build(const vector<ll> &arr, int node, int start, int end) {
    if (start == end) {
      tree[node] = arr[start];
    } else {
      int mid = (start + end) / 2;
      build(arr, 2 * node, start, mid);
      build(arr, 2 * node + 1, mid + 1, end);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  void updateRange(int node, int start, int end, int l, int r, ll val) {
    pushDown(node, start, end);
    if (r < start || end < l)
      return;
    if (l <= start && end <= r) {
      lazy[node] += val;
      pushDown(node, start, end);
      return;
    }
    int mid = (start + end) / 2;
    updateRange(2 * node, start, mid, l, r, val);
    updateRange(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
  }

  void updatePoint(int node, int start, int end, int idx, ll val) {
    pushDown(node, start, end);
    if (start == end) {
      tree[node] = val;
    } else {
      int mid = (start + end) / 2;
      if (idx <= mid)
        updatePoint(2 * node, start, mid, idx, val);
      else
        updatePoint(2 * node + 1, mid + 1, end, idx, val);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  ll query(int node, int start, int end, int l, int r) {
    pushDown(node, start, end);
    if (r < start || end < l)
      return 0;
    if (l <= start && end <= r)
      return tree[node];
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) +
           query(2 * node + 1, mid + 1, end, l, r);
  }
};

// Sparse Table (Range Minimum Query)
class SparseTable {
public:
  vector<vector<int>> table;
  vector<int> log2_;
  int n;
  function<int(int, int)> op;

  SparseTable(
      const vector<int> &arr, function<int(int, int)> operation =
                                  [](int a, int b) { return min(a, b); })
      : op(operation) {
    n = sz(arr);
    int k = highestBit(n) + 1;
    table.assign(k, vector<int>(n));
    log2_.resize(n + 1);

    log2_[1] = 0;
    rep(i, 2, n + 1) log2_[i] = log2_[i / 2] + 1;

    table[0] = arr;
    rep(j, 1, k) {
      rep(i, 0, n - (1 << j) + 1) {
        table[j][i] = op(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  int query(int l, int r) {
    int k = log2_[r - l + 1];
    return op(table[k][l], table[k][r - (1 << k) + 1]);
  }
};

// ============================================================
//                  GRAPH ALGORITHMS
// ============================================================

// Add edge to adjacency list
inline void addEdge(vvi &adj, int u, int v, bool directed = false) {
  adj[u].pb(v);
  if (!directed)
    adj[v].pb(u);
}

// BFS - returns distances from start
inline vector<int> bfs(const vvi &adj, int start) {
  int n = sz(adj);
  vi dist(n, -1);
  queue<int> q;
  q.push(start);
  dist[start] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    fore(v, adj[u]) {
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
  return dist;
}

// DFS
inline void dfs(const vvi &adj, int u, vector<bool> &visited) {
  visited[u] = true;
  fore(v, adj[u]) {
    if (!visited[v])
      dfs(adj, v, visited);
  }
}

// 0-1 BFS for graphs with edge weights 0 or 1
inline vi bfs01(const vector<vector<pii>> &adj, int start) {
  int n = sz(adj);
  vi dist(n, INT_MAX);
  deque<int> dq;
  dq.push_back(start);
  dist[start] = 0;

  while (!dq.empty()) {
    int u = dq.front();
    dq.pop_front();
    for (auto [v, w] : adj[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        if (w == 0)
          dq.push_front(v);
        else
          dq.push_back(v);
      }
    }
  }
  return dist;
}

// Dijkstra's Algorithm
inline vll dijkstra(const vector<vector<pll>> &adj, int start) {
  int n = sz(adj);
  vll dist(n, INF);
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  dist[start] = 0;
  pq.push({0, start});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dist[u])
      continue;
    for (auto [v, w] : adj[u]) {
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }
  return dist;
}

// Bellman-Ford Algorithm (handles negative edges)
inline pair<vll, bool>
bellmanFord(int n, const vector<tuple<int, int, ll>> &edges, int start) {
  vll dist(n, INF);
  dist[start] = 0;

  rep(i, 0, n - 1) {
    for (auto [u, v, w] : edges) {
      if (dist[u] != INF && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
      }
    }
  }

  // Check for negative cycle
  for (auto [u, v, w] : edges) {
    if (dist[u] != INF && dist[u] + w < dist[v]) {
      return {dist, true}; // has negative cycle
    }
  }
  return {dist, false};
}

// Floyd-Warshall (All pairs shortest path)
inline vvll floydWarshall(int n, const vector<tuple<int, int, ll>> &edges) {
  vvll dist(n, vll(n, INF));
  rep(i, 0, n) dist[i][i] = 0;
  for (auto [u, v, w] : edges)
    dist[u][v] = min(dist[u][v], w);

  rep(k, 0, n) {
    rep(i, 0, n) {
      rep(j, 0, n) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}

// Topological Sort (Kahn's Algorithm)
inline vi topoSort(const vvi &adj) {
  int n = sz(adj);
  vi inDegree(n, 0);
  rep(u, 0, n) fore(v, adj[u]) inDegree[v]++;

  queue<int> q;
  rep(i, 0, n) if (inDegree[i] == 0) q.push(i);

  vi order;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    order.pb(u);
    fore(v, adj[u]) {
      if (--inDegree[v] == 0)
        q.push(v);
    }
  }

  if (sz(order) != n)
    return {}; // cycle exists
  return order;
}

// Lowest Common Ancestor (Binary Lifting)
class LCA {
public:
  int n, LOG;
  vvi up;
  vi depth;

  LCA(const vvi &adj, int root = 0) {
    n = sz(adj);
    LOG = highestBit(n) + 1;
    up.assign(n, vi(LOG, -1));
    depth.assign(n, 0);
    dfs(adj, root, -1);
  }

  void dfs(const vvi &adj, int u, int p) {
    up[u][0] = p;
    rep(i, 1, LOG) {
      if (up[u][i - 1] != -1)
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    fore(v, adj[u]) {
      if (v != p) {
        depth[v] = depth[u] + 1;
        dfs(adj, v, u);
      }
    }
  }

  int lca(int u, int v) {
    if (depth[u] < depth[v])
      swap(u, v);
    int diff = depth[u] - depth[v];
    rep(i, 0, LOG) if ((diff >> i) & 1) u = up[u][i];
    if (u == v)
      return u;
    rrep(i, LOG - 1, 0) {
      if (up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];
      }
    }
    return up[u][0];
  }

  int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
};

// Tarjan's SCC
class TarjanSCC {
public:
  int n, timer;
  vi disc, low, onStack, comp;
  stack<int> st;
  vvi sccs;

  TarjanSCC(const vvi &adj) {
    n = sz(adj);
    disc.assign(n, -1);
    low.assign(n, 0);
    onStack.assign(n, 0);
    comp.assign(n, -1);
    timer = 0;
    rep(i, 0, n) if (disc[i] == -1) dfs(adj, i);
  }

  void dfs(const vvi &adj, int u) {
    disc[u] = low[u] = timer++;
    st.push(u);
    onStack[u] = 1;

    fore(v, adj[u]) {
      if (disc[v] == -1) {
        dfs(adj, v);
        low[u] = min(low[u], low[v]);
      } else if (onStack[v]) {
        low[u] = min(low[u], disc[v]);
      }
    }

    if (low[u] == disc[u]) {
      vi scc;
      while (true) {
        int v = st.top();
        st.pop();
        onStack[v] = 0;
        comp[v] = sz(sccs);
        scc.pb(v);
        if (v == u)
          break;
      }
      sccs.pb(scc);
    }
  }
};

// Bridges and Articulation Points
class BridgesAP {
public:
  int n, timer;
  vi disc, low, parent;
  vector<bool> isAP;
  vpii bridges;

  BridgesAP(const vvi &adj) {
    n = sz(adj);
    disc.assign(n, -1);
    low.assign(n, 0);
    parent.assign(n, -1);
    isAP.assign(n, false);
    timer = 0;
    rep(i, 0, n) if (disc[i] == -1) dfs(adj, i);
  }

  void dfs(const vvi &adj, int u) {
    disc[u] = low[u] = timer++;
    int children = 0;

    fore(v, adj[u]) {
      if (disc[v] == -1) {
        children++;
        parent[v] = u;
        dfs(adj, v);
        low[u] = min(low[u], low[v]);

        if (parent[u] == -1 && children > 1)
          isAP[u] = true;
        if (parent[u] != -1 && low[v] >= disc[u])
          isAP[u] = true;
        if (low[v] > disc[u])
          bridges.pb({u, v});
      } else if (v != parent[u]) {
        low[u] = min(low[u], disc[v]);
      }
    }
  }
};

// ============================================================
//               DYNAMIC PROGRAMMING UTILITIES
// ============================================================

// Longest Increasing Subsequence O(n log n)
inline vi lis(const vi &arr) {
  vi dp, parent(sz(arr)), pos;
  rep(i, 0, sz(arr)) {
    int idx = lower_bound(all(dp), arr[i]) - dp.begin();
    if (idx == sz(dp))
      dp.pb(arr[i]);
    else
      dp[idx] = arr[i];
    parent[i] = idx > 0 ? pos[idx - 1] : -1;
    if (idx == sz(pos))
      pos.pb(i);
    else
      pos[idx] = i;
  }

  // Reconstruct LIS
  vi result;
  for (int i = pos.back(); i != -1; i = parent[i])
    result.pb(arr[i]);
  reverse(all(result));
  return result;
}

inline int lisLength(const vi &arr) {
  vi dp;
  fore(x, arr) {
    int idx = lower_bound(all(dp), x) - dp.begin();
    if (idx == sz(dp))
      dp.pb(x);
    else
      dp[idx] = x;
  }
  return sz(dp);
}

// Longest Common Subsequence
inline int lcs(const string &a, const string &b) {
  int n = sz(a), m = sz(b);
  vvi dp(n + 1, vi(m + 1, 0));
  rep(i, 1, n + 1) {
    rep(j, 1, m + 1) {
      if (a[i - 1] == b[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return dp[n][m];
}

// 0/1 Knapsack
inline ll knapsack01(const vi &weights, const vll &values, int capacity) {
  int n = sz(weights);
  vll dp(capacity + 1, 0);
  rep(i, 0, n) {
    rrep(w, capacity, weights[i]) {
      dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
    }
  }
  return dp[capacity];
}

// Unbounded Knapsack
inline ll knapsackUnbounded(const vi &weights, const vll &values,
                            int capacity) {
  int n = sz(weights);
  vll dp(capacity + 1, 0);
  rep(w, 1, capacity + 1) {
    rep(i, 0, n) {
      if (weights[i] <= w) {
        dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
      }
    }
  }
  return dp[capacity];
}

// Coin Change (minimum coins)
inline int coinChange(const vi &coins, int amount) {
  vi dp(amount + 1, amount + 1);
  dp[0] = 0;
  rep(i, 1, amount + 1) {
    fore(c, coins) {
      if (c <= i)
        dp[i] = min(dp[i], dp[i - c] + 1);
    }
  }
  return dp[amount] > amount ? -1 : dp[amount];
}

// Coin Change (count ways)
inline ll coinChangeWays(const vi &coins, int amount) {
  vll dp(amount + 1, 0);
  dp[0] = 1;
  fore(c, coins) { rep(i, c, amount + 1) dp[i] += dp[i - c]; }
  return dp[amount];
}

// ============================================================
//                    GEOMETRY
// ============================================================

struct Point {
  ld x, y;
  Point(ld x = 0, ld y = 0) : x(x), y(y) {}
  Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
  Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
  Point operator*(ld t) const { return Point(x * t, y * t); }
  Point operator/(ld t) const { return Point(x / t, y / t); }
  ld dot(const Point &p) const { return x * p.x + y * p.y; }
  ld cross(const Point &p) const { return x * p.y - y * p.x; }
  ld norm() const { return sqrt(x * x + y * y); }
  ld norm2() const { return x * x + y * y; }
  Point rotate(ld angle) const {
    return Point(x * cos(angle) - y * sin(angle),
                 x * sin(angle) + y * cos(angle));
  }
  bool operator<(const Point &p) const {
    if (abs(x - p.x) > EPS)
      return x < p.x;
    return y < p.y;
  }
  bool operator==(const Point &p) const {
    return abs(x - p.x) < EPS && abs(y - p.y) < EPS;
  }
};

// Distance between two points
inline ld dist(const Point &a, const Point &b) { return (a - b).norm(); }

// Cross product of vectors OA and OB
inline ld cross(const Point &O, const Point &A, const Point &B) {
  return (A - O).cross(B - O);
}

// Convex Hull (Graham Scan)
inline vector<Point> convexHull(vector<Point> points) {
  int n = sz(points);
  if (n < 3)
    return points;

  sort(all(points));
  vector<Point> hull;

  // Lower hull
  fore(p, points) {
    while (sz(hull) >= 2 &&
           cross(hull[sz(hull) - 2], hull[sz(hull) - 1], p) <= 0)
      hull.pop_back();
    hull.pb(p);
  }

  // Upper hull
  int lower_size = sz(hull);
  rrep(i, n - 2, 0) {
    while (sz(hull) > lower_size &&
           cross(hull[sz(hull) - 2], hull[sz(hull) - 1], points[i]) <= 0)
      hull.pop_back();
    hull.pb(points[i]);
  }

  hull.pop_back();
  return hull;
}

// Polygon area (signed)
inline ld polygonArea(const vector<Point> &poly) {
  ld area = 0;
  int n = sz(poly);
  rep(i, 0, n) area += poly[i].cross(poly[(i + 1) % n]);
  return area / 2;
}

// ============================================================
//                  MATRIX OPERATIONS
// ============================================================

struct Matrix {
  vvll mat;
  int n, m;
  ll mod;

  Matrix(int n, int m, ll mod = MOD) : n(n), m(m), mod(mod) {
    mat.assign(n, vll(m, 0));
  }

  static Matrix identity(int n, ll mod = MOD) {
    Matrix I(n, n, mod);
    rep(i, 0, n) I.mat[i][i] = 1;
    return I;
  }

  Matrix operator*(const Matrix &other) const {
    assert(m == other.n);
    Matrix result(n, other.m, mod);
    rep(i, 0, n) {
      rep(k, 0, m) {
        if (mat[i][k] == 0)
          continue;
        rep(j, 0, other.m) {
          result.mat[i][j] =
              (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % mod;
        }
      }
    }
    return result;
  }

  Matrix power(ll p) const {
    assert(n == m);
    Matrix result = identity(n, mod);
    Matrix base = *this;
    while (p > 0) {
      if (p & 1)
        result = result * base;
      base = base * base;
      p >>= 1;
    }
    return result;
  }
};

// ============================================================
//                  DEBUG UTILITIES
// ============================================================

#ifndef ONLINE_JUDGE
#define debug(x)                                                               \
  cerr << #x << " = ";                                                         \
  _print(x);                                                                   \
  cerr << endl;
#else
#define debug(x)
#endif

inline void _print(int x) { cerr << x; }
inline void _print(ll x) { cerr << x; }
inline void _print(ld x) { cerr << x; }
inline void _print(double x) { cerr << x; }
inline void _print(char x) { cerr << '\'' << x << '\''; }
inline void _print(string x) { cerr << '\"' << x << '\"'; }
inline void _print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T> void _print(const vector<T> &v) {
  cerr << "[ ";
  fore(x, v) {
    _print(x);
    cerr << " ";
  }
  cerr << "]";
}

template <typename T> void _print(const set<T> &s) {
  cerr << "{ ";
  fore(x, s) {
    _print(x);
    cerr << " ";
  }
  cerr << "}";
}

template <typename T1, typename T2> void _print(const map<T1, T2> &m) {
  cerr << "{ ";
  fore(p, m) {
    cerr << "{";
    _print(p.first);
    cerr << ":";
    _print(p.second);
    cerr << "} ";
  }
  cerr << "}";
}

template <typename T1, typename T2> void _print(const pair<T1, T2> &p) {
  cerr << "{";
  _print(p.first);
  cerr << ",";
  _print(p.second);
  cerr << "}";
}

// ============================================================
//                  MODULAR ARITHMETIC
// ============================================================

struct Mint {
  ll val;
  Mint(ll v = 0) : val(v % MOD) {
    if (val < 0)
      val += MOD;
  }
  Mint operator+(const Mint &o) const { return Mint(val + o.val); }
  Mint operator-(const Mint &o) const { return Mint(val - o.val + MOD); }
  Mint operator*(const Mint &o) const { return Mint(val * o.val); }
  Mint operator/(const Mint &o) const { return *this * o.inv(); }
  Mint inv() const { return Mint(modInv(val)); }
  Mint power(ll p) const { return Mint(::power(val, p, MOD)); }
  bool operator==(const Mint &o) const { return val == o.val; }
  bool operator!=(const Mint &o) const { return val != o.val; }
  friend ostream &operator<<(ostream &os, const Mint &m) { return os << m.val; }
  friend istream &operator>>(istream &is, Mint &m) {
    is >> m.val;
    m.val %= MOD;
    return is;
  }
};

#endif // HEADERS_H