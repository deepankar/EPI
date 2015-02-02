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
#include "./Binary_tree_prototype.h"
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

bool _isBst(const unique_ptr<BinaryTreeNode<int>> &root, int &mn, int &mx)
{
   if(!root->left && !root->right){
      mx = mn = root->data;
      return true;
   }
   int mn1, mx1;
   if(root->left){
      bool b1 = _isBst(root->left, mn1, mx1);
      if(!b1 || root->data < mx1){
         return false;
      }
   }
   int mn2, mx2;
   if(root->right){
      bool b2 = _isBst(root->right, mn2, mx2);
      if(!b2 || root->data > mn2){
         return false;
      }
   }
   mn = root->left? mn1 : root->data;
   mx = root->right? mx2: root->data;
   return true;
}

bool IsBST(const unique_ptr<BinaryTreeNode<int>> &root)
{
   if(!root) return true;
   int mn, mx;
   return _isBst(root, mn, mx);
}

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  auto root = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{3});
  root->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{2});
  root->left->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{1});
  root->right = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{5});
  root->right->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{4});
  root->right->right = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{6});
  // should output true.
  assert(IsBST(root) == true);
  cout << boolalpha << IsBST(root) << endl;
  //      10
  //    2   5
  //  1    4 6
  root->data = 10;
  // should output false.
  assert(!IsBST(root));
  cout << boolalpha << IsBST(root) << endl;
  // should output true.
  assert(IsBST(nullptr) == true);
  cout << boolalpha << IsBST(nullptr) << endl;
  return 0;
}
