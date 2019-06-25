//
// Created by raph on 24/06/19.
//
#pragma once

#include <iostream>
#include <cmath>


template<typename E>
struct SoftHeap {
    struct ListCell {
        E elem;
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

private:
    double epsilon;
    Tree *first;
    double max_node_rank;
    int rank;

    /*FIXME*/
    void sift(Node *x) = 0;
    Node *combine(Node *x, Node *y) = 0;
    void meld(SoftHeap *q) = 0;
    void insert(E e) = 0;
    E extract_min() = 0;
    void merge_into(SoftHeap *q) = 0;
    void repeated_combine(SoftHeap *q, int k) = 0;
    void update_suffix_min(Tree *t) = 0;
    void insert_tree(SoftHeap *q, Tree *t1, Tree *t2) = 0;
    void remove_tree(SoftHeap *q, Tree *t) = 0;
    Tree* make_tree(E e) = 0;
    Node* make_node(E e) = 0;
    bool leaf(Node *x) = 0;
    void concatenate(ListCell *l1, ListCell *l2) = 0;
    /*FIXME*/

};


/*CONSTRUCTORS*/

template<typename E>
SoftHeap<E>::ListCell::ListCell(E e) {
  this->elem = e;
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
  this->suffmin = this;
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
    delete this->first;
    this->first = nullptr;
}

template<typename E>
SoftHeap<E>::ListCell::~ListCell(){
    delete this->next;
    this->next = nullptr;
    delete this->elem;
    this->elem = nullptr;
}

template<typename E>
SoftHeap<E>::Tree::~Tree(){
    delete this->root;
    this->root = nullptr;
    delete this->prev;
    this->prev = nullptr;
    delete this->next;
    this->next = nullptr;
    delete this->sufmin;
    this->sufmin = nullptr;
}

template<typename E>
SoftHeap<E>::Node::~Node(){
    delete this->list;
    this->list = nullptr;
    delete this->left;
    this->left = nullptr;
    delete this->right;
    this->right = nullptr;
}

template <typename E>
void swap (E *a, E* b);
