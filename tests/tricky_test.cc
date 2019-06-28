#include "../src/softheap.hh"

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


void printRes(bool success) {
    if (!success) {
        printf("\033[1;31m");
        printf("FAIL\n");
        printf("\033[0m");
    } else {
        printf("\033[1;32m");
        printf("SUCESS\n");
        printf("\033[0m");
    }
}

void test_1_insert_then_delete_x2(){
    int t = 1, tt = 2;

    SoftHeap<int> *s = new SoftHeap<int>(&t);
    s->insert(&tt);
    s->realDelete(&t);
    s->realDelete(&tt);
    s->insert(&t);
    delete s;

}


int main() {
    test_1_insert_then_delete_x2();
    /*auto *tata = new Str("tata"), *z = new Str("z"), *ttttttt = new Str("ttttttt"), *xz = new Str("xz"),
            *azezaeazeeze = new Str("azezaeazeeze"), *zzz = new Str("zzz");

    SoftHeap <Str> *s = new SoftHeap<Str>(tata);
    s->insert(z);
    s->insert(xz);
    s->insert(azezaeazeeze);
    s->insert(zzz);
    s->insert(ttttttt);

    std::cout << "DELETE tata: " << s->realDelete(tata, false) << std::endl;
    std::cout << "DELETE zzz: " << s->realDelete(zzz, false) << std::endl;
    std::cout << "DELETE xz: " << s->realDelete(xz, false) << std::endl;
    std::cout << "DELETE ttttttt: " << s->realDelete(ttttttt, false) << std::endl;


    auto *treze = new Str("treze"), *braaaa = new Str("braaaa"), *tkqiazezz = new Str("tkqiazezz");
    SoftHeap <Str> *nw = new SoftHeap<Str>(treze);
    nw->insert(braaaa);
    nw->insert(tkqiazezz);

    s->meld(nw);

    std::optional < Str * > tmp = s->extract_min();
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
    delete s;*/

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


