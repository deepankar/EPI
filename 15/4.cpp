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
#include "./BST_prototype.h"
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

int f(const unique_ptr<BSTNode<int>> &root, int k, VI &res)
{
   if(k == 0 || !root) return 0;
   int added = f(root->right, k, res);
   k -= added;
   if(k > 0){
      res.push_back(root->data);
      added++;
      k--;
   }
   if(k > 0){
      added += f(root->left, k, res);
   }
   return added;
}
VI FindKLargestInBST(const unique_ptr<BSTNode<int>> &root, int k)
{
   VI res;
   f(root, k, res);
   return res;
}

int main(int argc, char* argv[]) {
  //    3
  //  2   5
  // 1   4 6
  unique_ptr<BSTNode<int>> root = unique_ptr<BSTNode<int>>(new BSTNode<int>{3});
  root->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{2});
  root->left->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{1});
  root->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{5});
  root->right->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{4});
  root->right->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{6});
  default_random_engine gen((random_device())());
  int k;
  if (argc == 2) {
    k = atoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 6);
    k = dis(gen);
  }
  cout << "k = " << k << endl;
  vector<int> ans = FindKLargestInBST(root, k);
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i] << endl;
  }
  for (int i = 1; i < ans.size(); ++i) {
    assert(ans[i - 1] >= ans[i]);
  }
  return 0;
}
