#pragma once

#include <string>
#include <vector>
using namespace std;

struct triple{
    int rv;//row_val
    int cv;//col_val
    int val;//value
};


class SparseMatrix {
private:

  /* TODO: Add any necessary data structure here. */
  int _row;//usual(?) matrix row
  int _col;//usual(...?) matrix col
  int num = 0;//Number of non-zero elements
  vector<triple> data;//sparse matrix triple data
public:


  SparseMatrix() = default;
  ~SparseMatrix();
//构造函数
  SparseMatrix(const string input_file);
//储存为文件
  void to_file(const string output_file);
//运算
  SparseMatrix operator*(const SparseMatrix &right);

};