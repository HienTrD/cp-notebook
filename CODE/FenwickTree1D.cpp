#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/201
 * Code được tham khảo từ: GSPVHCUTE
 */

struct FenwickTree{
  vector<long long> bit_1;
  vector<long long> bit_2;
  int N;

  FenwickTree(int sizes){
    N = sizes;
    bit_1.assign(N + 1, 0);
    bit_2.assign(N + 1, 0);
  }

  void update(vector<long long> &ft, int x, long long val){
    for(; x <= N; x += x & -x){
      ft[x] += val;
    }
  }

  long long get(vector<long long> &ft, int x){
    long long res = 0;
    for(; x >= 1; x -= x & -x){
      res += ft[x];
    }
    return res;
  }

  void updateLazy(int l, int r, long long val){
    update(bit_1, l, 1LL * (N - l + 1) * val);
    update(bit_1, r + 1, 1LL * -(N - r) * val);
    update(bit_2, l, val);
    update(bit_2, r + 1, -val);
  }

  long long getPrefixSum(int x){
    return get(bit_1, x) - 1LL * get(bit_2, x) * (N - x);
  }

  long long getRange(int l, int r){
    return getPrefixSum(r) - getPrefixSum(l - 1);
  }
};

const int mxN = 1e5 + 5;

int N, Q;
long long A[mxN];

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> Q;
  for(int i = 1; i <= N; ++ i){
    cin >> A[i];
  }

  FenwickTree ft(N);
  for(int i = 1; i <= N; ++ i){
    ft.updateLazy(i, i, A[i]);
  }

  while(Q --){
    int t;
    cin >> t;
    if(t == 1){
      int i, x;
      cin >> i >> x;
      ft.updateLazy(i, i, x - A[i]);
      A[i] = x;
    }
    else{
      int l, r;
      cin >> l >> r;
      cout << ft.getRange(l, r) << '\n';
    }
  }
  
  return 0;
}
