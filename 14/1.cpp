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

#include "./Intersect_sorted_arrays1.h"
#include "./Intersect_sorted_arrays2.h"
#include "./Intersect_sorted_arrays3.h"

#define FOR0(i, n) for(int i = 0; i < n; i++)

VI f(const VI &a, const VI &b)
{
   VI c;
   int i = 0, j=0;
   int m = a.size(), n = b.size();
   while(i < m && j < n){
      if(a[i] == b[j]){
         if(c.empty() || c.back() != a[i]){
            c.push_back(a[i]);
         }
         i++;
         j++;
      }else if(a[i] < b[j]){
         i++;
      }else{
         j++;
      }
   }
   return c;
}
void CheckAns(const vector<int> &a, const vector<int> &b,
              const vector<int> &c) {
  cout << a.size() << ' ' << b.size() << ' ' << c.size() << endl;
  assert(a.size() == b.size());
  assert(b.size() == c.size());
  for (int i = 0; i < a.size(); ++i) {
    assert(a[i] == b[i]);
    assert(b[i] == c[i]);
  }
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n, m;
    vector<int> A, B;
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen), m = dis(gen);
    }
    uniform_int_distribution<int> n_dis(0, n - 1);
    for (int i = 0; i < n; ++i) {
      A.emplace_back(n_dis(gen));
    }
    uniform_int_distribution<int> m_dis(0, m - 1);
    for (int j = 0; j < m; ++j) {
      B.emplace_back(m_dis(gen));
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    vector<int> res1 = f(A, B);
    vector<int> res2 = IntersectTwoSortedArrays2::IntersectTwoSortedArrays(A, B);
    vector<int> res3 = IntersectTwoSortedArrays3::IntersectTwoSortedArrays(A, B);
    CheckAns(res1, res2, res3);
  }
  return 0;
}
