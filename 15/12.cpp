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
typedef vector<PI> VPI;
typedef long long int lint;
typedef unsigned long long int luint;
struct BinaryTree {
  int data;
  BinaryTree* left, *right;
  BinaryTree(int val = 0, BinaryTree* l = nullptr, BinaryTree* r = nullptr)
      : data(val), left(l), right(r) {}
};

enum Direction{Left, Right, None};
typedef pair<BinaryTree*, Direction> Move;
typedef vector<Move> Stack;

BinaryTree* findNxt(Stack &stk)
{
   BinaryTree *n  = stk.back().first;
   if(n->right){
      BinaryTree *x = n->right;
      stk.push_back(Move(x, Right));
      while(x->left){
         x = x->left;
         stk.push_back(Move(x, Left));
      }
      return x;
   }
   while(!stk.empty()){
      if(stk.back().second == Right){
         stk.pop_back();
      }else{
         stk.pop_back();
         break;
      }
   }
   if(stk.empty()){
      return NULL;
   }
   return stk.back().first;
}

BinaryTree* convert_tree_to_doubly_list(BinaryTree* n)
{
   Stack stk;
   stk.push_back(Move(n, None));
   while(n->left){
      n = n->left;
      stk.push_back(Move(n, Left));
   }
   BinaryTree *first = n;
   BinaryTree *nxt;
   while(nxt = findNxt(stk)){
      n->right = nxt;
      nxt->left = n;
      n = nxt;
   }
   n->right = first;
   first->left = n;
   return first;
}

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  BinaryTree* root = new BinaryTree(3);
  root->left = new BinaryTree(2);
  root->left->left = new BinaryTree(1);
  root->right = new BinaryTree(5);
  root->right->left = new BinaryTree(4);
  root->right->right = new BinaryTree(6);
  // should output 1, 2, 3, 4, 5, 6
  BinaryTree* head = convert_tree_to_doubly_list(root);
  BinaryTree* temp = head;
  do {
    cout << temp->data << endl;
    temp = temp->right;
  } while (temp != head);
  return 0;
}
