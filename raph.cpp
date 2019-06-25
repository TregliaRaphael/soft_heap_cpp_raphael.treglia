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

template<typename E>
void SoftHeap<E>::merge_into(SoftHeap *q) {
    if (this->rank > q->rank)
        return;

    Tree *t1 = this->first;
    Tree *t2 = q->first;

    while(t1 != nullptr){
        while(t1->rank > t2->rank)
            t2 = t2->next;
        Tree *t1bis = t1->next;
        insert_tree(q, t1, t2);
        t1 = t1bis;
    }
}

template<typename E>
void SoftHeap<E>::insert_tree(SoftHeap *q, Tree *t1, Tree *t2) {
    t1->next = t2;
    if (t2->prev == nullptr)
        q->first = t1;
    else
        t2->prev->next = t1;
}

template<typename E>
void SoftHeap<E>::update_suffix_min(Tree *t) {
    while(t != nullptr) {
        if(t->root->ckey <= t->next->sufmin->root->ckey)
            t->sufmin = t;
        else
            t->sufmin = t->next->sufmin;
        t = t->prev;
    }
}

template<typename E>
void SoftHeap<E>::remove_tree(SoftHeap *q, Tree *t) {
    Tree *to_delete = t;
    if (t->prev == nullptr)
        q->first = t->next;
    else
        t->prev->next = t->next;
    if (t->next != nullptr)
        t->next->prev = t->prev;

    to_delete->next = nullptr;
    to_delete->prev = nullptr;
    delete to_delete;
}

template<typename E>
void SoftHeap<E>::repeated_combine(SoftHeap *q, int k) {
    Tree *t = q->first;
    while(t->next != nullptr){
        if (t->rank == t->next->rank)
            if (t->next->next == nullptr || t->rank != t->next->next->rank){
                t->root = combine(t->root, t->next->root);
                t->rank = t->root->rank;
                remove_tree(q, t->next);
            }
        else if (t->rank > k)
            break;
        t->next;
    }

    if (t->rank > q->rank)
        q->rank = t->rank;
    update_suffix_min(t);
}