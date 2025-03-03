#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/130
 * Code được tham khảo từ: ...
 * 
 * Phân tích độ phức tạp thời gian: O(log log N).
 */

int N, Q;

struct DisjointSetUnion{
  vector<int> sz;
  vector<int> par;
  int N;

  DisjointSetUnion(int sizes){
    N = sizes;
    sz.assign(N + 1, 1);
    par.assign(N + 1, -1);
  }

  int root(int u){
    if(par[u] < 0){
      return u;
    }
    else{
      par[u] = root(par[u]);
      return par[u];
    }
  }

  bool merge(int u, int v){
    u = root(u);
    v = root(v);
    if(u == v){ // Chung một thành phần liên thông không cần nối lại
      return false;
    }
    if(sz[v] > sz[u]){
      swap(u, v);
    }
    sz[u] += sz[v];
    par[v] = u;
    return true;
  }
};

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> Q;
  DisjointSetUnion dsu(N);
  while(Q --){
    int t;
    cin >> t;
    if(t == 1){
      int u, v;
      cin >> u >> v;
      dsu.merge(u, v);
    }
    else{
      int u, v;
      cin >> u >> v;
      cout << (dsu.root(u) == dsu.root(v) ? "YES" : "NO") << '\n';
    }
  }
  
  return 0;
}
