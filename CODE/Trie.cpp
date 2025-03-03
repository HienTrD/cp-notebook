#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/237
 * Code được tham khảo từ: GSPVHCUTE
 * 
 * Phân tích độ phức tạp thời gian: O(N * K).
 * Trong đó N là độ dài mỗi xâu tối đa
 * Trong đó K là số lượng xâu tối đa
 * 
 * Bài này vì lí do Trie ăn quá nhiều bộ nhớ trong MarisaOJ chỉ chấp nhận 256MB nên chúng ta phải dùng cấu trúc mảng động để tạo cây
 * Ngược lại nếu như trong mọi trường hợp có thể (số lượng node của cây tối đa 10^6) thì chúng ta nên sử dụng mảng cứng để tiết kiệm thời gian
 * Vì hàm new trong C++ chạy rất chậm (nếu là cây có rất nhiều node thì thời gian chạy có thể gấp 3-4 lần dùng mảng cứng)
 * Vì Trie là cấu trúc dữ liệu chạy bằng con trỏ nên nó ăn rất nhiều bộ nhớ + thời gian chạy (mỗi con trỏ là 8 bytes)
 * Khi sử dụng mảng cứng có thể bỏ command của những lệnh ở trong cây Trie ở dưới và chuyển thành command cho những lệnh còn lại với tên y chang
 */

const int ALPHABET = 26;
const int mxN = 1e6 + 5;

int N;
bool ok = false;

struct Trie{
  struct Node{
    Node* child[ALPHABET];
    Node(){
      for(int i = 0; i <= 25; ++ i){
        child[i] = nullptr;
      }
    }
  };

  Node* root = new Node();

  // Nếu số lượng tối đa của toàn bộ cây không vượt quá 10^6 node hoặc không bị quá bộ nhớ thì mở comment đoạn dưới và comment đoạn trên
  // int TrieNodeCnt = 0;
  // Node* root = createNode();
  // Node nodes[mxN];

  // Node* createNode(void){
  //   return &nodes[TrieNodeCnt ++];
  // }

  void add(const string &s){
    Node* p = root;
    bool temp = true;
    for(char c : s){
      if(p->child[c - 'a'] == nullptr){
        p->child[c - 'a'] = new Node();
        temp = false;
      }
      p=p->child[c - 'a'];
    }
    ok |= temp;
  }
};

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;
  Trie trie;
  for(int i = 1; i <= N; ++ i){
    string s;
    cin >> s;
    trie.add(s);
    if(ok == true){
      cout << "YES";
      return 0;
    }
  }
  cout << "NO";
  
  return 0;
}
