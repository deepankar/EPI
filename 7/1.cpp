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

string IntToString(int n)
{
   deque<char> q;
   bool neg = false;
   if(n < 0){
      neg = true;
      n = -n;
   }
   while(n){
      char c = '0' + n%10;
      q.push_front(c);
      n = n /10;
   }
   if(neg){
      q.push_front('-');
   }
   string str(q.size(), '0');
   FOR0(i, q.size()){
      str[i] = q[i];
   }
   return str;
}

int StringToInt(const string &s)
{
   if(s.empty()) return 0;
   int r = 0;
   bool neg = s[0] == '-';
   for(int i = neg; i < s.size(); i++){
      r = 10*r + (s[i]-'0');
   }
   if(neg) r = -r;
   return r;
}

string RandIntString(int len) {
  default_random_engine gen((random_device())());
  string ret;
  if (len == 0) {
    return {"0"};
  }
  uniform_int_distribution<int> pos_or_neg(0, 1);
  if (pos_or_neg(gen)) {
    ret.push_back('-');
  }
  uniform_int_distribution<int> num_dis('1', '9');
  ret.push_back(num_dis(gen));
  while (--len) {
    uniform_int_distribution<int> dis('0', '9');
    ret.push_back(dis(gen));
  }
  return ret;
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  if (argc == 2) {
    cout << StringToInt(argv[1]) << endl;
  } else {
    for (int times = 0; times < 10000; ++times) {
      uniform_int_distribution<int> dis(numeric_limits<int>::min(),
                                        numeric_limits<int>::max());
      int x = dis(gen);
      string str = IntToString(x);
      cout << x << " " << str << endl;
      assert(x == stoi(str));
      uniform_int_distribution<int> len_dis(0, 9);
      str = RandIntString(len_dis(gen));
      x = StringToInt(str);
      cout << str << " " << x << endl;
      assert(x == stoi(str));
    }
  }
  return 0;
}
