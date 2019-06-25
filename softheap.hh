//
// Created by raph on 24/06/19.
//
#pragma once

#include <iostream>
#include <cmath>
#include <typeinfo>

template<typename E>
struct SoftHeap {
    struct ListCell {
        E* elem;
        ListCell *next;
        int size();

        ListCell(E e);
        ~ListCell();
    };

    struct Node {
        int rank, size, ckey;
        Node *left, *right;
        ListCell *list;

        Node(Node *l, Node *r);
        Node(E e);
        ~Node();
    };

    struct Tree {
        Node *root;
        Tree *prev, *next, *sufmin;
        int rank;

        Tree(E e);
        ~Tree();
    };

    SoftHeap(E e);
    ~SoftHeap();

    void insert(E e);
    bool deleteE(E e);
    void meld(SoftHeap *Q);
    E extract_min();

private:
    double epsilon;
    Tree *first;
    double max_node_rank;
    int rank;

    void sift(Node *x);
    Node *combine(Node *x, Node *y);
    bool searchAndDestroy(Node *x, E e);
    void merge_into(SoftHeap *q);
    void repeated_combine(SoftHeap *q, int k);
    void update_suffix_min(Tree *t);
    void insert_tree(SoftHeap *q, Tree *t1, Tree *t2);
    void remove_tree(SoftHeap *q, Tree *t);
    bool leaf(Node *x);
    void concatenate(ListCell *l1, ListCell *l2);
    E pick_elem(Node* x);

};


/*CONSTRUCTORS*/

template<typename E>
SoftHeap<E>::ListCell::ListCell(E e) {
  this->elem = new E(e);
  this->next = nullptr;
}

template<typename E>
SoftHeap<E>::Node::Node(SoftHeap<E>::Node *l, SoftHeap<E>::Node *r) {
    this->list = nullptr;
    this->rank = left->rank + 1;
    this->size = nullptr;
    this->ckey = nullptr;
    this->left = l;
    this->right = r;
}

template<typename E>
SoftHeap<E>::Node::Node(E e) {
  this->list = new ListCell(e);
  this->rank = 0;
  this->size = 1;
  this->ckey = e;
  this->left = nullptr;
  this->right = nullptr;
}

template<typename E>
SoftHeap<E>::Tree::Tree(E e) {
  this->root = new Node(e);
  this->rank = 0;
  this->prev = nullptr;
  this->next = nullptr;
  this->sufmin = this;
}

template<typename E>
SoftHeap<E>::SoftHeap(E e) {
    this->epsilon = 0.5;
    this->rank = 0;
    this->max_node_rank = log2(1. / this->epsilon) + 5;
    this->first = new Tree(e);
}


/*DESTRUCTORS*/


template<typename E>
SoftHeap<E>::~SoftHeap(){
    if (this->prev != nullptr)
        delAndSetNullptr(this->first);
}

template<typename E>
SoftHeap<E>::ListCell::~ListCell(){
    if (this->prev != nullptr)
        delAndSetNullptr(this->next);
    if (this->prev != nullptr)
        delAndSetNullptr(this->elem);
}

template<typename E>
SoftHeap<E>::Node::~Node(){
    if (this->list != nullptr)
        delAndSetNullptr(this->list);
    if (this->left != nullptr)
        delAndSetNullptr(this->left);
    if (this->right != nullptr)
        delAndSetNullptr(this->right);
}

template<typename E>
SoftHeap<E>::Tree::~Tree(){
    if (this->root != nullptr)
        delAndSetNullptr(this->root);
    if (this->prev != nullptr)
        delAndSetNullptr(this->prev);
    if (this->next != nullptr)
        delAndSetNullptr(this->next);
    if (this->prev != nullptr)
        delAndSetNullptr(this->sufmin);
}

/*SWAP DEC*/

template <typename E>
void swap (E *a, E* b);

/*DELETE AND SET NULL*/
template<typename E>
void delAndSetNullptr(E *e){
    delete e;
    e = nullptr;
}