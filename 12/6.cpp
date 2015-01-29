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

int SquareRoot(int N)
{
   if(!N) return N;
   int L = 1, R = N/2, res =1;
   while(L <= R){
      int m = (L+R)/2;
      int64_t ms = ((int64_t)m)*m;
      if(ms == N){
         return m;
      }
      if(ms < N){
         res = m;
         L = m+1;
      }else{
         R = m-1;
      }
   }
   return res;
}

int main(int argc, char** argv) {
  assert(SquareRoot(0) == 0);
  assert(SquareRoot(1) == 1);
  assert(SquareRoot(121) == 11);
  assert(SquareRoot(64) == 8);
  int x;
  if (argc == 2) {
    x = stoi(argv[1]);
  } else {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(0, numeric_limits<int>::max());
    for (int times = 0; times < 100000; ++times) {
      x = dis(gen);
      int result[2];
      cout << "x is " << x << endl;
      cout << (result[0] = SquareRoot(x)) << ' '
           << (result[1] = static_cast<int>(sqrt(x))) << endl;
      assert(result[0] == result[1]);
    }
  }
  x = 2147395599;
  cout << SquareRoot(x) << endl;
  return 0;
}
