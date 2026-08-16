#include <bits/stdc++.h>
using namespace std;

int minOp(int a, int b) { return min(a, b); }
int maxOp(int a, int b) { return max(a, b); }
int sumOp(int a, int b) { return a + b; }

template <typename T>
class SegmentTree {
 private:
  int n;
  vector<T> dat;
  T init_value;
  T (*op)(T, T);
  T querySub(int left, int right, int node, int node_left, int node_right);

 public:
  SegmentTree(int size, T init_value, T (*op)(T, T));
  void update(int index, T value);
  T query(int left, int right);
};

/*
input
5 4
8 3 7 2 6
1 0 5
1 1 4
0 3 10
1 0 5

output
function : 2
lambda   : 2
function : 2
lambda   : 2
function : 3
lambda   : 3
*/
int main() {
  int n, q;
  cin >> n >> q;
  // ① 演算関数を使用したSegmentTree
  SegmentTree<int> minseg_function(n, INT_MAX, minOp);
  // ② ラムダ式を使用したSegmentTree
  SegmentTree<int> minseg_lambda(n, INT_MAX,
                                 [](int a, int b) { return min(a, b); });
  // 初期値を両方のSegmentTreeに設定
  for (int i = 0; i < n; i++) {
    int value;
    cin >> value;
    minseg_function.update(i, value);
    minseg_lambda.update(i, value);
  }
  for (int i = 0; i < q; i++) {
    int type;
    cin >> type;
    if (type == 0) {
      int index, value;
      cin >> index >> value;
      minseg_function.update(index, value);
      minseg_lambda.update(index, value);
    } else if (type == 1) {
      int left, right;
      cin >> left >> right;
      cout << "function : " << minseg_function.query(left, right) << '\n';
      cout << "lambda   : " << minseg_lambda.query(left, right) << '\n';
    }
  }
  return 0;
}

template <typename T>
SegmentTree<T>::SegmentTree(int size, T init_value, T (*op)(T, T)) {
  n = 1;
  while (n < size) n *= 2;
  this->init_value = init_value;
  this->op = op;
  dat.resize(2 * n - 1, init_value);
}

template <typename T>
void SegmentTree<T>::update(int index, T value) {
  index = n - 1 + index;
  dat[index] = value;

  while (index > 0) {
    index = (index - 1) / 2;
    dat[index] = op(dat[2 * index + 1], dat[2 * index + 2]);
  }
}

template <typename T>
T SegmentTree<T>::query(int left, int right) {
  return querySub(left, right, 0, 0, n);
}

template <typename T>
T SegmentTree<T>::querySub(int left, int right, int node, int node_left,
                           int node_right) {
  if (right <= node_left || node_right <= left) return init_value;
  if (left <= node_left && node_right <= right) return dat[node];
  int mid = (node_left + node_right) / 2;
  return op(querySub(left, right, 2 * node + 1, node_left, mid),
            querySub(left, right, 2 * node + 2, mid, node_right));
}