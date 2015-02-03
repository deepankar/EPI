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

typedef pair<const BSTNode<int>*,bool> PT;
typedef vector<PT> Path;

const BSTNode<int> *look(const unique_ptr<BSTNode<int>> &root, int k, Path &path)
{
   const BSTNode<int> *n = root.get();
   while(n){
      if(k == n->data){
         path.push_back(PT(n, false));
         return n;
      }
      if(k < n->data){
         path.push_back(PT(n, true)); //true = left
         n = n->left.get();
      }else{
         path.push_back(PT(n, false)); //false = right
         n = n->right.get();
      }
   }
   return NULL;
}

const BSTNode<int> *smallest(const unique_ptr<BSTNode<int>> &root)
{
   const BSTNode<int> *n = root.get();
   assert(n);
   while(n->left) n = n->left.get();
   return n;
}

const BSTNode<int>* FindFirstLargerKWithKExist(const unique_ptr<BSTNode<int>> &root, int k)
{
   Path path;
   const BSTNode<int> *res = look(root, k, path);
   if(!res) return NULL;
   if(res->right){
      return smallest(res->right);
   }
   for(int i = path.size()-1; i >= 0; i--){
      if(path[i].second) //left
         return path[i].first;
   }
   return NULL;
}
int main(int argc, char* argv[]) {
  //    3
  //  2   5
  // 1   4 7
  auto root = unique_ptr<BSTNode<int>>(new BSTNode<int>{3});
  root->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{2});
  root->left->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{1});
  root->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{5});
  root->right->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{4});
  root->right->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{7});
  assert(FindFirstLargerKWithKExist(root, 1) == root->left.get());
  assert(FindFirstLargerKWithKExist(root, 5) == root->right->right.get());
  assert(!FindFirstLargerKWithKExist(root, 6));
  assert(!FindFirstLargerKWithKExist(root, 7));
  return 0;
}
