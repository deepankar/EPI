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

void moveRight(char *s)
{
   char *l = s;
   while(*l) l++;
   //l is at \0 now
   while(l >= s){
      l[1] = l[0];
      l--;
   }
}

void moveLeft(char *s)
{
   while(*s){
      *(s-1) = *s;
      s++;
   }
   *(s-1) = 0;
}

string ReplaceAndRemove(const string &str)
{
   char *ss = new char[str.size()*2+1];
   char *s = ss;
   strcpy(s, str.c_str());
   while(*s){
      if(*s == 'a'){
         moveRight(s+1);
         *s = 'd';
         s[1] = 'd';
         s+= 2;
      }else if(*s == 'b'){
         moveLeft(s+1);
      }else{
         s++;
      }
   }
   string ret(ss);
   delete [] ss;
   return ret;
}
string RandString(int len) {
  default_random_engine gen((random_device())());
  string ret;
  while (len--) {
    uniform_int_distribution<char> dis('a', 'd');
    ret += dis(gen);
  }
  return ret;
}

void CheckAns(const string &s, const string &ans) {
  string temp;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'a') {
      temp += 'd', temp += 'd';
    } else if (s[i] != 'b') {
      temp += s[i];
    }
  }
  assert(ans.compare(temp) == 0);
}
int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    string s;
    if (argc == 2) {
      s = argv[1];
    } else {
      uniform_int_distribution<int> dis(1, 1000);
      s = RandString(dis(gen));
    }
    cout << s << endl << endl;
    string ans = ReplaceAndRemove(s);
    cout << ans << endl;
    CheckAns(s, ans);
  }
  return 0;
}
