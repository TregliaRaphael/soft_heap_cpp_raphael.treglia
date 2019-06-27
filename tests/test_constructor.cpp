#include <cstring>
#include "softheap.hh"



void test_constructor_listcell()
{
  printf("This the ListCell\n");
  SoftHeap<int>::ListCell *fi = new SoftHeap<int>::ListCell(968);
  printf("%d\n", fi->elem);
  printf("%p\n", (void *)fi->next);
}



/*int  (void)
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
	SoftHeap<int>::Tree *tr = new SoftHeap<int>::Tree(50);

	printf("%p\n", (void *)tr->root);
	printf("%p\n", (void *)tr->prev);
	printf("%p\n", (void *)tr->next);
	printf("%p\n", (void *)tr->sufmin);
	printf("%d\n", tr->rank);
	printf("\n");


	printf("This the SofyHeap\n");
	SoftHeap<int> *sh = new SoftHeap(4);
	sh = sh;
	printf("%f\n", sh->epsilon);
	printf("%d\n", sh->rank);
	printf("%d\n", sh->max_node_rank);
	printf("%p\n", (void *)sh->first->root);
	printf("%p\n", (void *)sh->first->prev);
	printf("%p\n", (void *)sh->first->next);
	printf("%p\n", (void *)sh->first->sufmin);
	printf("%d\n", sh->first->rank);
	printf("\n");

	delete(fi);
	delete(lo);
	delete (tr);
	delete(sh);
	return 0;
}
*/
