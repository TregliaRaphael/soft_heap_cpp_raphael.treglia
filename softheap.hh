//
// Created by raph on 24/06/19.
//
#pragma once

#include <iostream>
#include <cmath>
#include <typeinfo>
#include <memory>

template<typename E>
struct SoftHeap {
    struct ListCell {
        E elem;
        std::shared_ptr<ListCell> next;

        ListCell(E e);
    };

    struct Node {
        int rank, size;
        E ckey;
        std::shared_ptr<Node> left, right;
        std::shared_ptr<ListCell> list;

        Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r);

        Node(E e);
    };

    struct Tree {
        std::shared_ptr<Node> root;
        std::shared_ptr<Tree> prev, next, sufmin;
        int rank;

        Tree(E e);
    };

    SoftHeap(E e);


    void insert(E e);

    E deleteE(E e);

    void meld(std::shared_ptr<SoftHeap> Q);

    E extract_min();

    double epsilon;
    std::shared_ptr<Tree> first;
    int max_node_rank;
    int rank;


    private:
    void sift(std::shared_ptr<Node> x);

    std::shared_ptr<Node> combine(std::shared_ptr<Node> x, std::shared_ptr<Node> y);

    E searchAndDestroy(std::shared_ptr<Node> parent, std::shared_ptr<Node> child, E e);

    void merge_into(std::shared_ptr<SoftHeap> q);

    void repeated_combine(std::shared_ptr<SoftHeap> q, int rk);

    void update_suffix_min(std::shared_ptr<Tree> t);

    void insert_tree(std::shared_ptr<SoftHeap> q, std::shared_ptr<Tree> t1, std::shared_ptr<Tree> t2);

    void remove_tree(std::shared_ptr<SoftHeap> q, std::shared_ptr<Tree> t);

    bool leaf(std::shared_ptr<Node> x);

    void concatenate(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);

    E pick_elem(std::shared_ptr<Node> x);

    void swapLR(std::shared_ptr<Node> x);

    void thisSwap(std::shared_ptr<SoftHeap> Q);

    int listSize(std::shared_ptr<Node> x);

};


/*CONSTRUCTORS*/

//FIXME NEW E
template<typename E>
SoftHeap<E>::ListCell::ListCell(E e) {
    this->elem = e;
    this->next = nullptr;
}

template<typename E>
SoftHeap<E>::Node::Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r) {
    this->list = nullptr;
    this->rank = l->rank + 1;
    this->size = 0;
    this->ckey = 0;
    this->left = l;
    this->right = r;
}

//FIXME NEW E
template<typename E>
SoftHeap<E>::Node::Node(E e) {
    this->list = std::make_shared<ListCell>(e);
    this->rank = 0;
    this->size = 1;
    this->ckey = e;
    this->left = nullptr;
    this->right = nullptr;
}

template<typename E>
SoftHeap<E>::Tree::Tree(E e) {
    this->root = std::make_shared<Node>(e);
    this->rank = 0;
    this->prev = nullptr;
    this->next = nullptr;
    this->sufmin = (std::shared_ptr<Tree>)this;
}

template<typename E>
SoftHeap<E>::SoftHeap(E e) {
    this->epsilon = 0.1;
    this->rank = 0;
    this->max_node_rank = log2(1. / this->epsilon) + 5;
    this->first = std::make_shared<Tree>(e);
}