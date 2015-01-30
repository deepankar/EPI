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

int partition(VI::iterator b, VI::iterator e)
{
   int num = e-b;
   assert(num > 1);
   VI::iterator s = b+1;
   VI::iterator n = s;
   while(n != e){
      if(*n > *b){
         swap(*s, *n);
         s++;
      }
      n++;
   }
   swap(*(s-1), *b);
   return s-1-b;
}

int kth(VI::iterator b, VI::iterator e, int k)
{
   int n = e-b;
   assert(n > 0);
   if(n==1)
   {
      assert(k==0);
      return *b;
   }
   int ri = rand() % n;
   swap(*b, *(b+ri));
   int pi = partition(b,e);
   if(pi == k){
      return *(b+pi);
   }else if(pi < k){
      return kth(b+pi+1, e, k-pi-1);
   }else{
      return kth(b, b+pi, k);
   }
}

int FindKthLargest(VI &a, int k)
{
   assert(k > 0 && k <= a.size());
   return kth(a.begin(), a.end(), k-1);
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n, k;
    if (argc == 2) {
      n = atoi(argv[1]);
      uniform_int_distribution<int> k_dis(1, n);
      k = k_dis(gen);
    } else if (argc == 3) {
      n = atoi(argv[1]), k = atoi(argv[2]);
    } else {
      uniform_int_distribution<int> n_dis(1, 100000);
      n = n_dis(gen);
      uniform_int_distribution<int> k_dis(1, n - 1);
      k = k_dis(gen);
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(0, 9999999);
      A.emplace_back(dis(gen));
    }
    int result = FindKthLargest(A, k);
    nth_element(A.begin(), A.begin() + A.size() - k, A.end());
    assert(result == A[A.size() - k]);
  }
  return 0;
}
