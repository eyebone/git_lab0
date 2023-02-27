#include <fstream>
#include <stdexcept>
#include <string>
#include "SparseMatrix.h"

using namespace std;

void sortRow(SparseMatrix s){
    int *arrRow =
    for(vector<triple>::iterator it = s.data.begin(); it != s.data.end();it++){

    }
}
void sortCol(SparseMatrix s){

}

SparseMatrix::SparseMatrix(const string input_file) {
  /* TODO: Your code here. */
    ifstream infile;
    infile.open(input_file,ios::in);
    if(!infile.is_open()){
        cout<<"read file failed!"<<endl;
        return;
    }
    string buf;
    getline(infile,buf);
    _row = buf[0];
    _col = buf[2];
    buf.clear();
    while(getline(infile,buf)){
        data.push_back({buf[0],buf[2],buf[4]});
        num++;
        buf.clear();
    }



}

void SparseMatrix::to_file(const string output_file) {
  /* TODO: Your code here. */
    fstream file;
    file.open(output_file, ios::out | ios::app);
    if(!file.is_open()){
        cerr << "open out_put file failed!" << endl;
    }
    file << _row << " " << _col << endl;
    int r,c,v;
    for(vector<triple>::iterator it = data.begin(); it != data.end(); it++){
        r = (*it).rv;
        c = (*it).cv;
        v = (*it).val;
        file << rv << " " << cv << " " << val << endl;
    }
    file.close();
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix &right) {
  /* TODO: Your code here. */
  SparseMatrix res;
  if(_col != right._row){
      cout<<"Error: Matrix dimensions do not match!"<< endl;
  }
  /*else if(num * right == 0){//零矩阵
      res._row = _row;
      res._col = right._col;
      //
  }*/
    vector<int> row_ptr(_row + 1, 0);//initialize row pointer
    for(int i = 0; i < num; i++) {
        //Calculate how many non-zero elements there are in row i
        row_ptr[data[i].rv]++;
    }
    //Calculates the prefix sum of an array of row pointer:row_ptr
    for(int i = 0; i < _row; i++) {
        row_ptr[i + 1] += row_ptr[i];
    }
    //calculate
    for(int i = 1;i <= _row; i++){
        for(int j = 1; j <= right._col; j++){
            int sum = 0;

            for(int k = row_ptr[i]; k < row_ptr[i + 1]; k++){
                int col = data[k].cv;
                int v = data[k].val;

                for(int l = 0; l < right.num; l++){
                    if(right.data[l].rv == col && right.data[l].cv == j){
                        sum += val * right.data[l].val;
                        break;
                    }
                }
            }
            if(sum != 0){
                res.data.push_back({i,j,sum});
            }
        }
    }
    res.num = res.data.size();
    res.data.resize(res.num);

    return res;
}