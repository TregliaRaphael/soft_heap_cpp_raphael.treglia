#include <iostream>
#include "softheap.hh"
#include <string>


class Str {
public:
    std::string s;
    Str(std::string _s){
        this->s = _s;
    }

    void operator>(Str& other){
        return this.s.size() > other.s.size();
    }

    void operator<(Str& other){
        return this.s.size() < other.s.size();
    }

    void operator>=(Str& other){
        return this.s.size() >= other.s.size();
    }

    void operator<=(Str& other){
        return this.s.size() <= other.s.size();
    }

    void operator==(Str& other){
        return this.s == other.s;
    }

    void operator!=(Str& other){
        return this.s != other.s;
    }

    void operator=(Str& other){
        return other;
    }
};



int main() {
    auto *tata = new Str("tata"), *z = new Str("z"), *azeaeeza = new Str("azeaeeza"), *xz = new Str("xz"),
            *azezaeazeeze = new Str("azezaeazeeze"), *zzz = new Str("zzz");

    SoftHeap<Str> *s = new SoftHeap<Str>(tata);

    s->insert(z);
    s->insert(azeaeeza);
    s->insert(xz);
    s->insert(azezaeazeeze);
    s->insert(zzz);

    std::cout << "DELETE 6: " << s->fakeDelete(tata) << std::endl;
    std::cout << "DELETE 3: " << s->fakeDelete(zzz) << std::endl;
    std::cout << "DELETE 4: " << s->fakeDelete(xz) << std::endl;
    std::cout << "DELETE 5: " << s->fakeDelete(azeaeeza) << std::endl;


    auto *treze = new Str("treze"), braaaa = new Str("braaaa"), tkqiazezz = new Str("tkqiazezz");
    SoftHeap<Str> *nw = new SoftHeap<Str>(treze);


    nw->insert(braaaa);
    nw->insert(tkqiazezz);

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

    delete tata, z, azeaeeza, xz, azezaeazeeze, zzz, treze, braaaa, tkqiazezz;

    delete nw;
    delete s;
}
