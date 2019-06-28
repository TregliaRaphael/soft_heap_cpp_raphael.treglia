#include "../src/softheap.hh"
#include <vector>
#include <random>

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


void printName(std::string c) {
    printf("\033[1;33m");
    std::cout << c << std::endl;
    printf("\033[0m");
}


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

void test_1_insert_then_delete_x2() {
    printName("test_1_insert_then_delete_x2");
    int t = 1, tt = 2, ttt = 3;

    SoftHeap<int> *s = new SoftHeap<int>(&t);
    s->insert(&tt);
    s->realDelete(&t);
    s->realDelete(&tt);
    s->insert(&ttt);
    printRes(s->first->root->ckey == &ttt);
    delete s;

}

void test_2_using_other_class() {
    printName("test_2_using_other_class");
    auto *tata = new Str("tata"), *z = new Str("z"), *ttttttt = new Str("ttttttt"), *xz = new Str("xz"),
            *azezaeazeeze = new Str("azezaeazeeze"), *zzz = new Str("zzz");

    SoftHeap<Str> *s = new SoftHeap<Str>(tata);
    s->insert(z);
    s->insert(xz);
    s->insert(azezaeazeeze);
    s->insert(zzz);
    s->insert(ttttttt);

    s->realDelete(tata);
    s->realDelete(zzz);
    s->realDelete(xz);
    s->realDelete(ttttttt);


    auto *treze = new Str("treze"), *braaaa = new Str("braaaa"), *tkqiazezz = new Str("tkqiazezz");
    SoftHeap<Str> *nw = new SoftHeap<Str>(treze);
    nw->insert(braaaa);
    nw->insert(tkqiazezz);

    s->meld(nw);

    int cpt = 0;

    std::optional < Str * > tmp = s->extract_min();
    while (tmp.value_or(nullptr) != nullptr) {
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


void test_3_puting_more_int_and_extract_all() {
    printName("test_3_puting_more_int_and_extract_all");
    int t = 1, tt = 2, ttt = 3, tttt = 4, ttttt = 5, tttttt = 6, ttttttt = 7,
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

    int cpt = 0;
    std::optional<int *> tmp = s->extract_min();
    while (tmp.value_or(nullptr) != nullptr) {
        cpt++;
        tmp = s->extract_min();
    }
    delete s;
    printRes(cpt == 9);
}

void test_4_already_deleted() {
    printName("test_4_already_deleted");
    int t = 1, tt = 2;

    SoftHeap<int> *s = new SoftHeap<int>(&t);
    s->insert(&tt);
    s->realDelete(&t);
    s->realDelete(&t);
    printRes(s->first->root->ckey == &tt);
    delete s;
}


void test_5_fake_delete() {
    printName("test_5_fake_delete");
    int t = 1, tt = 2;

    SoftHeap<int> *s = new SoftHeap<int>(&t);
    s->insert(&tt);
    s->fakeDelete(&t);
    s->fakeDelete(&tt);
    s->extract_min();
    printRes(s->first == nullptr);
    delete s;
}


void test_6_merge_all_kind_of_delete() {
    printName("test_6_merge_all_kind_of_delete");
    int t = 1, tt = 2, ttt = 3, tttt = 4, ttttt = 5, tttttt = 6, ttttttt = 7,
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

    s->fakeDelete(&tt);
    s->fakeDelete(&tttt);
    s->realDelete(&tt);
    s->realDelete(&tttt);
    s->realDelete(&tt, true);
    s->realDelete(&tttt, true);
    s->realDelete(&tttttt);
    s->realDelete(&t);
    s->fakeDelete(&tttttttt);

    int cpt = 0;
    std::optional<int *> tmp = s->extract_min();
    while (tmp.value_or(nullptr) != nullptr) {
        cpt++;
        tmp = s->extract_min();
    }
    delete s;
    printRes(cpt == 4);
}


void test_7_ultime_test(int number_of_elem){
    std::vector<int> numbers;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,1000000);

    for (int i = 0; i < number_of_elem; i++){
        numbers.push_back(dist6(rng));
    }
    int first = 1;
    SoftHeap<int> *s = new SoftHeap<int>(&first);

    for (int i = 0; i < number_of_elem; i++){
        s->insert(&numbers[i]);
    }
    for (int i = 0; i < number_of_elem; i++){
        std::cout << **s->extract_min() << std::endl;
    }
    delete s;
}



int main() {
    test_1_insert_then_delete_x2();
    test_2_using_other_class();
    test_3_puting_more_int_and_extract_all();
    test_4_already_deleted();
    test_5_fake_delete();
    test_6_merge_all_kind_of_delete();
    test_7_ultime_test(100000);
}


