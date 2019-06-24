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
        ~ListCell();
    };

    struct Node {
        int rank, size, ckey;
        Node *left, *right;
        ListCell *first;
        ~Node();
    };

    struct Tree {
        Node *root;
        Tree *prev, *next, *sufmin;
        int rank;
        ~Tree();
    };

    SoftHeap(E e);
    ~SoftHeap();

private:
    double epsilon;
    Tree *first;
    double max_node_rank;
    int rank;


};


/*CONSTRUCTORS*/


template<typename E>
SoftHeap<E>::SoftHeap(E e) {
    this->epsilon = 0.5;
    this->rank = 0;
    this->max_node_rank = log2(1. / this->epsilon) + 5;
    this->first = nullptr;
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
    delete this->first;
    this->first = nullptr;
    delete this->left;
    this->left = nullptr;
    delete this->right;
    this->right = nullptr;
}