#include <cstring>
#include "../src/softheap.hh"



void test_constructor_listcell()
{
  printf("\033[1;33m");
  printf("TEST 1: Simple ListCell constructor\n");
  printf("\033[0m");
  SoftHeap<int>::ListCell *fi = new SoftHeap<int>::ListCell(968);

  if (fi->elem  != 968)
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

  SoftHeap<int>::Node *lo = new SoftHeap<int>::Node(10);
  if (lo->ckey  != 10 || lo->rank != 0 || lo->size !=1 || lo->left!=nullptr|| lo->right != nullptr)
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

  SoftHeap<int>::Tree *tr = new SoftHeap<int>::Tree(50);

  if (tr->root->ckey  != 50 || tr->root->rank != 0 || tr->root->size !=1 || tr->root->left!=nullptr|| tr->root->right != nullptr)
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

  SoftHeap<int> *sh = new SoftHeap(4);
  if (sh->first->root->ckey  != 4 || sh->first->root->rank != 0 || sh->first->root->size !=1 || sh->first->root->left!=nullptr|| sh->first->root->right != nullptr)
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


