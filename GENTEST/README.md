Code sinh test ở trên được làm một cách thật tinh gọn và tập chung đến những dạng chính (đồ thị có tồn tại chu trình / không tồn tại chu trình, cây, DAG, ...).

Nên những điều kiện nhỏ có thể không xuất hiện, ví dụ:
- Đồ thị có trọng số (có thể in số random).
- Đồ thị không tồn tại khuyên, cạnh song song.

Hướng dẫn sinh các loại đồ thị đặc biệt:
- Đồ thị cây dạng đường thẳng:
  - Có thể sinh hoán vị rồi nối cạnh i - i + 1 (với mọi i thuộc 1 <= i <= N - 1).
