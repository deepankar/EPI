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
const int kNumTelDigits = 10;
const array<string, kNumTelDigits> M = {{"0", "1", "ABC", "DEF", "GHI",
                                         "JKL", "MNO", "PQRS", "TUV",
                                         "WXYZ"}};

string findNxt(char x)
{
   return M[x-'0'];
}

void backtrack(const string &str, int pos, char *sol, VS &sols)
{
   if(pos == str.size()){
      sol[pos] = 0;
      sols.push_back(sol);
      return;
   }
   string nxt = findNxt(str[pos]);
   FOR0(i, nxt.size()){
      sol[pos] = nxt[i];
      backtrack(str, pos+1, sol, sols);
   }
}

vector<string> PhoneMnemonic(const string& phone_number) {
   VS sols;
   char *sol = new char[phone_number.size() + 1];
   backtrack(phone_number, 0, sol, sols);
   delete [] sol;
   return sols;
}
string RandString(int len) {
  default_random_engine gen((random_device())());
  string ret;
  while (len--) {
    uniform_int_distribution<char> dis('0', '9');
    ret += dis(gen);
  }
  return ret;
}
int main(int argc, char *argv[]) {
  string num;
  if (argc == 2) {
    num = argv[1];
  } else {
    num = RandString(10);
  }
  auto result = PhoneMnemonic(num);
  cout << "number = " << num << endl;
  for (const auto& str : result) {
    cout << str << endl;
  }
  return 0;
}
