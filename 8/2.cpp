// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Linked_list_prototype.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

template <typename T>
void Print(shared_ptr<ListNode<T>> head) {
  if (head) {
    cout << "(" << head->data << ")" << endl;
    Print(head->next);
  }
}
shared_ptr<ListNode<int>> ReverseLinkedListMine(shared_ptr<ListNode<int>> l){
   shared_ptr<ListNode<int>> p1 = l;
   if(!l) return l;
   shared_ptr<ListNode<int>> p2 = p1->next;
   if(!p2) return l;
   shared_ptr<ListNode<int>> p3 = p2->next;
   p1->next = NULL;
   while(p2){
      p2->next = p1;
      p1 = p2;
      p2 = p3;
      if(p3) p3 = p3->next;
   }
   return p1;
}

int main(int argc, char* argv[]) {
  shared_ptr<ListNode<int>> L1 = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
  shared_ptr<ListNode<int>> L2 = make_shared<ListNode<int>>(ListNode<int>{2, nullptr});
  L1->next = L2;
  shared_ptr<ListNode<int>> L3 = make_shared<ListNode<int>>(ListNode<int>{3, nullptr});
  L2->next = L3;

  cout << "before reverse" << endl;
  Print(L1);
  shared_ptr<ListNode<int>> newhead = ReverseLinkedListMine(L1);
  cout << endl << "after reverse" << endl;
  assert(newhead->data == 3 && newhead->next->data == 2 && newhead->next->next->data == 1);
  Print(newhead);
  newhead = ReverseLinkedListMine(newhead);
  assert(newhead->data == 1 && newhead->next->data == 2 && newhead->next->next->data == 3);
  cout << endl << "after another reverse" << endl;
  Print(newhead);
  return 0;
}
