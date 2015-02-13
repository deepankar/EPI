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

int LevenshteinDistance(const string &a, const string &b){
   VI ed[2];
   ed[0].resize(a.size()+1);
   ed[1].resize(a.size()+1);
   int k=0;
   for(int i = 0; i <= a.size(); i++){
      ed[k][i] = i;
   }
   for(int j = 1; j <=b.size(); j++){
      k = 1-k;
      ed[k][0] = j;
      for(int i = 1; i <= a.size(); i++){
         int o1 = ed[k][i-1] + 1;
         int o2 = ed[1-k][i] + 1;
         int o3 = ed[1-k][i-1] + (a[i-1] == b[j-1] ? 0:1);
         ed[k][i] = min(min(o1,o2),o3);
      }
   }
   return ed[k][a.size()];
}
string RandString(int len) {
  default_random_engine gen((random_device())());
  uniform_int_distribution<int> dis('a', 'z');
  string ret;
  while (len--) {
    ret += dis(gen);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  string A, B;
  // Wiki example (http://en.wikipedia.org/wiki/Levenshtein_distance)
  A = "Saturday", B = "Sunday";
  assert(3 == LevenshteinDistance(A, B));
  A = "kitten", B = "sitting";
  assert(3 == LevenshteinDistance(A, B));

  if (argc == 3) {
    A = argv[1], B = argv[2];
  } else {
    uniform_int_distribution<int> dis(1, 100);
    A = RandString(dis(gen));
    B = RandString(dis(gen));
  }
  cout << A << endl << B << endl;
  cout << LevenshteinDistance(A, B) << endl;
  return 0;
}
