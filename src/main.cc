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
};



int main() {
    auto *ma = new Str("tata");
    SoftHeap<Str> *s = new SoftHeap<Str>(ma);
    s->insert("z");
    s->insert("azeaeeza");
    s->insert("xz");
    s->insert("azezaeazeeze");
    s->insert("zzz");

    auto *s1 = new Str("tata");
    auto *s2 = new Str("zzz");
    auto *s3 = new Str("xz");
    auto *s4 = new Str("azeaeeza");

    std::cout << "DELETE 6: " << s->fakeDelete(s1) << std::endl;
    std::cout << "DELETE 3: " << s->fakeDelete(s2) << std::endl;
    std::cout << "DELETE 4: " << s->fakeDelete(s3) << std::endl;
    std::cout << "DELETE 5: " << s->fakeDelete(s4) << std::endl;



    SoftHeap<Str> *nw = new SoftHeap<int>(2);
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
