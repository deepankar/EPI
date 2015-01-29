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

int SearchFirstOfK(VI &a, int k)
{
   int L = 0, R = a.size()-1;
   if(a[R] < k) return -1;
   while(L <= R){
      int m = (L+R)/2;
      if(a[m] == k){
         if(m == 0 || a[m-1] != k){
            return m;
         }
         //a[m-1] == k
         R = m-1;
      }else if(a[m] < k){
         L = m+1;
      }else{
         R = m-1;
      }
   }
   return -1;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 100000);
      n = dis(gen);
    }
    vector<int> A;
    uniform_int_distribution<int> k_dis(0, n - 1);
    int k = k_dis(gen);
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(0, n - 1);
      A.emplace_back(dis(gen));
    }
    sort(A.begin(), A.end());
    int ans = SearchFirstOfK(A, k);
    cout << "k = " << k << " locates at " << ans << endl;
    if (ans != -1) {
      cout << "A[k] = " << A[ans] << endl;
    }
    auto it = find(A.cbegin(), A.cend(), k);
    assert((it == A.cend() && ans == -1) || (distance(A.cbegin(), it) == ans));
  }
  return 0;
}
