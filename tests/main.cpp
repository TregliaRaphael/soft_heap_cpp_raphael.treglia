#include "test.hh"

int main (void)
{
  test_constructor_listcell();
  test_constructor_node();
  test_constructor_tree();
  test_constructor_softheap();
  test_constructor_listcell_with_several_cell();
  test_constructor_node_with_children();
  
  return 0;
}
