#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/174
 * Code được tham khảo từ: 
 * 
 * Phân tích độ phức tạp thời gian: O(E + VlogV)
 */

const int mxN = 2e5 + 5;

struct Edge{
  int v;
  long long w;
};

// Hàm viết tay để so sánh các phần tử trong min heap (priority_queue)
// Vì mặc định của min heap là từ lớn đến bé nên hàm so sánh phải đảo ngược dấu lại để cho cạnh có trọng số nhỏ nhất được lên đầu
struct cmp{
  bool operator() (const pair<int, long long> &a, const pair<int, long long> &b){
    return a.second > b.second;
  }
};

int N, M;
vector<Edge> adj[mxN];
int trace[mxN]; // Truy vết đường đi

// Hàm trả về một vector chứa khoảng cách gần nhất đến N - 1 đỉnh còn lại
vector<long long> dijkstra(int st){
  vector<long long> dist(N + 1, 1e18);
  priority_queue<pair<int, long long>, vector<pair<int, long long>>, cmp> Q;
  dist[st] = 0;
  Q.push(make_pair(st, dist[st]));
  while(Q.empty() == false){
    pair<int, long long> cur = Q.top();
    Q.pop();
    // Dijkstra mang tính chất gần giống với BFS nhưng trên đồ thị có trọng số
    // Là nếu như đỉnh u hiện đang được xét đến thì chắc chắn đường đi từ điểm bắt đầu (st) đến u là tối ưu hóa nhất có thể
    if(dist[cur.first] != cur.second){ // Vì một đỉnh có thể được tối ưu hóa nhiều lần nên đỉnh u có thể xuất hiện trong min heap nhiều hơn một cái do đó chúng ta cần phải kiếm tra xem liệu hiện tại thì u đang xét
      // có phải là đỉnh đã được tối ưu hóa hoàn toàn hay không
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
