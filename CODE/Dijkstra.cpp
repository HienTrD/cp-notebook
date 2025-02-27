#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/174
 * Code được tham khảo từ: 
 */

const int mxN = 2e5 + 5;

struct Edge{
  int v;
  long long w;
};

// 
struct cmp{
  bool operator() (const pair<int, long long> &a, const pair<int, long long> &b){
    return a.second > b.second;
  }
};

int N, M;
vector<Edge> adj[mxN];
int trace[mxN];

vector<long long> dijkstra(int st){
  vector<long long> dist(N + 1, 1e18);
  priority_queue<pair<int, long long>, vector<pair<int, long long>>, cmp> Q;
  dist[st] = 0;
  Q.push(make_pair(st, dist[st]));
  while(Q.empty() == false){
    pair<int, long long> cur = Q.top();
    Q.pop();
    if(dist[cur.first] != cur.second){
      continue;
    }
    for(Edge next : adj[cur.first]){
      if(dist[next.v] > dist[cur.first] + next.w){
        dist[next.v] = dist[cur.first] + next.w;
        Q.push(make_pair(next.v, dist[next.v]));
        trace[next.v] = cur.first;
      }
    }
  }
  return dist;
}

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;
  for(int i = 1; i <= M; ++ i){
    int u, v;
    long long w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  vector<long long> dist = dijkstra(1);
  if(dist[N] == 1e18){
    cout << -1;
    return 0;
  }
  cout << dist[N] << '\n';
  int cur = N;
  vector<int> path;
  while(cur != 0){
    path.push_back(cur);
    cur = trace[cur];
  }
  reverse(path.begin(), path.end());
  for(const int &x : path){
    cout << x << ' ';
  }
  
  return 0;
}
