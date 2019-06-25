#include "softheap.hh"
#include <iostream>


template<typename E>
void SoftHeap<E>::insert(E e)
{
    meld(this, new SoftHeap(e));
}


template<typename E>
void swap(E* a, E* b)
{
    E cpy = *a;
    *a = *b;
    *b = cpy; 
}


template<typename E>
void SoftHeap<E>::meld(SoftHeap* Q)
{
    if (this->rank > Q.rank)
    {
        swap(this, Q);
    }

    merge_into(this,Q);
    repeated_combine(Q,this->rank);
    return Q;
}

template<typename E>
E pick_elem(SoftHeap<E>::Node x)
{
    SoftHeap<E>::ListCell* cpy = x->list;
    SoftHeap<E>::ListCell* last = x->list;

    while (cpy != nullptr)
    {
        last = cpy;
        cpy = cpy->next;
    }

    E cpy_elem = last->elem;
    delete[] last;
    return cpy_elem;
}

template<typename E>
E SoftHeap<E>::extract_min()
{
    if (this->first == nullptr)
        return nullptr;

    auto Tree = this->first->sufmin;
    Node* x = Tree->root;
    E e = pick_elem(x);

    if (x->list.size() <= x->size/2)
    {
        if (leaf(x) == nullptr)
        {
            sift(x);
            update_suffix_min(Tree);
        }
        else if (x->list == nullptr)
            remove_tree(this, Tree);
    }
    return e;
}
