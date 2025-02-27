#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/134
 * Code được tham khảo từ: ...
 */

const int mxN = 1e5 + 5;

struct Edge{
  int u, v;
  long long w;
};

int N, M;
Edge edge[mxN];

struct cmp{ // Sắp xếp các cặp cạnh theo W
  bool operator() (const Edge &a, const Edge &b){
    return a.w < b.w;
  }
};

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
    if(u == v){
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

  cin >> N >> M;
  for(int i = 1; i <= M; ++ i){
    cin >> edge[i].u >> edge[i].v >> edge[i].w;
  }

  DisjointSetUnion dsu(N);
  sort(edge + 1, edge + 1 + M, cmp());
  int cnt = 0;
  int cost = 0;
  for(int i = 1; i <= M; ++ i){
    if(cnt > N - 1){
      break;
    }
    int u = edge[i].u;
    int v = edge[i].v;
    long long w = edge[i].w;
    if(dsu.merge(u, v) == true){
      ++ cnt;
      cost += w;
    }
  }
  cout << cost;
  
  return 0;
}
