#include <limits.h>
#include <iterator>
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
typedef vector<PI> VPI;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

int FindStartCity(const VI &g, const VI &d)
{
   assert(g.size() == d.size());
#define delta(i) (g[i] - d[i])
   int n = g.size();
   int i = -1, j = n;
   int sum = 0;
   int k = 0;
   FOR0(k, n){
      if(sum >= 0){ //go fwd
         i++;
         sum += delta(i);
      }else{
         j--;
         sum += delta(j);
      }
   }
   if(j == n) return 0;
   return j;
}

void CheckAns(const vector<int>& G, const vector<int>& D, size_t c) {
  size_t s = c;
  int gas = 0;
  do {
    gas += G[s] - D[s];
    assert(gas >= 0);
    s = (s + 1) % G.size();
  } while (s != c);
}

void SmallTest() {
  // Example in the book.
  vector<int> G = {20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25};
  vector<int> D = {15, 20, 50, 15, 15, 30, 20, 55, 20, 50, 10, 15, 15};
  size_t ans = FindStartCity(G, D);
  assert(ans == 8);
  CheckAns(G, D, ans);
}

int main(int argc, char* argv[]) {
  SmallTest();
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<int> G, D;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(1, 200);
      int x = dis(gen);
      sum += x;
      G.emplace_back(x);
    }
    sum -= n;
    for (int i = 0; i < n; ++i) {
      int x = 0;
      if (sum) {
        uniform_int_distribution<int> dis(1, sum);
        x = dis(gen);
      }
      D.emplace_back(x + 1);
      sum -= x;
    }
    D.back() += sum;
    /*
    for (int i = 0; i < n; ++i) {
      cout << G[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
      cout << D[i] << ' ';
    }
    cout << endl;
    */
    size_t c = FindStartCity(G, D);
    cout << "start city = " << c << endl;
    CheckAns(G, D, c);
  }
  return 0;
}
