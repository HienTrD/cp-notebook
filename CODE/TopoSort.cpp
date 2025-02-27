#include <bits/stdc++.h>
using namespace std;

/**
 * Link: ...
 * Code được tham khảo từ: ...
 */

const int mxN = 1e5 + 5;

int N, M;
vector<int> adj[mxN];
int indeg[mxN]; // Lưu bán bậc vào của đỉnh i
vector<int> topo;
queue<int> Q;

int main(void){ 
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;
  for(int i = 1; i <= M; ++ i){
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    indeg[v] ++;  
  }

  for(int i = 1; i <= N; ++ i){
    if(indeg[i] == 0){
      Q.push(i);
      topo.push_back(i);
    }
  }

  while(Q.empty() == false){
    int u = Q.front();
    Q.pop();
    for(int v : adj[u]){
      indeg[v] --;
      if(indeg[v] == 0){
        Q.push(v);
        topo.push_back(v);
      }
    }
  }

  for(const int &x : topo){
    cout << x << ' ';
  }
  
  return 0;
}
