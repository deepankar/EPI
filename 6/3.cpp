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
#include "execute-shell.h"

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

void mult(const char *n1, char m, char *resultEnd)
{
   int carry = 0;
   int d2 = m-'0';
   const char *i=n1;
   char *r = resultEnd;
   while(*(i+1)) i++;
   while(i >= n1){
      int d1 = *i-'0';
      int res = d1*d2 + carry;
      carry = res/10;
      res = res % 10;
      *r = '0' + res;
      r--;
      i--;
   }
   *r = '0'+carry;
}

void add(char *n1, const char*n2){
   assert(strlen(n1) == strlen(n2));
   char *i1 = n1;
   const char *i2 = n2;
   while(*(i1+1)) i1++;
   while(*(i2+1)) i2++;
   int carry = 0;
   while(i1 >= n1){
      int sum = carry + (*i1-'0') + (*i2-'0');
      *i1 = (sum%10) + '0';
      carry = sum/10;
      i1--;
      i2--;
   }
}

string Multiply(const string &_n1, const string &_n2)
{
   string n1(_n1);
   string n2(_n2);
   if(n1.empty()) return n2;
   if(n2.empty()) return n1;
   bool neg1 = n1[0]=='-';
   bool neg2 = n2[0]=='-';
   if(neg1){
      n1.erase(0,1);
   }
   if(neg2){
      n2.erase(0,1);
   }
   int rsize = 1 + 1 + n1.size() + n2.size(); //excluding '-'
   char *res = new char[rsize];
   char *tmp = new char[rsize];
   memset(res, '0', rsize-1);
   res[rsize-1]=0;
   tmp[rsize-1]=0;
   char *tmpEnd = tmp + rsize-1-1;
   int shift = 0;
   for(int i = n2.size()-1; i >= 0; i--){
      memset(tmp, '0', rsize-1);
      mult(n1.c_str(), n2[i], tmpEnd - shift);
      add(res, tmp);
      shift++;
   }
   char *i = res;
   while(*(i+1) && *i=='0') i++;
   string result(i);
   if((neg1 ^ neg2) && *i != '0')
         result.insert(0,1,'-');
//   cout << n1 << " * " << n2 << " = " << result << endl;
   return result;
}

string RandString(int len) {
  string ret;
  if (!len) {
    ret += '0';
  } else {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> positive_or_negative(0, 1);
    if (positive_or_negative(gen)) {
      ret += '-';
    }
    uniform_int_distribution<int> dis(1, 9);
    ret += dis(gen) + '0';
    --len;
    while (len--) {
      uniform_int_distribution<int> dis(0, 9);
      ret += dis(gen) + '0';
    }
  }
  return ret;
}

void SimpleTest() {
  assert(Multiply("0", "1000") == "0");
  cout << Multiply("131412", "-1313332") << endl;
  assert(Multiply("131412", "-1313332") == "-172587584784");
}

int main(int argc, char *argv[]) {
  SimpleTest();
  for (int times = 0; times < 1000; ++times) {
    string s1, s2;
    if (argc == 3) {
      s1 = argv[1], s2 = argv[2];
    } else {
      default_random_engine gen((random_device())());
      uniform_int_distribution<int> dis(0, 19);
      s1 = RandString(dis(gen)), s2 = RandString(dis(gen));
    }
    string res = Multiply(s1, s2);
    cout << s1 << " * " << s2 << " = " << res << endl;
    string command = "bash -c 'bc <<<" + s1 + "*" + s2 +"'";
    string result = execute_shell(command);
    cout << "answer = " << result;
    assert(res.compare(result.substr(0, result.size() - 1)) == 0);
  }
  return 0;
}
