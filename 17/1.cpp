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

int N(const VI &w, int t, int i)
{
   if(t == 0){
      return 1;
   }
   if(t < 0){
      return 0;
   }
   if(i >= w.size()){
      return 0;
   }
   int sum = 0;
   while(t >= 0){
      sum += N(w, t, i+1);
      t -= w[i];
   }
   return sum;
}

int CountCombinations(int t, const VI &w)
{
   return N(w, t, 0);
}

void SimpleTest() {
  vector<int> score_ways = {2, 3, 7};
  assert(4 == CountCombinations(12, score_ways));
  assert(1 == CountCombinations(5, score_ways));
}

int main(int argc, char* argv[]) {
  SimpleTest();
  default_random_engine gen((random_device())());
  int k;
  vector<int> score_ways;
  if (argc == 1) {
    uniform_int_distribution<int> k_dis(0, 999);
    k = k_dis(gen);
    uniform_int_distribution<int> size_dis(1, 50);
    score_ways.resize(size_dis(gen));
    for (int i = 0; i < score_ways.size(); ++i) {
      uniform_int_distribution<int> score_dis(1, 1000);
      score_ways[i] = score_dis(gen);
    }
  } else if (argc == 2) {
    k = atoi(argv[1]);
    uniform_int_distribution<int> size_dis(1, 50);
    score_ways.resize(size_dis(gen));
    for (int i = 0; i < score_ways.size(); ++i) {
      uniform_int_distribution<int> score_dis(1, 1000);
      score_ways[i] = score_dis(gen);
    }
  } else {
    k = atoi(argv[1]);
    for (int i = 2; i < argc; ++i) {
      score_ways.emplace_back(atoi(argv[i]));
    }
  }
  cout << CountCombinations(k, score_ways) << endl;
  return 0;
}
