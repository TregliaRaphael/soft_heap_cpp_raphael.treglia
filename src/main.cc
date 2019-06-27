#include <iostream>
#include "softheap.hh"

int main() {
    SoftHeap<int> *s = new SoftHeap<int>(5);
    s->insert(3);
    s->insert(4);
    s->insert(6);
    s->insert(7);
    s->insert(8);

    std::cout << "DELETE 6: " << s->fakeDelete(6) << std::endl;
    std::cout << "DELETE 3: " << s->fakeDelete(3) << std::endl;
    std::cout << "DELETE 4: " << s->fakeDelete(4) << std::endl;
    std::cout << "DELETE 5: " << s->fakeDelete(5) << std::endl;



    SoftHeap<int> *nw = new SoftHeap<int>(2);
    nw->insert(1);
    nw->insert(9);

    s->meld(nw);

    std::cout << *s->extract_min() << std::endl;
    std::cout << *s->extract_min() << std::endl;
    std::cout << *s->extract_min() << std::endl;
    std::cout << *s->extract_min() << std::endl;
    std::cout << *s->extract_min() << std::endl;
    std::cout << *s->extract_min() << std::endl;
    std::cout << *s->extract_min() << std::endl;
    std::cout << *s->extract_min() << std::endl;
    std::cout << *s->extract_min() << std::endl;

    delete nw;
    delete s;
}
