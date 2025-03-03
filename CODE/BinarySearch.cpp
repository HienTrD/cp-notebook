#include <bits/stdc++.h>
using namespace std;

/**
 * Link: https://marisaoj.com/problem/515
 * Code được tham khảo từ: Yugihacker
 * 
 * Giải thích sơ về cách hoạt động của hàm tìm kiếm nhị phân bên dưới:
 * - Đầu tiên khác với cách TKNP của VNOI hàm bên dưới sẽ CHỈ TRẢ LẠI KẾT QUẢ KHI TÌM KIẾM HẾT 2 BIÊN [L, R]
 * - Hai cận HI và LO sẽ dừng khi chia mảng thành 2 phần riêng biệt là [1, lo] và [hi, N]. 
 * Trong đó để biết tìm kết quả như nào thì ta sẽ phân tích bài toán (phần ở dưới).
 * 
 * - Đầu tiên để sử dụng được hàm bên dưới phải hiểu được cách tư duy của tìm kiếm nhị phân là:
 * + Xác định xem giá trị cần tìm là cận phải true hay cận trái của false (xét trong một dãy là true - false nếu ngược lại thì đổi dấu của hàm lại). 
 * Ví dụ như ở link ở trên thì đề bài yêu cầu phải IN RA VỊ TRÍ CỦA PHẦN TỬ X TRONG MẢNG A thì vì mảng A đã được sắp xếp nên để kiếm được vị trí của X thì ta có thể:
 * + Nếu chọn <= và chúng ta cần tìm 4 trong mảng gồm 1 4 6 8 10 thì mảng đó sẽ là true true false false false (mọi giá trị <= x sẽ là true và > x sẽ là false). Khi đó kết quả sẽ là cận phải xa nhất của true
 * + Nếu chọn >= và chúng ta cần tìm 4 trong mảng gầm 1 4 6 8 10 thì mảng đó sẽ là false true true true true (mọi giá trị >= x sẽ là true và < x sẽ là false). Khi đó kết quả sẽ là cận trái xa nhất của true.
 * 
 * Những điểm đặc biệt của code TKNP theo kiểu của Yugihacker:
 * - Nếu chặt <= x và mọi phần tử của mảng đều > x thì cnp sẽ trả về l - 1.
 * - Ngược lại nếu chặt >= x và mọi phần tử của mảng đều < x thì cnp sẽ trả về r + 1.
 * -*Cách hoạt động rất giống của lower_bound và upper_bound của C++
 * - Và đặc biệt nó còn có thể tùy chỉnh tùy theo bài toán.
 * Link 2: https://marisaoj.com/problem/76
 * solve link 2: https://ideone.com/9tDK9U
 * 
 * Tóm tắt tìm i NHỎ NHẤT hay cận trái xa nhất của true do đó chỉ cần điều chỉnh thành >= và trả về hi là được (nếu là cận phải xa nhất của true thì trả về lo còn cận trái xa nhất là hi). 
 * 
 * Code này của Yugihacker sẽ LUÔN ĐẢM BẢO SẼ TÌM ĐƯỢC KẾT QUẢ nhưng lưu ý trong trường hợp <= thì có thể không tồn tại = mà sẽ trả về < và ngược lại với >= thì có thể không có trường hợp = mà có trường hợp >.
 */

const int mxN = 1e5 + 5;

int N, Q;
int A[mxN];

int cnp(int x, int l, int r){
  int lo = l - 1;
  int hi = r + 1;
  while(hi - lo > 1){
    int mid = hi + lo >> 1;
    if(A[mid] <= x) lo = mid;
    else hi = mid;
  }
  return lo;
}

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> Q;
  for(int i = 1; i <= N; ++ i){
    cin >> A[i];
  }

  while(Q --){
    int x;
    cin >> x;
    cout << cnp(x, 1, N) << '\n';
  }
  
  return 0;
}
