Lưu ý rằng phần code ở dưới chưa bao gồm các trường hợp đặc biệt của đồ thị như:
- Đồ thị có trọng số.
- Đồ thị không tồn tại khuyên và cạnh song song (Vì sinh random nên những trường hợp này có thể xảy ra).

Để có thể sinh được có trọng số thì có thể in ra số random cho mỗi trọng số cạnh.

*Lưu ý: Nếu như dùng thuật toán random đồ thị dưới 10 đỉnh thì có tỉ lệ xấp xỉ 90% tồn tại cạnh song song (hoặc có thể hiểu là một cạnh bị lặp lại nhiều lần).
- Tỉ lệ xuất hiện giảm dần nếu số lượng đỉnh tăng dần.

Trường hợp sinh cây dạng đường thẳng thì có thể coi như một trường hợp đặc biệt của DAG nhưng chỉ sinh hoán vị + nối các cạnh i - i + 1 (1 <= i <= N - 1) lại với nhau là được.

Để sinh có nhiều thành phần liên thông thì có thể điều chỉnh hàm sinh của đồ thị lại và sinh nhiều khoảng với nhau ví dụ:
- Để sinh nhiều thành phần liên thông như 1 - 5 và 6 - 10 thì ta chỉnh lại phần sinh hoán vị để hàm chỉ sinh trong khoảng [L, R]  sau đó nối cạnh như thường và in ra đồ thị nhiều lần tùy thuộc vào số lượng thành phần liên thông.
