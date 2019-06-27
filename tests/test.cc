#include <cassert>
#include "../src/softheap.hh"

class Test
{
    public:
        static void unit_test_first_ckey()
        {
            SoftHeap<int> *s = new SoftHeap(3);
            s->insert(6);
            s->insert(4);
            assert(s->first->root->ckey == 4);
        }

        static void unit_test_next_ckey()
        {
            SoftHeap<int> *s = new SoftHeap(3);
            s->insert(6);
            s->insert(4);
            assert(s->first->next->root->ckey == 3);
        }

        static void unit_test_child_ckeys()
        {
            SoftHeap<int> *s = new SoftHeap(3);
            s->insert(6);
            s->insert(4);
            s->insert(12);
            s->insert(1);
            s->insert(50);

            assert(s->first->root->ckey == 1);
            assert(s->first->root->right->ckey == 50);

            assert(s->first->next->root->ckey == 3);
            assert(s->first->next->root->right->ckey == 4);
            assert(s->first->next->root->left->ckey == 6);
            assert(s->first->next->root->right->right->ckey == 12);
        }

        static void unit_test_suf_min()
        {
            SoftHeap<int> *s = new SoftHeap(-9);
            s->insert(-10);
            s->insert(2);

            assert(s->extract_min() == -10);
        }

        static void unit_test_delete()
        {
            SoftHeap<int> *s = new SoftHeap(2);
            s->insert(9);
            s->insert(1);
            assert(s->extract_min() == 1);
            assert(s->extract_min() == 2);
            assert(s->extract_min() == 9);
            assert(s->extract_min() == std::nullopt);
        }
};

int main(void)
{
    Test::unit_test_first_ckey();
    Test::unit_test_next_ckey();
    Test::unit_test_child_ckeys();
    Test::unit_test_suf_min();
    Test::unit_test_delete();
}
