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

void DutchFlagPartition(int i, vector<int> &a)
{
//   cout <<"i=" << i << endl;
   if(a.size() <= 1) return;
   int p = a[i];
   int n = a.size();
   swap(a[0], a[i]);
   int nxt = 1, b = 1;
   while(nxt < n){
      if(a[nxt] <= p){
         swap(a[b], a[nxt]);
         b++;
      }
      nxt++;
   }
   b--;
   while(b >= 0 && a[b] == p)  b--;
   int j = 0;
   while(j < b){
      if(a[j] == p){
         swap(a[j], a[b]);
         while(b >= 0 && a[b] == p)  b--;
      }
      j++;
   }
}
vector<int> RandVector(int len) {
  default_random_engine gen((random_device())());
  vector<int> ret;
  while (len--) {
    uniform_int_distribution<int> dis(0, 2);
    ret.emplace_back(dis(gen));
  }
  return ret;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 100);
      n = dis(gen);
    }
    vector<int> A(RandVector(n));
    uniform_int_distribution<int> dis(0, A.size() - 1);
    int pivot_index = dis(gen);
    int pivot = A[pivot_index];
//    cout << "P=" << pivot <<endl;
//    pv(A);
    DutchFlagPartition(pivot_index, A);
//    pv(A);
    int i = 0;
    while (A[i] < pivot && i < A.size()) {
      cout << A[i] << ' ';
      ++i;
    }
    while (A[i] == pivot && i < A.size()) {
      cout << A[i] << ' ';
      ++i;
    }
    while (A[i] > pivot && i < A.size()) {
      cout << A[i] << ' ';
      ++i;
    }
    cout << endl;
    assert(i == A.size());
  }
  return 0;
}
