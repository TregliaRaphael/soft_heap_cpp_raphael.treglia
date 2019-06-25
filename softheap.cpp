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

E pick_elem(

template<typename E>
E SoftHeap<E>::extract_min()
{
    if (this->first == nullptr)
        return nullptr;

    auto Tree = this->first->sufmin;
    auto x = Tree->root;
    auto e = 
}
