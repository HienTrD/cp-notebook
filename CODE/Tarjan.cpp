#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 5;

/**
 * Đối với riêng Tarjan cho cầu khớp sẽ có 2 trường hợp đặc biệt cần lưu ý có thể khiến thuật toán VNOI sai:
 * 1. Đồ thị có nhiều thành phần liên thông.
 * 2. Đồ thị có đúng 2 đỉnh và 1 cạnh.
 * 
 * Trường hợp 1 có thể dễ dàng giải quyết riêng trường hợp 2 thì có một số lưu ý:
 * 1. Nếu như làm các bài liên quan đến cầu, khớp và thuật toán tarjan thì ta nên cài theo kiểu danh sách cạnh thay vì danh sách kề.
 * Vì khi đó mỗi cạnh sẽ chỉ được đi đúng 1 lần (hay có thể hiểu là nếu một cạnh u - v thì ta chỉ xét 1 chiều duy nhất 1 là u -> v 2 là u <- v chứ không xét cùng lúc cả 2 chiều).
 * Việc cài danh sách cạnh đảm bảo định hình được chiều của cạnh.
 * Code được tham khảo từ: GSPVHCUTE
 */

int N, M;
pair<int, int> edge[mxN]; // Danh sách cạnh
vector<int> adj[mxN]; // Mảng lưu danh sách cạnh nếu adj[u] có cạnh id trong tập hợp chứng tỏ có cạnh nối u và một điểm được mã hóa là edge[id].first và edge[id].second.
int num[mxN]; // Tarjan
int low[mxN]; // Tarjan
bitset<mxN> used; // Đánh dấu cạnh đã sử dụng
int child[mxN]; // Đếm số lượng con (nếu số lượng con <= 1 => đỉnh đó là đỉnh lá không thể là khớp)
bitset<mxN> bridge; // Đánh dấu cạnh id là cầu
bitset<mxN> joint; // Đánh dấu đỉnh u là khớp
int cnt_joint = 0, cnt_bridge = 0; // Đếm khớp, cầu
int cnt = 0; // Bộ đo thời gian

void dfs(int u){
  low[u] = num[u] = ++ cnt;
  for(int id : adj[u]){
    if(used[id] == true){
      continue;
    }
    used[id] = true;
    int v = edge[id].first + edge[id].second - u;
    if(num[v] == 0){
      ++ child[u];
      dfs(v);
      low[u] = min(low[u], low[v]);
      if(low[v] > num[u]) bridge[id] = true;
      if(low[v] >= num[u]) joint[u] = true;
    }
    else{
      low[u] = min(low[u], num[v]);
    }
  }
}

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;

  for(int i = 1; i <= M; ++ i){
    int u, v;
    cin >> u >> v;
    edge[i] = make_pair(u, v);
    adj[u].push_back(i);
    adj[v].push_back(i);
  }

  for(int i = 1; i <= N; ++ i){
    if(num[i] == 0){
      dfs(i);
      if(child[i] == 1){
        joint[i] = false;
      }
    }
  }
  
  for(int i = 1; i <= M; ++ i){
    if(bridge[i] == true){
      cnt_bridge ++;
    }
  }

  for(int i = 1; i <= N; ++ i){
    if(joint[i] == true){
      cnt_joint ++;
    }
  }
  cout << cnt_joint << ' ' << cnt_bridge;
  
  return 0;
}
