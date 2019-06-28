#include <cstring>
#include "../src/softheap.hh"


void test_insert_tree()
{
  printf("\033[1;33m");
  printf("TEST 8: Simple insert_tree\n");
  printf("\033[0m");
  
  int a = 4;
  int b = 10;
  int c = 60;
  int d = 14;
  SoftHeap<int> *sh = new SoftHeap(&a);
  SoftHeap<int> *ch = new SoftHeap(&d);
  SoftHeap<int>::Tree *ti = new SoftHeap<int>::Tree(&b);
  SoftHeap<int>::Tree *to = new SoftHeap<int>::Tree(&c);
  ch->insert_tree(sh,to,ti);

   
  /*  if (sh->first->root->ckey != &a  || sh->first->root->ckey != &b || sh->first->root->ckey != &c)
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
      }  */
  delete sh;
  delete ch;
}
