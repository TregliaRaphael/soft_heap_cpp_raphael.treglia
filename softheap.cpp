#include "softheap.hh"
#include <iostream>


template<typename E>
void SoftHeap<E>::insert(E e)
{
    return meld(this, new SoftHeap(e));
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
    if (this.rank > Q.rank)
    {
        swap(this, Q);
    }

    merge_into(this,Q);
    repeated_combine(Q,this.rank);
    return Q;
}

