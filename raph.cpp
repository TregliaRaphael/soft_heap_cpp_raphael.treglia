#include "softheap.hh"
#include <iostream>


template<typename E>
int SoftHeap<E>::ListCell::size() {
    SoftHeap<E>::ListCell list = this;
    if (list == nullptr)
        return 0;
    int cpt = 1;
    while(list->next){
        list = list->next;
        cpt++;
    }
    return cpt;
}

template<typename E>
void SoftHeap<E>::sift(SoftHeap::Node *x) {
    while(x->list->size() < x->size && !leaf(x)){
        if (x->left == nullptr || (x->right != nullptr && x->left->ckey > x->right->ckey))
            swap(x->left, x->right);

        concatenate(x->list, x->left->list);
        x->ckey = x->left->ckey;
        delete x->left->list;

        if (leaf(x->left))
            delete x->left;
        else
            sift(x->left);
    }
}

template<typename E>
typename SoftHeap<E>::Node* SoftHeap<E>::combine(SoftHeap<E>::Node *x, SoftHeap<E>::Node *y) {
    SoftHeap<E>::Node z = new SoftHeap<E>::Node();
}

template<typename E>
bool SoftHeap<E>::leaf(Node *x) {
    return x->left == nullptr && x->right == nullptr;

}