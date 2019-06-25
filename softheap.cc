#include "softheap.hh"
#include <iostream>


template<typename E>
void SoftHeap<E>::insert(E e) {
    meld(new SoftHeap<E>(e));
}


template<typename E>
void swap(E *a, E *b) {
    E cpy = *a;
    *a = *b;
    *b = cpy;
}


template<typename E>
void SoftHeap<E>::meld(SoftHeap *Q) {
    if (this->rank > Q->rank) {
        swap(this, Q);
    }

    merge_into(this, Q);
    repeated_combine(Q, this->rank);

    Tree *cpy = this->first;
    this->epsilon = Q->epsilon;
    this->rank = Q->rank;
    this->max_node_rank = Q->max_node_rank;

    this->first = Q->first;

    delete cpy;
}

template<typename E>
E SoftHeap<E>::pick_elem(Node *x) {
    SoftHeap<E>::ListCell *cpy = x->list;
    SoftHeap<E>::ListCell *last = x->list;

    while (cpy != nullptr) {
        last = cpy;
        cpy = cpy->next;
    }

    E cpy_elem = last->elem;
    delete last;
    return cpy_elem;
}

template<typename E>
E SoftHeap<E>::extract_min() {
    if (this->first == nullptr)
        return nullptr;

    auto Tree = this->first->sufmin;
    Node *x = Tree->root;
    E e = pick_elem(x);

    if (x->list.size() <= x->size / 2) {
        if (leaf(x) == nullptr) {
            sift(x);
            update_suffix_min(Tree);
        } else if (x->list == nullptr)
            remove_tree(this, Tree);
    }
    return e;
}


template<typename E>
int SoftHeap<E>::ListCell::size() {
    SoftHeap<E>::ListCell list = this;
    if (list == nullptr)
        return 0;
    int cpt = 1;
    while (list->next) {
        list = list->next;
        cpt++;
    }
    return cpt;
}

template<typename E>
void SoftHeap<E>::concatenate(ListCell *l1, ListCell *l2) {
    if (l1->next == nullptr)
        l1->next = l2;
    else
        concatenate(l1->next, l2);
}

template<typename E>
void SoftHeap<E>::sift(Node *x) {
    while (x->list->size() < x->size && !leaf(x)) {
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
typename SoftHeap<E>::Node *SoftHeap<E>::combine(Node *x, Node *y) {
    Node *z = new Node(x, y);
    if (x->rank <= this->max_node_rank)
        z->size = 1;
    else
        z->size = (3 * x->size + 1) / 2;
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

    while (t1 != nullptr) {
        while (t1->rank > t2->rank)
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
    while (t != nullptr) {
        if (t->root->ckey <= t->next->sufmin->root->ckey)
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
    while (t->next != nullptr) {
        if (t->next->rank == t->rank && (t->next->next == nullptr || t->rank != t->next->next->rank)) {
            t->root = combine(t->root, t->next->root);
            t->rank = t->root->rank;
            remove_tree(q, t->next);
        } else if (t->rank > k)
            break;
        t->next;
    }

    if (t->rank > q->rank)
        q->rank = t->rank;
    update_suffix_min(t);
}

template<typename E>
bool SoftHeap<E>::searchAndDestroy(Node *x, E e) {
    ListCell *l = x->list;
    bool lft = false;
    bool rgt = false;
    while (l != nullptr) {
        if (l->elem == e) {
            /////
            return true;
        }
        l = l->next;
    }
    if (x->left != nullptr)
        lft = searchAndDestroy(x->left, e);
    if (!lft && x->right != nullptr)
        rgt = searchAndDestroy(x->right, e);
    return lft || rgt;
}

template<typename E>
bool SoftHeap<E>::deleteE(E e) {
    Tree *t = this->first;
    while (t != nullptr) {
        bool tmp = searchAndDestroy(t->root, e);
        if (tmp)
            return tmp;
        t = t->next;
    }
    return false;
}

int main() {
    SoftHeap<int> *s = new SoftHeap<int>(5);
    std::cout << "CREATE SOFT HEAP WORKS" << std::endl;
    delete s;
}