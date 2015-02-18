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
#include <pthread.h>
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

int last = 0;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* start(void *arg)
{
   bool odd = arg != NULL;
   while(true){
      int ret = pthread_mutex_lock(&mtx);
      assert(ret == 0);
      while(!(odd ^ (last&1))){
         pthread_cond_wait(&cond, &mtx);
      }
      last++;
      if(last > 100)
      {
         ret = pthread_mutex_unlock(&mtx);
         assert(ret == 0);
         ret = pthread_cond_signal(&cond);
         assert(ret == 0);
         return NULL;
      }
      cerr << (odd? "- ":"+ ")  << last << endl;
      ret = pthread_mutex_unlock(&mtx);
      assert(ret == 0);
      ret = pthread_cond_signal(&cond);
      assert(ret == 0);
   }
   return NULL;
}

int main()
{
   pthread_t t1, t2;
   bool x;
   int ret = pthread_create(&t1, NULL, start, &x);
   assert(ret==0);
   ret = pthread_create(&t2, NULL, start, NULL);
   assert(ret==0);
   //pthread_cond_signal(&cond);
   pthread_join(t1, NULL);
   pthread_join(t2, NULL);
}
