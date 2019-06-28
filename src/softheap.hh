//
// Created by raph on 24/06/19.
//
#pragma once

#include <optional>
#include <iostream>
#include <cmath>
#include <typeinfo>


#define ABORTED_DEL 0
#define NOT_DELETED 1
#define DELETED 2


template<typename E>
struct SoftHeap {
    struct ListCell {
        E *elem;
        int del;
        ListCell *next;

        ListCell(E *e);

        ~ListCell();
    };

    struct Node {
        int rank, size, num;
        E *ckey;
        Node *left, *right;
        ListCell *list;

        Node(Node *l, Node *r);

        Node(E *e);

        ~Node();
    };

    struct Tree {
        Node *root;
        Tree *prev, *next, *sufmin;
        int rank;

        Tree(E *e);

        ~Tree();
    };

    SoftHeap(E *e);

    ~SoftHeap();

    void insert(E *e);

    int realDelete(E *e, bool force_delete = false);

    bool fakeDelete(E *e);

    void meld(SoftHeap *Q);

    std::optional<E*> extract_min();

    double epsilon;
    Tree *first;
    int max_node_rank;
    int rank;


  //    private:
    void sift(Node *x);

    Node *combine(Node *x, Node *y);

    int searchAndDestroy(Node *parent, Node *child, E *e, bool force_delete = false);

    bool searchAndDestroyFake(Node *child, E *e);

    void merge_into(SoftHeap *q);

    void repeated_combine(SoftHeap *q, int rk);

    void update_suffix_min(Tree *t);

    void insert_tree(SoftHeap *q, Tree *t1, Tree *t2);

    void remove_tree(SoftHeap *q, Tree *t);

    bool leaf(Node *x);

    void concatenate(Node *n1, Node *n2);

    E *pick_elem(Tree *t, int *deleted);

    void swapLR(Node *x);

    void thisSwap(SoftHeap *Q);

    int listSize(Node *x);

};


/*CONSTRUCTORS*/

template<typename E>
SoftHeap<E>::ListCell::ListCell(E *e) {
    this->elem = e;
    this->del = 1; //NOT_DELETED = 1
    this->next = nullptr;
}

template<typename E>
SoftHeap<E>::Node::Node(SoftHeap<E>::Node *l, SoftHeap<E>::Node *r) {
    this->list = nullptr;
    this->rank = l->rank + 1;
    this->size = 0;
    this->num = this->size;
    this->ckey = 0;
    this->left = l;
    this->right = r;
}

template<typename E>
SoftHeap<E>::Node::Node(E *e) {
    this->list = new ListCell(e);
    this->rank = 0;
    this->size = 1;
    this->num = this->size;
    this->ckey = e;
    this->left = nullptr;
    this->right = nullptr;
}

template<typename E>
SoftHeap<E>::Tree::Tree(E *e) {
    this->root = new Node(e);
    this->rank = 0;
    this->prev = nullptr;
    this->next = nullptr;
    this->sufmin = this;
}

template<typename E>
SoftHeap<E>::SoftHeap(E *e) {
    this->epsilon = 0.1;
    this->rank = 0;
    this->max_node_rank = log2(1. / this->epsilon) + 5;
    this->first = new Tree(e);
}


/*DESTRUCTORS*/


template<typename E>
SoftHeap<E>::~SoftHeap() {
    if (this->first != nullptr) {
        delete this->first;
        this->first = nullptr;
    }
}

template<typename E>
SoftHeap<E>::ListCell::~ListCell() {
    if (this->next != nullptr) {
        delete this->next;
        this->next = nullptr;
    }
}

template<typename E>
SoftHeap<E>::Node::~Node() {
    if (this->list != nullptr) {
        delete this->list;
        this->list = nullptr;
    }
    if (this->left != nullptr) {
        delete this->left;
        this->left = nullptr;
    }
    if (this->right != nullptr) {
        delete this->right;
        this->right = nullptr;
    }
}

template<typename E>
SoftHeap<E>::Tree::~Tree() {
    if (this->root != nullptr) {
        delete this->root;
        this->root = nullptr;
    }
    if (this->prev != nullptr) {
        this->prev->next = nullptr;
        delete this->prev;
        this->prev = nullptr;
    }
    if (this->next != nullptr) {
        this->next->prev = nullptr;
        delete this->next;
        this->next = nullptr;
    }
}

#include "softheap.hxx"
