/**
 * ==============================================
 *  COMPETITIVE PROGRAMMING HEADER
 * ==============================================
 *  Optimized for Codeforces, CodeChef, AtCoder
 *  Include this in Solution.h for all utilities
 */

#ifndef HEADERS_H
#define HEADERS_H

// ============ COMPILER OPTIMIZATIONS ============
// These pragmas enable aggressive optimizations for faster execution
// They work with GCC and Clang (online judges use GCC)

#pragma GCC optimize("O2") // Enable O2 optimization level
#pragma GCC optimize("O3") // Enable O3 optimization level (more aggressive)
#pragma GCC optimize("unroll-loops") // Unroll loops for speed
#pragma GCC optimize(                                                          \
    "fast-math") // Fast floating-point math (use with caution for precision)
#pragma GCC optimize("inline") // Aggressive inlining

// Target modern CPU features (available on most online judges)
#pragma GCC target("avx2")   // Enable AVX2 SIMD instructions
#pragma GCC target("bmi")    // Bit manipulation instructions
#pragma GCC target("bmi2")   // More bit manipulation
#pragma GCC target("popcnt") // Population count instruction
#pragma GCC target("lzcnt")  // Leading zero count

// Alternative: Use this single line for broader compatibility
// #pragma GCC
// target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

// Standard Library Headers (cross-platform compatible)
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
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

// ============ MATH UTILITIES ============
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

inline ll power(ll x, ll y, ll mod = MOD) {
  ll res = 1;
  x %= mod;
  while (y > 0) {
    if (y & 1)
      res = (res * x) % mod;
    x = (x * x) % mod;
    y >>= 1;
  }
  return res;
}

inline ll modInv(ll x, ll mod = MOD) { return power(x, mod - 2, mod); }

inline ll nCr(ll n, ll r, ll mod = MOD) {
  if (r > n)
    return 0;
  ll num = 1, den = 1;
  rep(i, 0, r) {
    num = (num * (n - i)) % mod;
    den = (den * (i + 1)) % mod;
  }
  return (num * modInv(den, mod)) % mod;
}

// ============ BIT MANIPULATION ============
#define setBit(n, i) ((n) | (1LL << (i)))
#define clearBit(n, i) ((n) & ~(1LL << (i)))
#define toggleBit(n, i) ((n) ^ (1LL << (i)))
#define checkBit(n, i) (((n) >> (i)) & 1)
inline int countSetBits(ll n) { return __builtin_popcountll(n); }
inline int trailingZeros(ll n) { return __builtin_ctzll(n); }
inline int leadingZeros(ll n) { return __builtin_clzll(n); }

// ============ ARRAY UTILITIES ============
template <typename T> T maxElement(const vector<T> &v) {
  return *max_element(all(v));
}

template <typename T> T minElement(const vector<T> &v) {
  return *min_element(all(v));
}

template <typename T> T sum(const vector<T> &v) {
  return accumulate(all(v), 0LL);
}

template <typename T> void sortAsc(vector<T> &v) { sort(all(v)); }

template <typename T> void sortDesc(vector<T> &v) { sort(rall(v)); }

template <typename T> void removeDuplicates(vector<T> &v) {
  sort(all(v));
  v.erase(unique(all(v)), v.end());
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

// ============ DEBUG UTILITIES ============
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

// ============ PRIME UTILITIES ============
inline vector<bool> sieve(int n) {
  vector<bool> isPrime(n + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i * i <= n; i++) {
    if (isPrime[i]) {
      for (int j = i * i; j <= n; j += i) {
        isPrime[j] = false;
      }
    }
  }
  return isPrime;
}

inline vector<int> getPrimes(int n) {
  auto isPrime = sieve(n);
  vector<int> primes;
  rep(i, 2, n + 1) {
    if (isPrime[i])
      primes.pb(i);
  }
  return primes;
}

// ============ DSU (Disjoint Set Union) ============
class DSU {
public:
  vector<int> parent, rank_;

  DSU(int n) {
    parent.resize(n);
    rank_.resize(n, 0);
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
    if (rank_[px] == rank_[py])
      rank_[px]++;
    return true;
  }
};

// ============ FENWICK TREE (BIT) ============
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
};

// ============ SEGMENT TREE ============
class SegmentTree {
public:
  vector<ll> tree;
  int n;

  SegmentTree(int n) : n(n) { tree.assign(4 * n, 0); }

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

  void update(int node, int start, int end, int idx, ll val) {
    if (start == end) {
      tree[node] = val;
    } else {
      int mid = (start + end) / 2;
      if (idx <= mid)
        update(2 * node, start, mid, idx, val);
      else
        update(2 * node + 1, mid + 1, end, idx, val);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  ll query(int node, int start, int end, int l, int r) {
    if (r < start || end < l)
      return 0;
    if (l <= start && end <= r)
      return tree[node];
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) +
           query(2 * node + 1, mid + 1, end, l, r);
  }
};

// ============ GRAPH UTILITIES ============
inline void addEdge(vvi &adj, int u, int v, bool directed = false) {
  adj[u].pb(v);
  if (!directed)
    adj[v].pb(u);
}

// BFS
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

// ============ MODULAR ARITHMETIC ============
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
  friend ostream &operator<<(ostream &os, const Mint &m) { return os << m.val; }
};

#endif // HEADERS_H