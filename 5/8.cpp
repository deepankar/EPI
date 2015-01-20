//only +ve numbers supported!
#include <limits.h>
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

class Solver
{
   int chartoi(char c)
   {
      if(isdigit(c)){
         return c - '0';
      }
      assert(c <='F' && c >='A');
      return c - 'A' + 10;
   }
   luint toi(const string &n, int ib)
   {
      luint x = 0;
      luint m = 1;
      for(int i = n.size() - 1; i >= 0; i--){
         x += chartoi(n[i])*m;
         m *= ib;
      }
      return x;
   }

   char numtochar(uint x)
   {
      assert(x <= 15);
      if(x < 10){
         return '0' + x;
      }else{
         return 'A' + (x-10);
      }
   }

   string tos(luint n, int ob){
      string s;
      while(n){
         s = s + numtochar(n % ob);
         n = n/ob;
      }
      reverse(s.begin(), s.end());
      return s;
   }

   public:
   string solve(const string &n, int ib, int ob)
   {
      string res;
      luint i = toi(n,ib);
//      cout << "n=" << i << endl;
      res = tos(i, ob);
      return res;
   }
};
string RandIntString(int len) {
  default_random_engine gen((random_device())());
  string ret;
  if (len == 0) {
    return {"0"};
  }
  uniform_int_distribution<int> pos_or_neg(0, 1);
  if (pos_or_neg(gen)) {
//    ret.push_back('-');
  }
  uniform_int_distribution<int> num_dis('1', '9');
  ret.push_back(num_dis(gen));
  while (--len) {
    uniform_int_distribution<int> dis('0', '9');
    ret.push_back(dis(gen));
  }
  return ret;
}

int main(int argc, char **argv)
{
   Solver slv;
  if (argc == 4) {
    string input(argv[1]);
    cout << slv.solve(input, atoi(argv[2]), atoi(argv[3])) << endl;
    assert(input ==
           slv.solve(slv.solve(input, atoi(argv[2]), atoi(argv[3])),
                       atoi(argv[3]), atoi(argv[2])));
  } else {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 100000; ++times) {
      uniform_int_distribution<int> len_dis(1, 9);
      string input = RandIntString(len_dis(gen));
      uniform_int_distribution<int> base_dis(2, 16);
      int base = base_dis(gen);
      cout << "input is " << input << ", base1 = 10, base2 = " << base
           << ", result = " << slv.solve(input, 10, base) << endl;
      assert(input == slv.solve(slv.solve(input, 10, base), base, 10));
    }
  }
/*   int ib, ob;
   string n;
   n = argv[1];
   ib = atoi(argv[2]);
   ob = atoi(argv[3]);
   cout << slv.solve(n, ib, ob) << endl;
   */
   return 0;
}
