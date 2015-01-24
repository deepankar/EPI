// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include "./Linked_list_prototype.h"
#include "./Merge_sorted_lists.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_shared;
using std::numeric_limits;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;

shared_ptr<ListNode<int>> MergeTwoSortedListsMine(shared_ptr<ListNode<int>> F, shared_ptr<ListNode<int>> L){
   shared_ptr<ListNode<int>> prev;
   shared_ptr<ListNode<int>> ret;
   shared_ptr<ListNode<int>> p1 = L;
   shared_ptr<ListNode<int>> p2 = F;
   if(!p1) return p2;
   if(!p2) return p1;

   if(p1->data < p2->data){
      ret = p1;
      prev=p1;
      p1 = p1->next;
   }else{
      ret = p2;
      prev = p2;
      p2 = p2->next;
   }
   while(p1 && p2){
      if(p1->data < p2->data){
         prev->next = p1;
         prev = p1;
         p1 = p1->next;
      }else{
         prev->next = p2;
         prev = p2;
         p2 = p2->next;
      }
   }
   if(p1) prev->next = p1;
   else prev->next = p2;
   return ret;

}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10000; ++times) {
    shared_ptr<ListNode<int>> F = nullptr, L = nullptr;
    int n, m;
    if (argc == 3) {
      n = stoi(argv[1]), m = stoi(argv[2]);
    } else if (argc == 2) {
      n = stoi(argv[1]), m = stoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(0, 99);
      n = dis(gen), m = dis(gen);
    }
    for (int i = n; i > 0; --i) {
      shared_ptr<ListNode<int>> temp =
          make_shared<ListNode<int>>(ListNode<int>{i, nullptr});
      temp->next = F;
      F = temp;
    }
    for (int j = m; j > 0; --j) {
      shared_ptr<ListNode<int>> temp =
          make_shared<ListNode<int>>(ListNode<int>{j, nullptr});
      temp->next = L;
      L = temp;
    }

    shared_ptr<ListNode<int>> sorted_head = MergeTwoSortedListsMine(F, L);
    int count = 0;
    int pre = numeric_limits<int>::min();
    while (sorted_head) {
      assert(pre <= sorted_head->data);
      pre = sorted_head->data;
      sorted_head = sorted_head->next;
      ++count;
    }
    // Make sure the merged list have the same number of nodes as F and L.
    assert(count == n + m);
  }
  return 0;
}
