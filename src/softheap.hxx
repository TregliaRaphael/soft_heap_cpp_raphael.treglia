#include <iostream>
#include <cassert>

template<typename E>
void SoftHeap<E>::insert(E *e) {
    if (this->first == nullptr) {
        this->first = new Tree(e);
    }
    else{
        SoftHeap <E> *q = new SoftHeap<E>(e);
        meld(q);
        delete q;
    }
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
    Q->first = nullptr;
}


template<typename E>
E *SoftHeap<E>::pick_elem(Tree *t, int *deleted) {
    SoftHeap<E>::ListCell *actual = t->root->list;
    E *act_elem = actual->elem;
    *deleted = actual->del;
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
    t->root->num--;
    return act_elem;
}


template<typename E>
std::optional<E *> SoftHeap<E>::extract_min() {
    int *deleted = new int(2);//DELETED = 2
    E *e = nullptr;
    while (*deleted == DELETED) {
        if (this->first == nullptr) {
            delete deleted;
            return std::nullopt;
        }

        Tree *t = this->first->sufmin;
        Node *x = t->root;
        e = pick_elem(t, deleted);

        if (x->num <= x->size / 2) {
            if (!leaf(x)) {
                sift(x);
                update_suffix_min(t);
            } else if (x->num == 0) {
                delete x;
                remove_tree(this, t);

                if (t->next == nullptr) {
                    if (t->prev == nullptr)
                        this->rank = -1;
                    else
                        this->rank = t->prev->rank;
                }

                if (t->prev != NULL)
                    update_suffix_min(t->prev);
                t->prev = nullptr;
                t->next = nullptr;
                t->root = nullptr;
                delete t;
            }
        }
    }
    delete deleted;
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
    n1->num += n2->num;
    n2->num = 0;
    n2->list = nullptr;
}


template<typename E>
void SoftHeap<E>::sift(Node *x) {
    while (x->num < x->size && !leaf(x)) {
        if (x->left == nullptr || (x->right != nullptr && *x->left->ckey > *x->right->ckey))
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
        if (t->next == nullptr || *t->root->ckey <= *t->next->sufmin->root->ckey)
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
            Tree *to_delete = t->next;
            remove_tree(q, t->next);
            to_delete->prev = nullptr;
            to_delete->next = nullptr;
            to_delete->root = nullptr;
            delete to_delete;

        } else if (t->rank > rk)
            break;
        else
            t = t->next;
    }

    if (t->rank > q->rank)
        q->rank = t->rank;
    update_suffix_min(t);
}


/*************DELETE*************/


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
int SoftHeap<E>::searchAndDestroy(Node *parent, Node *child, E *e, bool force_delete) {
    assert(listSize(child) != 0);

    ListCell *l = child->list;
    ListCell *prev = nullptr;
    int success = NOT_DELETED;

    while (l != nullptr) {
        if (*l->elem == *e) {
            if (l->del == 2 && !force_delete)
                return ABORTED_DEL;

            if (prev == nullptr && l->next == nullptr) {
                child->list = nullptr;
                child->num--;
                sift(child);
                if (parent->left == child && parent->left->list == nullptr) {
                    parent->left = nullptr;
                    delete child;
                } else if (parent->right == child && parent->right->list == nullptr) {
                    parent->right = nullptr;
                    delete child;
                }
            }
                /*First elt of the list size > 1*/
            else if (prev == nullptr) {
                child->list = l->next;
                l->next = nullptr;
            }
                /*Last element*/
            else if (l->next == nullptr)
                prev->next = nullptr;

                /*Element in the middle of the list*/
            else
                prev->next = l->next;

            delete l;
            return DELETED;
        }
        prev = l;
        l = l->next;
    }

    if (child->left != nullptr) success = searchAndDestroy(child, child->left, e, force_delete);
    if (success == NOT_DELETED && child->right != nullptr) success = searchAndDestroy(child, child->right, e, force_delete);
    return success;
}


template<typename E>
int SoftHeap<E>::realDelete(E *e, bool force_delete) {
    Tree *t = this->first;
    int success = NOT_DELETED;
    while (t != nullptr) {

        ListCell *l = t->root->list;
        ListCell *prev = nullptr;
        assert(listSize(t->root) != 0);

        while (l != nullptr) {
            if (*l->elem == *e) {
                if (l->del == 2 && !force_delete)
                    return ABORTED_DEL;

                if (prev == nullptr && l->next == nullptr) {
                    l = t->root->list;
                    t->root->list = nullptr;
                    t->root->num--;
                    sift(t->root);
                    if (t->root->list == nullptr) {
                        if (t->next == nullptr and t->prev == nullptr)
                            this->first = nullptr;
                        else if (t->prev == nullptr) {
                            t->next->prev = nullptr;
                            this->first = t->next;
                        }
                        else if (t->next == nullptr)
                            t->prev->next = nullptr;
                        else
                            t->prev->next = t->next;
                        update_suffix_min(this->first);
                        t->next = nullptr;
                        t->prev = nullptr;
                        delete t;
                    }
                }
                    /*First elt of the list size > 1*/
                else if (prev == nullptr) {
                    t->root->list = l->next;
                    l->next = nullptr;
                }
                    /*Last element*/
                else if (l->next == nullptr)
                    prev->next = nullptr;

                    /*Element in the middle of the list*/
                else
                    prev->next = l->next;

                delete l;

                return DELETED;
            }
            prev = l;
            l = l->next;
        }
        if (t->root->left != nullptr) success = searchAndDestroy(t->root, t->root->left, e, force_delete);
        if (success == NOT_DELETED && t->root->right != nullptr) success = searchAndDestroy(t->root, t->root->right, e, force_delete);
        if (success == DELETED || success == ABORTED_DEL)break;
        t = t->next;
    }
    return success;
}


/*******FAKE DELETE********/



template<typename E>
bool SoftHeap<E>::fakeDelete(E *e) {
    Tree *t = this->first;
    bool success = false;
    while (t != nullptr) {
        ListCell *l = t->root->list;
        assert(listSize(t->root) != 0);
        while (l != nullptr) {
            if (*l->elem == *e) {
                l->del = 2; //DELETED = 2
                return true;
            }
            l = l->next;
        }
        if (t->root->left != nullptr) success = searchAndDestroyFake(t->root->left, e);
        if (!success && t->root->right != nullptr) success = searchAndDestroyFake(t->root->right, e);
        if (success) break;
        t = t->next;
    }
    return success;
}

template<typename E>
bool SoftHeap<E>::searchAndDestroyFake(Node *child, E *e) {
    assert(listSize(child) != 0);

    ListCell *l = child->list;
    bool success = false;

    while (l != nullptr) {
        if (*l->elem == *e) {
            l->del = 2; //DELETED = 2
            return true;
        }
        l = l->next;
    }

    if (child->left != nullptr) success = searchAndDestroyFake(child->left, e);
    if (!success && child->right != nullptr) success = searchAndDestroyFake(child->right, e);
    return success;
}
