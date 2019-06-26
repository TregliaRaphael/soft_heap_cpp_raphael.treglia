#include "softheap.hh"
#include <iostream>


template<typename E>
void SoftHeap<E>::insert(E e) {
    meld(new SoftHeap<E>(e));
}


template<typename E>
void SoftHeap<E>::swapLR(Node *x) {
    Node *tmp = x->left;
    x->left = x->right;
    x->right = tmp;
}


template<typename E>
void SoftHeap<E>::thisSwap(SoftHeap *Q) {
    Tree *tQ = Q->first;
    int maxQ = Q->max_node_rank;
    int rkQ = Q->rank;
    double epsQ = Q->epsilon;

    Q->first = this->first;
    Q->max_node_rank = this->max_node_rank;
    Q->rank = this->rank;
    Q->epsilon = this->epsilon;

    this->first = tQ;
    this->max_node_rank = maxQ;
    this->rank = rkQ;
    this->epsilon = epsQ;
}


template<typename E>
void SoftHeap<E>::meld(SoftHeap *Q) {
    if (this->rank > Q->rank)
        thisSwap(Q);

    merge_into(Q);
    //SEEMS ALWAYS GOOD AFTER MERGE_INTO
    //The tricky one seems to be repeated_combine
    repeated_combine(Q, this->rank);

    Tree *cpy = this->first;
    thisSwap(Q);
    delete cpy;
}


//FIXME
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
        return NULL;

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
    SoftHeap<E>::ListCell *list = this;
    if (list == nullptr)
        return 0;
    int cpt = 1;
    while (list->next != nullptr) {
        list = list->next;
        cpt++;
    }
    return cpt;
}


template<typename E>
void SoftHeap<E>::concatenate(Node *n1, Node *n2) {
    if (n1->list == nullptr and n2->list == nullptr)
        return;
    else if (n1->list == nullptr)
        n1->list = n2->list;
    else if (n2->list == nullptr)
        return;
    else {
        ListCell *l = n1->list;
        while (l->next != nullptr)
            l = l->next;
        l->next = n2->list;
    }
}


template<typename E>
void SoftHeap<E>::sift(Node *x) {
    while (x->list->size() < x->size && !leaf(x)) {
        if (x->left == nullptr || (x->right != nullptr && x->left->ckey > x->right->ckey))
            swapLR(x);

        concatenate(x, x->left);
        x->ckey = x->left->ckey;

        // CARE FROM THIS LINE, here because when concate,
        // we put addr in x, then we don't want to delete the addr,
        // that's why i'm setting x->left->list to nullptr
        x->left->list = nullptr;

        if (leaf(x->left)) {
            delete x->left;
            x->left = nullptr;
        } else
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
    if (t2->prev == nullptr) {
        q->first = t1;
        this->first = nullptr;
    } else
        t2->prev->next = t1;
    t2->prev = t1;

}


template<typename E>
void SoftHeap<E>::update_suffix_min(Tree *t) {
    while (t != nullptr) {
        if (t->next == nullptr || t->root->ckey <= t->next->sufmin->root->ckey)
            t->sufmin = t;
        else
            t->sufmin = t->next->sufmin;
        t = t->prev;
    }
}


template<typename E>
void SoftHeap<E>::remove_tree(SoftHeap *q, Tree *t) {
    if (t->prev == nullptr)
        q->first = t->next;
    else
        t->prev->next = t->next;
    if (t->next != nullptr)
        t->next->prev = t->prev;
}


template<typename E>
void SoftHeap<E>::repeated_combine(SoftHeap *q, int rk) {
    Tree *t = q->first;
    while (t->next != nullptr) {
        if (t->next->rank == t->rank && (t->next->next == nullptr || t->rank != t->next->next->rank)) {
            t->root = combine(t->root, t->next->root);
            t->rank = t->root->rank;
            //FIXME STORE T->NEXT
            remove_tree(q, t->next);
            //FIXME DELETE T->NEXT
        } else if (t->rank > rk)
            break;
        else
            t = t->next;
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
            /////FIXME DELETE ELEM
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
    s->insert(3);
    s->insert(3);
    s->insert(6);
    std::cout << "CREATE SOFT HEAP WORKS" << std::endl;
    delete s;
}