#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/191
 */

const int mxN = 1e5 + 5;
const int LOG = 19;

int N, Q;
vector<int> adj[mxN];
int high[mxN];
int par[mxN][LOG + 1];

void dfs(int u){
  for(int v : adj[u]){
    if(v != par[u][0]){
      par[v][0] = u;
      high[v] = high[u] + 1;
      dfs(v);
    }
  }
}

int lca(int u, int v){
  if(high[v] > high[u]){
    return lca(v, u);
  }

  for(int j = LOG; j >= 0; -- j){
    if(high[par[u][j]] >= high[v]){
      u = par[u][j];
    }
  }

  if(u == v){
    return u;
  }

  for(int j = LOG; j >= 0; -- j){
    if(par[u][j] != par[v][j]){
      u = par[u][j];
      v = par[v][j];
    }
  }

  return par[u][0];
}

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> Q;
  for(int i = 1; i <= N - 1; ++ i){
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1);
  for(int j = 1; j <= LOG; ++ j){
    for(int i = 1; i <= N; ++ i){
      par[i][j] = par[par[i][j - 1]][j - 1];
    }
  }
  high[0] = -1;

  while(Q --){
    int u, v;
    cin >> u >> v;
    cout << lca(u, v) << '\n';
  }
  
  return 0;
}
