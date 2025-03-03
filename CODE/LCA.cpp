#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/191
 * Code được tham khảo từ: GSPVHCUTE
 * 
 * Phân tích độ phức tạp thời gian:
 * - DFS: O(E + V)
 * - Tính LCA: O(log E)
 * - Truy vấn LCA: O(log E)
 */

const int mxN = 1e5 + 5;
const int LOG = 19;

int N, Q;
vector<int> adj[mxN];
int high[mxN]; // Độ cao đỉnh đang xét
int par[mxN][LOG + 1]; // i là đỉnh đang xét còn j là tổ tiên thứ 2^j của đỉnh i

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
  // Ở đây sau khi biết được tổ tiên bước 2^0 = 1 bước của đỉnh i thì chúng ta bắt đầu tính tiếp tổ tiên của i nhưng bước 2^j bước
  // Chúng ta có công thức quy hoạch động: 2^j = 2^(j - 1) + 2^(j - 1) hay để tính được tổ tiên của đỉnh i nhưng bước 2 bước thì ta bước lên 2^(1 - 1) = 1 bước rồi bước thêm 2^(1 - 1) = 1 bước nữa
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
