#include "softheap.hh"
#include <iostream>


template<typename E>
void SoftHeap<E>::insert(E e) {
    meld(std::make_shared<SoftHeap<E>>(e));
}


template<typename E>
void SoftHeap<E>::swapLR(std::shared_ptr<Node> x) {
    x->left.swap(x->right);
}


template<typename E>
void SoftHeap<E>::thisSwap(std::shared_ptr<SoftHeap> Q) {
    this->first.swap(Q->first);

    int maxQ = Q->max_node_rank;
    int rkQ = Q->rank;
    double epsQ = Q->epsilon;

    Q->max_node_rank = this->max_node_rank;
    Q->rank = this->rank;
    Q->epsilon = this->epsilon;

    this->max_node_rank = maxQ;
    this->rank = rkQ;
    this->epsilon = epsQ;
}


template<typename E>
void SoftHeap<E>::meld(std::shared_ptr<SoftHeap> Q) {
    if (this->rank > Q->rank)
        thisSwap(Q);

    merge_into(Q);
    //SEEMS ALWAYS GOOD AFTER MERGE_INTO
    //The tricky one seems to be repeated_combine
    repeated_combine(Q, this->rank);

    //    Tree *cpy = this->first;
    thisSwap(Q);
    
}


//FIXME
template<typename E>
E SoftHeap<E>::pick_elem(std::shared_ptr<Node> x) {
    std::shared_ptr<ListCell> cpy = x->list;
    std::shared_ptr<ListCell> last = x->list;

    while (cpy != nullptr) {
        last.reset(cpy);
        cpy.reset(cpy->next);
    }

    E cpy_elem = last->elem;
    return cpy_elem;
}


template<typename E>
E SoftHeap<E>::extract_min() {
    if (this->first == nullptr)
        return NULL;

    std::shared_ptr<Tree> t = this->first->sufmin;
    std::shared_ptr<Node> *x = t->root;
    E e = pick_elem(x);

    if (listSize(x->list) <= x->size / 2) {
        if (!leaf(x)) {
            sift(x);
            update_suffix_min(t);
        } else if (x->list == nullptr)
            remove_tree(this, t);
    }
    return e;
}


template<typename E>
int SoftHeap<E>::listSize(std::shared_ptr<Node> x) {
    if (x->list == nullptr)
        return 0;
    std::shared_ptr<ListCell> list = x->list;
    int cpt = 1;
    while (list->next != nullptr) {
        list = list->next;
        cpt++;
    }
    return cpt;
}


template<typename E>
void SoftHeap<E>::concatenate(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2) {
    if (n1->list == nullptr and n2->list == nullptr)
        return;
    else if (n1->list == nullptr)
        n1->list = n2->list;
    else if (n2->list == nullptr)
        return;
    else {
        std::shared_ptr<ListCell> l = n1->list;
        while (l->next != nullptr)
            l = l->next;
        l->next = n2->list;
    }
}


template<typename E>
void SoftHeap<E>::sift(std::shared_ptr<Node> x) {
    while (listSize(x) < x->size && !leaf(x)) {
        if (x->left == nullptr || (x->right != nullptr && x->left->ckey > x->right->ckey))
            swapLR(x);

        concatenate(x, x->left);
        x->ckey = x->left->ckey;

	
        // CARE FROM THIS LINE, here because when concate,
        // we put addr in x, then we don't want to delete the addr,
        // that's why i'm setting x->left->list to nullptr
        x->left->list = nullptr;

        if (leaf(x->left)) {
            x->left = nullptr;
        } else
            sift(x->left);
    }
}


template<typename E>
typename std::shared_ptr<typename SoftHeap<E>::Node> SoftHeap<E>::combine(std::shared_ptr<Node> x, std::shared_ptr<Node> y) {
    std::shared_ptr<Node> z = std::make_shared<Node>(x, y);
    if (x->rank <= this->max_node_rank)
        z->size = 1;
    else
        z->size = (3 * x->size + 1) / 2;
    sift(z);
    return z;
}


template<typename E>
bool SoftHeap<E>::leaf(std::shared_ptr<Node> x) {
    return x->left == nullptr && x->right == nullptr;
}


template<typename E>
void SoftHeap<E>::merge_into(std::shared_ptr<SoftHeap> q) {
    if (this->rank > q->rank)
        return;

    std::shared_ptr<Tree> t1 = this->first;
    std::shared_ptr<Tree> t2 = q->first;

    while (t1 != nullptr) {
        while (t1->rank > t2->rank)
            t2 = t2->next;
        std::shared_ptr<Tree> t1bis = t1->next;
        insert_tree(q, t1, t2);
        t1 = t1bis;
    }
}


template<typename E>
void SoftHeap<E>::insert_tree(std::shared_ptr<SoftHeap> q, std::shared_ptr<Tree> t1, std::shared_ptr<Tree> t2) {
    t1->next = t2;
    if (t2->prev == nullptr) {
        q->first = t1;
        this->first = nullptr;
    } else
        t2->prev->next = t1;
    t2->prev = t1;

}


template<typename E>
void SoftHeap<E>::update_suffix_min(std::shared_ptr<Tree> t) {
    while (t != nullptr) {
        if (t->next == nullptr || t->root->ckey <= t->next->sufmin->root->ckey)
            t->sufmin = t;
        else
            t->sufmin = t->next->sufmin;
        t = t->prev;
    }
}


template<typename E>
void SoftHeap<E>::remove_tree(std::shared_ptr<SoftHeap> q, std::shared_ptr<Tree> t) {
    if (t->prev == nullptr)
        q->first = t->next;
    else
        t->prev->next = t->next;
    if (t->next != nullptr)
        t->next->prev = t->prev;
}


template<typename E>
void SoftHeap<E>::repeated_combine(std::shared_ptr<SoftHeap> q, int rk) {
    std::shared_ptr<Tree> t = q->first;
    while (t->next != nullptr) {
        if (t->next->rank == t->rank && (t->next->next == nullptr || t->rank != t->next->next->rank)) {
            t->root = combine(t->root, t->next->root);
            t->rank = t->root->rank;
            remove_tree(q, t->next);
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
E SoftHeap<E>::searchAndDestroy(std::shared_ptr<Node> parent, std::shared_ptr<Node> child, E e) {
    std::shared_ptr<ListCell> *l = child->list;
    E lft = NULL;
    E rgt = NULL;
    while (l != nullptr) {
        if (l->elem == e) {
            //DO MY DELETE BEHAVIOR FROM PSEUDO CODE
            return e;
        }
        l = l->next;
    }
    if (child->left != nullptr) {
        lft = searchAndDestroy(child, child->left, e);
        if (lft != NULL)
            return lft;
    }

    if (child->right != nullptr) {
        rgt = searchAndDestroy(child, child->right, e);
        if (rgt != NULL)
            return rgt;
    }
    return NULL;
}


template<typename E>
E SoftHeap<E>::deleteE(E e) {
    Tree *t = this->first;
    while (t != nullptr) {

        /******/

        std::shared_ptr<ListCell> l = t->root->list;
        E lft = NULL;
        E rgt = NULL;
        while (l != nullptr) {
            if (l->elem == e) {
                //DO MY DELETE BEHAVIOR FROM PSEUDO CODE
                return e;
            }
            l = l->next;
        }
        if (t->root->left != nullptr) {
            lft = searchAndDestroy(t->root, t->root->left, e);
            if (lft != NULL)
                return lft;
        }

        if (t->root->right != nullptr) {
            rgt = searchAndDestroy(t->root, t->root->right, e);
            if (rgt != NULL)
                return rgt;
        }

        /******/

        t = t->next;
    }
    return NULL;
}

int main() {
    std::shared_ptr<SoftHeap<int>> s = std::make_shared<SoftHeap<int>>(5);
    s->insert(3);
    s->insert(4);
    s->insert(6);

    std::shared_ptr<SoftHeap<int>> nw = std::make_shared<SoftHeap<int>>(2);
    nw->insert(2);
    nw->insert(3);

    s->meld(nw);
}
