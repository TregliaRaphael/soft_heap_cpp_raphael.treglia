#include <iostream>
#include "softheap.hh"
#include <string>


class Str {
public:
    std::string s;

    Str(std::string _s) {
        this->s = _s;
    }

    bool operator>(Str &other) {
        return this->s.size() > other.s.size();
    }

    bool operator<(Str &other) {
        return this->s.size() < other.s.size();
    }

    bool operator>=(Str &other) {
        return this->s.size() >= other.s.size();
    }

    bool operator<=(Str &other) {
        return this->s.size() <= other.s.size();
    }

    bool operator==(Str &other) {
        return this->s.size() == other.s.size();
    }

    bool operator!=(Str &other) {
        return this->s.size() != other.s.size();
    }
};


int main() {
    auto *tata = new Str("tata"), *z = new Str("z"), *ttttttt = new Str("ttttttt"), *xz = new Str("xz"),
            *azezaeazeeze = new Str("azezaeazeeze"), *zzz = new Str("zzz");

    SoftHeap<Str> *s = new SoftHeap<Str>(tata);
    s->insert(z);
    s->insert(ttttttt);
    s->insert(xz);
    s->insert(azezaeazeeze);
    s->insert(zzz);

    std::cout << "DELETE tata: " << s->fakeDelete(tata) << std::endl;
    std::cout << "DELETE zzz: " << s->fakeDelete(zzz) << std::endl;
    std::cout << "DELETE xz: " << s->fakeDelete(xz) << std::endl;
    std::cout << "DELETE ttttttt: " << s->fakeDelete(ttttttt) << std::endl;


    auto *treze = new Str("treze"), *braaaa = new Str("braaaa"), *tkqiazezz = new Str("tkqiazezz");
    SoftHeap<Str> *nw = new SoftHeap<Str>(treze);
    nw->insert(braaaa);
    nw->insert(tkqiazezz);

    s->meld(nw);

    std::optional <Str*> tmp = s->extract_min();
    while (tmp.value_or(nullptr) != nullptr) {
        std::cout << (*tmp)->s << std::endl;
        tmp = s->extract_min();
    }


    delete tata;
    delete z;
    delete ttttttt;
    delete xz;
    delete azezaeazeeze;
    delete zzz;
    delete treze;
    delete braaaa;
    delete tkqiazezz;

    delete nw;
    delete s;
    /*int t = 1, tt = 2, ttt = 3, tttt = 4, ttttt = 5, tttttt = 6, ttttttt = 7,
    tttttttt = 8, ttttttttt = 9;

    SoftHeap<int> *s = new SoftHeap<int>(&ttttttt);
    s->insert(&ttt);
    s->insert(&t);
    s->insert(&tttttt);
    s->insert(&ttttttttt);
    s->insert(&tttttttt);
    s->insert(&ttttt);
    s->insert(&tttt);
    s->insert(&tt);

    std::optional <int*> tmp = s->extract_min();
    while (tmp.value_or(nullptr) != nullptr) {
        std::cout << **tmp << std::endl;
        tmp = s->extract_min();
    }
    delete s;*/
}
