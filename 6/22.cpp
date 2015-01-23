#include <limits.h>
#include <limits>
#include <random>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <stdint.h>
#include <sstream>
using namespace std;
typedef uint8_t u8;
typedef vector<u8> VU8;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef vector<bool> VB;
typedef pair<int,int> PI;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

#if 1
#define C cout
#else
#include <fstream>
ofstream C("/dev/null");
#endif

#if 1
#define INS \
{ \
   static int calls; \
   calls++; \
   cout << __FUNCTION__ << ":" << calls << endl; \
}
#else
#define INS 
#endif
template<class T>
void pv(const vector<T> &v){
   if(!v.size()){
      cout <<"{}\n";
      return;
   }
   cout << "{";
   FOR0(i,v.size()-1){
      cout << v[i] <<", ";
   }
   cout << v[v.size()-1] << "}\n";
}

void PrintMatrixInSpiralOrder(const VVI &a)
{
   int n = a.size();
   cout <<"N=" << n << endl;
   int y1=0, x1=0;
   int y2=n-1, x2=n-1;
   while(y1 <= y2 && x1 <= x2){
      for(int x = x1; x <=x2; x++){
         cout << a[y1][x] << ' ';
      }
      y1++;
      for(int y = y1; y <=y2; y++){
         cout << a[y][x2] << ' ';
      }
      x2--;
      for(int x = x2; x>=x1; x--){
         cout << a[y2][x] << ' ';
      }
      y2--;
      for(int y = y2; y >= y1; y--){
         cout << a[y][x1]  << ' ';
      }
      x1++;
   }
   cout << endl;
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  int N;
  if (argc == 2) {
    N = atoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 50);
    N = dis(gen);
  }
  vector<vector<int>> A(N, vector<int>(N));
  int x = 1;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      A[i][j] = x++;
    }
  }
  PrintMatrixInSpiralOrder(A);
  return 0;
}
