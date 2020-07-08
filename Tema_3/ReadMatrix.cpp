#include <iostream>
#include <fstream>

using namespace std;

int main() {

  int n;
  ifstream myfile;
  myfile.open ("mat1");
  myfile >> n;
  int mat[n][n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      myfile >> mat[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << mat[i][j];
    }
    cout << endl;
  }
  return 0;
}