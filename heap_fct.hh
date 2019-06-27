#pragma once

#include "softheap.hh"
#include <iostream>
#include <cassert>
#include <optional>

template<typename E>
void SoftHeap<E>::insert(E e) {
    SoftHeap<E> *q = new SoftHeap<E>(e);
    meld(q);
    delete q;
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

    thisSwap(Q);
}


template<typename E>
E SoftHeap<E>::pick_elem(Tree *t) {
    SoftHeap<E>::ListCell *actual = t->root->list;
    E act_elem = actual->elem;
    if (actual->next == nullptr) {
        delete t->root->list;
        t->root->list = nullptr;
        sift(t->root);
    }
        /*First elt of the list size > 1*/
    else {
        t->root->list = actual->next;
        actual->next = nullptr;
        delete actual;
    }

    return act_elem;
}


template<typename E>
E SoftHeap<E>::extract_min() {
    if (this->first == nullptr)
        return 0;//FIXME PUT OPTIONAL

    Tree *t = this->first->sufmin;
    Node *x = t->root;
    E e = pick_elem(t);

    if (listSize(x) <= x->size / 2) {
        if (!leaf(x)) {
            sift(x);
            update_suffix_min(t);
        } else if (x->list == nullptr) {
            delete x;
            remove_tree(this, t);
        }

        if (t->prev != NULL)
            update_suffix_min(t->prev);
        t->prev = nullptr;
        t->root = nullptr;
        delete t;
    }
    return e;
}


template<typename E>
int SoftHeap<E>::listSize(Node *x) {
    if (x->list == nullptr)
        return 0;
    ListCell *list = x->list;
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
    else if (n1->list == nullptr) {
        n1->list = n2->list;
        n1->num = n2->num;
        n2->num = 0;
    } else if (n2->list == nullptr)
        return;
    else {
        ListCell *l = n1->list;
        while (l->next != nullptr)
            l = l->next;
        l->next = n2->list;
        n1->num += n2->num;
        n2->num = 0;
    }
    n2->list = nullptr;
    //FIXME do smtg with nelemns when delete will works
}


template<typename E>
void SoftHeap<E>::sift(Node *x) {
    while (listSize(x) < x->size && !leaf(x)) {
        if (x->left == nullptr || (x->right != nullptr && x->left->ckey > x->right->ckey))
            swapLR(x);

        concatenate(x, x->left);
        x->ckey = x->left->ckey;

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

            /*Want to delete just the tree object and not what is inside*/
            Tree *todelete = t->next;
            remove_tree(q, t->next);
            todelete->prev = nullptr;
            todelete->next = nullptr;
            todelete->root = nullptr;
            delete todelete;

        } else if (t->rank > rk)
            break;
        else
            t = t->next;
    }

    if (t->rank > q->rank)
        q->rank = t->rank;
    update_suffix_min(t);
}

/**
 * Lets assume that this function delete and stop at the first occurence of the e element
 * About the case when e is present not only one time in the heap
 * This function is the users delete and not the delete of the extract
 * @tparam E
 * @param parent
 * @param child
 * @param e
 * @return
 */
template<typename E>
bool SoftHeap<E>::searchAndDestroy(Node *parent, Node *child, E e) {
    assert(listSize(child) != 0);

    ListCell *l = child->list;
    ListCell *prev = nullptr;
    bool lft, rgt;

    while (l != nullptr) {
        if (l->elem == e) {
            kickEFromList(prev, l, parent, child);
            return true;
        }
        prev = l;
        l = l->next;
    }

    if (child->left != nullptr) {
        lft = searchAndDestroy(child, child->left, e);
        if (lft)
            return true;
    }

    if (child->right != nullptr) {
        rgt = searchAndDestroy(child, child->right, e);
        if (rgt)
            return true;
    }
    return false;
}


template<typename E>
void SoftHeap<E>::kickEFromList(ListCell *prev, ListCell *actual, Node *parent, Node *child) {
    /*If only one element*/
    if (prev == nullptr && actual->next == nullptr) {
        delete child->list;
        child->list = nullptr;
        sift(child);
        if (leaf(child)) {
            if (parent->left == child)
                parent->left = nullptr;
            else
                parent->right = nullptr;

            //IF e become a allocated ptr var,
            // we'll need to put child->ckey = nullptr; before delete
            delete child;
        }
    }
        /*First elt of the list size > 1*/
    else if (prev == nullptr) {
        child->list = actual->next;
        actual->next = nullptr;
        delete actual;
    }
        /*Last element*/
    else if (actual->next == nullptr) {
        prev->next = nullptr;
        delete actual;
    }
        /*Element in the middle of the list*/
    else {
        prev->next = actual->next;
        delete actual;
    }
}


template<typename E>
bool SoftHeap<E>::deleteE(E e) {
    Tree *t = this->first;
    while (t != nullptr) {
        ListCell *l = t->root->list;
        ListCell *prev = nullptr;
        assert(listSize(t->root) != 0);
        bool lft, rgt;
        while (l != nullptr) {
            if (l->elem == e) {
                if (prev == nullptr && l->next == nullptr) {
                    delete t->root->list;
                    t->root->list = nullptr;
                    sift(t->root);
                    if (leaf(t->root)) {
                        //IF e become a allocated ptr var,
                        // we'll need to put child->ckey = nullptr; before delete
                        delete t->root;
                        t->root = nullptr;
                    }
                }
                    /*First elt of the list size > 1*/
                else if (prev == nullptr) {
                    t->root->list = l->next;
                    l->next = nullptr;
                    delete l;
                }
                    /*Last element*/
                else if (l->next == nullptr) {
                    prev->next = nullptr;
                    delete l;
                }
                    /*Element in the middle of the list*/
                else {
                    prev->next = l->next;
                    delete l;
                }
                return true;
            }
            prev = l;
            l = l->next;
        }
        if (t->root->left != nullptr) {
            lft = searchAndDestroy(t->root, t->root->left, e);
            if (lft)
                return true;
        }

        if (t->root->right != nullptr) {
            rgt = searchAndDestroy(t->root, t->root->right, e);
            if (rgt)
                return true;
        }

        t = t->next;
    }
    return false;
}


