#include <cstring>
#include "softheap.hh"

int main (void)
{
  printf("This the ListCell\n");
  SoftHeap<int>::ListCell *fi = new SoftHeap<int>::ListCell(968);
  printf("%d\n", fi->elem);
  printf("%p\n", (void *)fi->next);

  printf("\n");

  printf("This the Node\n");
  SoftHeap<int>::Node *lo = new SoftHeap<int>::Node(10);
  printf("%d\n", lo->ckey);
  printf("%d\n", lo->rank);
  printf("%d\n", lo->size);
  printf("%p\n", (void *)lo->left);
  printf("%p\n", (void*)lo->right);
  printf("%p\n", (void *)lo->list);

  printf("\n");

  printf("This the Tree\n");
  SoftHeap<int>::Tree tr = SoftHeap<int>::Tree(50);
  
  printf("%p\n", (void *)tr.root);
  printf("%p\n", (void *)tr.prev);
  printf("%p\n", (void *)tr.next);
  printf("%p\n", (void *)tr.sufmin);
  printf("%d\n", tr.rank);
  printf("\n");
    

 delete(fi);
 delete(lo);
 return 0;
}
