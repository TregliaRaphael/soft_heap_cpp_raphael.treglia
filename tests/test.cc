#include <cassert>
#include "../src/softheap.hh"

class Test
{
    public:
        static void unit_test_first_ckey()
        {
            int a = 3, b = 6, c = 4;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);
            s->insert(&c);
            assert(*s->first->root->ckey == 4);
            delete s;
        }

        static void unit_test_extract_void()
        {
            int a = 2;
            SoftHeap<int> *s = new SoftHeap(&a);

            assert(*s->extract_min().value() == 2);
            assert(s->extract_min() == std::nullopt);
        }

        static void unit_test_next_ckey()
        {
            int a = 3, b = 6, c = 4;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);
            s->insert(&c);
            assert(*s->first->next->root->ckey == 3);
            delete s;
        }

        static void unit_test_child_ckeys()
        {
            int a = 3, b = 6, c = 4, d = 12, e = 1, f = 50;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);
            s->insert(&c);
            s->insert(&d);
            s->insert(&e);
            s->insert(&f);

            assert(*s->first->root->ckey == 1);
            assert(*s->first->root->right->ckey == 50);

            assert(*s->first->next->root->ckey == 3);
            assert(*s->first->next->root->right->ckey == 4);
            assert(*s->first->next->root->left->ckey == 6);
            assert(*s->first->next->root->right->right->ckey == 12);
            delete s;
        }

        static void unit_test_suf_min()
        {
            int a = -9, b = -10, c = 2;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);
            s->insert(&c);

            assert(*s->extract_min().value() == -10);
            delete s;
        }

        static void unit_test_delete()
        {
            int a = 2, b = 9, c = 1;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);
            s->insert(&c);
            assert(*s->extract_min().value() == 1);
            assert(*s->extract_min().value() == 2);
            assert(*s->extract_min().value() == 9);
            delete s;
        }

        static void unit_test_meld()
        {
            int a = 5, b = 2, c = 3, d = 8, e = 1;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);

            SoftHeap<int> *p = new SoftHeap(&c);
            p->insert(&d);
            p->insert(&e);

            s->meld(p);

            assert(*s->extract_min().value() == 1);
            delete p;
            delete s;
        }

        static void unit_test_hard_meld()
        {
            int a = 6, b = 3, c = 12, d = 9, e = 19, f = 3, g = 8, h = 1,
                i = 19, j = -1;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);
            s->insert(&c);
            s->insert(&d);
            s->insert(&e);

            SoftHeap<int> *p = new SoftHeap(&f);
            p->insert(&g);
            p->insert(&h);
            p->insert(&i);
            p->insert(&j);

            s->meld(p);

            assert(*s->extract_min().value()== -1);
            assert(*s->extract_min().value() == 1);
            assert(*s->extract_min().value() == 3);
            assert(*s->extract_min().value() == 3);
            assert(*s->extract_min().value() == 6);
            assert(*s->extract_min().value() == 8);
            assert(*s->extract_min().value() == 9);
            assert(*s->extract_min().value() == 12);
            assert(*s->extract_min().value() == 19);
            assert(*s->extract_min().value() == 19);
            assert(s->extract_min() == std::nullopt);

            delete s;
            delete p;
        }

        static void unit_test_insert_random_1()
        {
            int a = 2, b = 9, c = 1, d = 6;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);
            s->insert(&c);
            s->insert(&d);
            assert(*s->extract_min().value() == 1);
            assert(*s->extract_min().value() == 2);
            assert(*s->extract_min().value() == 6);
            assert(*s->extract_min().value() == 9);
            delete s;

        }

        static void unit_test_insert_random_2()
        {
            int a = 2, b = 9, c = 1, d = 6;
            SoftHeap<int> *s = new SoftHeap(&a);
            s->insert(&b);
            s->insert(&c);
            s->insert(&d);

            assert(*s->first->root->ckey == 1);
            assert(*s->first->root->right->ckey == 2 );
            assert(*s->first->root->left->ckey == 6);
            assert(*s->first->root->right->right->ckey == 9);

            delete s;
        }
        
        static void unit_test_insert_random_3()
        {
            int a = 2, b = 9, c = 1, d = 6;
            SoftHeap<int> *s = new SoftHeap(&b);
            s->insert(&d);
            s->insert(&a);
            s->insert(&c);

            assert(*s->first->root->ckey == 1);
            assert(*s->first->root->left->ckey == 2 );
            assert(*s->first->root->right->ckey == 6);
            assert(*s->first->root->right->right->ckey == 9);

            delete s;
        }




};

int main(void)
{
    Test::unit_test_first_ckey();
    Test::unit_test_extract_void();
    Test::unit_test_next_ckey();
    Test::unit_test_child_ckeys();
    Test::unit_test_suf_min();
    Test::unit_test_delete();
    Test::unit_test_meld();
    Test::unit_test_hard_meld();
    Test::unit_test_insert_random_1();
    Test::unit_test_insert_random_2();
    Test::unit_test_insert_random_3();
}
