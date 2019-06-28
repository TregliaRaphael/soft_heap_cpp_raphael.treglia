#include "test.hh"

void launch_test_constructor()
{
  printf("\033[1;36m");
  printf("TESTS ON THE CONSTRUCTORS\n");
  printf("\033[0m");
  test_constructor_listcell();
  test_constructor_node();
  test_constructor_tree();
  test_constructor_softheap();
  test_constructor_listcell_with_several_cell();
  test_constructor_node_with_children();
  test_constructor_tree_with_children();
}

void launch_test_insert()
{
  printf("\033[1;36m");
  printf("TESTS OF THE INSERT FUNCTIONS\n");
  printf("\033[0m");
  test_insert_tree();
}


int main (void)
{
  launch_test_constructor();
  //launch_test_insert(); // test not accurate
  return 0;
}
