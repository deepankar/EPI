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

int ComputeBinomialCoefficients(int n, int k)
{
   lint cprev=1, d=1;
   for(lint i = k+1; i <=n; i++){
      lint c = cprev*i/d;
      d++;
      cprev=c;
   }
   return cprev;
}

int CheckAns(int n, int k) {
  vector<int> number;
  for (int i = 0; i < k; ++i) {
    number.emplace_back(n - i);
  }

  vector<int> temp;
  for (int i = 2; i <= k; ++i) {
    bool find = false;
    for (int& a : number) {
      if ((a % i) == 0) {
        a /= i;
        find = true;
        break;
      }
    }
    if (find == false) {
      temp.emplace_back(i);
    }
  }

  int res = 1;
  for (const int& a : number) {
    res *= a;
  }

  for (const int& a : temp) {
    res /= a;
  }

  return res;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n, k;
    if (argc == 3) {
      n = atoi(argv[1]), k = atoi(argv[2]);
    } else {
      uniform_int_distribution<int> n_dis(1, 21);
      n = n_dis(gen);
      uniform_int_distribution<int> k_dis(0, n);
      k = k_dis(gen);
    }

    int res = ComputeBinomialCoefficients(n, k);
    cout << "res = " << res << endl;
    assert(res == CheckAns(n, k));
    cout << n << " out of " << k << " = " << res << endl;
    if (argc == 3) {
      break;
    }
  }
  return 0;
}
