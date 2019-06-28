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
        printf("SUCCESS\n");
        printf("\033[0m");
    }
}

void test_1_insert_then_delete_x2(){
    int t = 1, tt = 2, ttt = 3;

    SoftHeap<int> *s = new SoftHeap<int>(&t);
    s->insert(&tt);
    s->realDelete(&t);
    s->realDelete(&tt);
    s->insert(&ttt);
    printRes(s->first->root->ckey == &ttt);
    delete s;

}

void test_2_using_other_class(){
    auto *tata = new Str("tata"), *z = new Str("z"), *ttttttt = new Str("ttttttt"), *xz = new Str("xz"),
            *azezaeazeeze = new Str("azezaeazeeze"), *zzz = new Str("zzz");

    SoftHeap <Str> *s = new SoftHeap<Str>(tata);
    s->insert(z);
    s->insert(xz);
    s->insert(azezaeazeeze);
    s->insert(zzz);
    s->insert(ttttttt);

    std::cout << "DELETE tata: " << s->realDelete(tata) << std::endl;
    std::cout << "DELETE zzz: " << s->realDelete(zzz) << std::endl;
    std::cout << "DELETE xz: " << s->realDelete(xz) << std::endl;
    std::cout << "DELETE ttttttt: " << s->realDelete(ttttttt) << std::endl;


    auto *treze = new Str("treze"), *braaaa = new Str("braaaa"), *tkqiazezz = new Str("tkqiazezz");
    SoftHeap <Str> *nw = new SoftHeap<Str>(treze);
    nw->insert(braaaa);
    nw->insert(tkqiazezz);

    s->meld(nw);

    int cpt = 0;

    std::optional < Str * > tmp = s->extract_min();
    while (tmp.value_or(nullptr) != nullptr) {
        std::cout << (*tmp)->s << std::endl;
        cpt++;
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

    printRes(cpt == 5);
}


int main() {
    test_1_insert_then_delete_x2();
    test_2_using_other_class();

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


