#include "softheap.hh"
#include <iostream>

template <typename E>

SoftHeap<E>::Node* SoftHeap<E>::Node::make_node( E element)
{
  Node *nov = new Node();
  nov->list.elem = e;
  nov->list.elem->next = null;
  nov->rank = 0;
  nov->size = 1;
  nov->ckey = e;
  nov->left = null;
  nov->right = null;
  return nov; 
}

int main(){

}
