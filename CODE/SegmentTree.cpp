#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/203
 * Code được tham khảo từ: GSPVHCUTE
 * 
 * Phân tích độ phức tạp thời gian:
 * - Chuẩn bị cây: O(N log N)
 * - Update lazy: O(log N)
 * - Truy vấn: O(log N)
 * 
 * Giải thích về sự khác nhau của update lazy và update điểm
 * Mảng lazy[id] trong bài được tượng trưng cho nếu như node đó lazy[id] != 0 chứng tỏ nếu bài toán là tổng đoạn thì chắc chắn toàn bộ những node con của node id hiện đang xét cũng tăng 
 * Một lượng giá trị là lazy[id] do đó val[id] của node hiện đang xét sẽ tăng một lượng (r - l + 1) * lazy[id]
 * Ngược lại, nếu như đó là min max thì nếu như lazy[id] != 0 chứng tỏ mọi con trong tầm quản lý của node id hiện đang xét đều được tăng lên một lượng giá trị là lazy[id] do đó
 * Min hoặc Max chỉ thay đổi lên hoặc xuống do đó không cần nhân thêm (r - l + 1) vào bên trong
 */

const int mxN = 1e5 + 5;

int N, Q;
int A[mxN];

struct SegmentTree{
  struct Node{
    long long val;
    long long lazy;
  };

  vector<Node> st;
  int N;

  SegmentTree(int sizes){
    N = sizes;
    st.assign(N * 4 + 1, {0, 0});
    build(1, 1, N);
  }

  void down(int id, int l, int r){
    if(st[id].lazy == 0) return;
    
    // Sum case
    int mid = (l + r) >> 1;
    st[id << 1].val += st[id].lazy * (mid - l + 1); // id << 1 <=> id * 2
    st[id << 1 | 1].val += st[id].lazy * (r - mid); // id << 1 | 1 <=> id * 2 + 1
    st[id << 1].lazy += st[id].lazy; // id << 1 <=> id * 2
    st[id << 1 | 1].lazy += st[id].lazy; // id << 1 | 1 <=> id * 2 + 1

    // Max Min
    // st[id << 1].val += st[id].lazy;
    // st[id << 1 | 1].val += st[id].lazy;
    // st[id << 1].lazy += st[id].lazy;
    // st[id << 1 | 1].lazy += st[id].lazy;
    
    st[id].lazy = 0;
  }

  void build(int id, int l, int r){
    if(l == r){
      st[id].val = A[l];
      return;
    }

    int mid = (l + r) >> 1; // <=> mid = (l + r) / 2
  
    build(id << 1, l, mid); // id << 1 <=> id * 2
    build(id << 1 | 1, mid + 1, r); // id << 1 | 1 <=> id * 2 + 1

    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
  }

  // Update range A[i] (L <= i <= R) to A[i] + val
  void update(int id, int l, int r, int a, int b, long long val){
    if(b < l || r < a || a > b || l > r) return;
    if(a <= l && r <= b){
      st[id].val += val * (r - l + 1);
      st[id].lazy += val;
      return;
    }

    down(id, l, r);
    int mid = (l + r) >> 1; // mid = (l + r) >> 1 <=> mid = (l + r) / 2

    update(id << 1, l, mid, a, b, val); // id << 1 <=> id * 2
    update(id << 1 | 1, mid + 1, r, a, b, val); // id << 1 | 1 <=> id * 2 + 1

    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
  }

  long long querry(int id, int l, int r, int a, int b){
    if(b < l || r < a || a > b || l > r) return 0;
    if(a <= l && r <= b) return st[id].val;

    down(id, l, r);
    int mid = (l + r) >> 1; // <=> mid = (l + r) / 2

    return querry(id << 1, l, mid, a, b) + querry(id << 1 | 1, mid + 1, r, a, b);
  }
};

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> Q;
  for(int i = 1; i <= N; ++ i){
    cin >> A[i];
  }

  SegmentTree st(N);
  while(Q --){
    int t;
    cin >> t;
    if(t == 1){
      int l, r, x;
      cin >> l >> r >> x;
      st.update(1, 1, N, l, r, x);
    }
    else{
      int l, r;
      cin >> l >> r;
      cout << st.querry(1, 1, N, l, r) << '\n';
    }
  }
  
  return 0;
}
