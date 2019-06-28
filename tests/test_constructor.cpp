#include <cstring>
#include "../src/softheap.hh"



void test_constructor_listcell()
{
  printf("\033[1;33m");
  printf("TEST 1: Simple ListCell constructor\n");
  printf("\033[0m");
  int a = 968 ;
  SoftHeap<int>::ListCell *fi = new SoftHeap<int>::ListCell(&a);

  if (fi->elem  != &a)
    {
      printf("\033[1;31m");
      printf("FAIL\n");
      printf("\033[0m");
    }
  else
    {
      printf("\033[1;32m");
      printf("SUCESS\n");
      printf("\033[0m");
    }
  delete fi;
    
}


void test_constructor_node()
{
  printf("\033[1;33m");
  printf("TEST 2: Simple Node constructor\n");
  printf("\033[0m");

  int a = 10; 
  SoftHeap<int>::Node *lo = new SoftHeap<int>::Node(&a);
  if (lo->ckey  != &a || lo->rank != 0 || lo->size !=1 || lo->left!=nullptr|| lo->right != nullptr)
    {
      printf("\033[1;31m");
      printf("FAIL\n");
      printf("\033[0m");
    }
  else
    {
      printf("\033[1;32m");
      printf("SUCESS\n");
      printf("\033[0m");
    }

  delete lo;
}


void test_constructor_tree()
{
  printf("\033[1;33m");
  printf("TEST 3: Simple Tree constructor\n");
  printf("\033[0m");

  int a = 50;
  SoftHeap<int>::Tree *tr = new SoftHeap<int>::Tree(&a);
  if (tr->root->ckey  != &a || tr->root->rank != 0 || tr->root->size !=1 || tr->root->left!=nullptr|| tr->root->right != nullptr)
    {
      printf("\033[1;31m");
      printf("FAIL\n");
      printf("\033[0m");
    }
  else if ( tr->prev != nullptr || tr->next != nullptr || tr->rank != 0)  
    {
      printf("\033[1;31m");
      printf("FAIL\n");
      printf("\033[0m");
    }
  else
    {
      printf("\033[1;32m");
      printf("SUCESS\n");
      printf("\033[0m");
    }
  delete tr;
}

void test_constructor_softheap()
{
  printf("\033[1;33m");
  printf("TEST 4: Simple SoftHeap constructor\n");
  printf("\033[0m");

  int a = 4;
  SoftHeap<int> *sh = new SoftHeap(&a);
  if (sh->first->root->ckey  != &a || sh->first->root->rank != 0 || sh->first->root->size !=1 || sh->first->root->left!=nullptr|| sh->first->root->right != nullptr)
    {
      printf("\033[1;31m");
      printf("FAIL\n");
      printf("\033[0m");
    }
  else if ( sh->first->prev != nullptr || sh->first->next != nullptr || sh->first->rank != 0)
    {
      printf("\033[1;31m");
      printf("FAIL\n");
      printf("\033[0m");
    }
  else
    {
      printf("\033[1;32m");
      printf("SUCESS\n");
      printf("\033[0m");
    }
  delete sh;  
}

void test_constructor_listcell_with_several_cell()
{
  printf("\033[1;33m");
  printf("TEST 5: Simple ListCell constructor with several cell\n");
  printf("\033[0m");
  int a = 968 ;
  int b = 4;
  SoftHeap<int>::ListCell *fi = new SoftHeap<int>::ListCell(&a);
  SoftHeap<int>::ListCell *fo = new SoftHeap<int>::ListCell(&b);

  fi->next = fo;
  
  if (fi->elem  != &a || fi->next->elem != &b)
    {
      printf("\033[1;31m");
      printf("FAIL\n");
      printf("\033[0m");
    }
  else
    {
      printf("\033[1;32m");
      printf("SUCESS\n");
      printf("\033[0m");
    }
  delete fi;
}


void test_constructor_node_with_children()
{
  printf("\033[1;33m");
  printf("TEST 6: Node constructor and add children to the node\n");
  printf("\033[0m");

  int a = 10;
  int b = 50;
  int c = 80;
  SoftHeap<int>::Node *lo = new SoftHeap<int>::Node(&a);
  SoftHeap<int>::Node *left_child = new SoftHeap<int>::Node(&b);
  SoftHeap<int>::Node *right_child = new SoftHeap<int>::Node(&c);
  
  lo->left = left_child;
  lo->right = right_child;
  if (lo->ckey  != &a || lo->rank != 0 || lo->size !=1 )
    {
      printf("\033[1;31m");
      printf("FAIL\n");
      printf("\033[0m");
    }
  else
    {
      printf("\033[1;32m");
      printf("SUCESS\n");
      printf("\033[0m");
    }

  delete lo;
}
