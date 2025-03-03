#include <bits/stdc++.h>
using namespace std;

/**
 * Tổng độ phức tạp thời gian:
 * - i = 1 => j lặp N lần
 * - i = 2 => j lặp N / 2 lần
 * - i = 3 => j lặp N / 3 lần
 * - ...
 * - i = N => j lặp 1 lần
 * 
 * => Tổng độ phức tạp thời gian: N + N/2 + N/3 + ... + 1 = O(N ln N)
 * *Lưu ý: Vì sử dụng vector nên thời gian thực tế chậm gấp 2 lần và bộ nhớ nhiều hơn 4 lần.
 */

const int mxN = 1e6 + 5;

int N;
vector<int> uoc[mxN];

void eratosthene(void){
  for(int i = 1; i <= N; ++ i){
    for(int j = i; j <= N; j += i){
      uoc[j].push_back(i);
    }
  }
}

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;
  eratosthene();
  for(int i = 1; i <= N; ++ i){
    cout << i << ": ";
    for(const int &x : uoc[i]){
      cout << x << ' ';
    }
    cout << '\n';
  }
  
  return 0;
}
