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
#include <iterator>
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

int CalculateTrappingWater(const VI &h)
{
   if(h.size() <= 2) return 0;
   VI rev_max(h.size()); //max h after this index. 
   rev_max[h.size()-1] = 0;
   for(int i = h.size() - 2; i >= 0; i--){
      rev_max[i] = max(h[i+1], rev_max[i+1]);
   }
   int prev_max = 0;
   int w = 0;
   for(int i = 1; i < h.size()-1; i++){
      prev_max = max(prev_max, h[i-1]);
      int mx = min(prev_max, rev_max[i]);
      if(mx - h[i] > 0){
         w += mx - h[i];
      }
   }
   return w;
}
// Stack approach, O(n) time, O(n) space
int CheckAnswer(const vector<int> &A) {
  stack<pair<int, int>> s;
  int sum = 0;
  for (size_t i = 0; i < A.size(); ++i) {
    while (!s.empty() && s.top().second <= A[i]) {
      int bottom = s.top().second;
      s.pop();
      if (s.empty()) {
        break;
      }
      int top = min(s.top().second, A[i]);
      sum += (top - bottom) * (i - s.top().first - 1);
    }
    s.emplace(i, A[i]);
  }
  return sum;
}

void SmallTest() {
  vector<int> A = {1, 0, 3, 2, 5, 0, 1};
  assert(CalculateTrappingWater(A) == 3);
  A = {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1};
  cout << CalculateTrappingWater(A) << endl;
  assert(CalculateTrappingWater(A) == 18);
}

int main(int argc, char *argv[]) {
  SmallTest();
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc == 2) {
      n = stoi(argv[1]);
    } else {
      uniform_int_distribution<int> n_dis(1, 1000);
      n = n_dis(gen);
    }
    vector<int> A;
    uniform_int_distribution<int> A_dis(0, 10);
    generate_n(back_inserter(A), n, [&] { return A_dis(gen); } );
    copy(A.cbegin(), A.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << CheckAnswer(A) << " " << CalculateTrappingWater(A) << endl;
    assert(CheckAnswer(A) == CalculateTrappingWater(A));
  }
  return 0;
}
