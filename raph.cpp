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
void SoftHeap<E>::concatenate(ListCell *l1, ListCell *l2){
    if (l1->next == nullptr)
        l1->next = l2;
    else
        concatenate(l1->next,l2);
}

template<typename E>
void SoftHeap<E>::sift(Node *x) {
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
typename SoftHeap<E>::Node* SoftHeap<E>::combine(Node *x, Node *y) {
    Node *z = new Node(x, y);
    if (x->rank <= this->r)
        z->size = 1;
    else
        z->size = (3 * x->size + 1)/2;
    sift(z);
    return z;
}

template<typename E>
bool SoftHeap<E>::leaf(Node *x) {
    return x->left == nullptr && x->right == nullptr;
}

