#include "../src/softheap.hh"
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

std::string base_green = "\033[1;32m";
std::string base_other = "\033[1;33m";
std::string base_end = "\033[0m";

void std_sort_ref(std::vector<int> numbers){

    std::cout << base_other << "std::sort reference" << base_end << std::endl;

    clock_t tStart = clock();

    std::sort(numbers.begin(), numbers.end());

    clock_t tEnd = clock();

    std::cout << "Timeout : " << base_green<< (double)(tEnd - tStart)/CLOCKS_PER_SEC << base_end;
    std::cout << std::endl << std::endl;
}


void fast_test(std::vector<int*> numbers, int number_of_elem, double epsi){
    std::cout << base_other << "Fast test epsilon : " << epsi << base_end << std::endl;

    auto s = new SoftHeap<int>();

    s->epsilon = epsi;
    s->max_node_rank = std::ceil(log2(1. / s->epsilon)) + 5;
	
    clock_t tStart = clock();

    for (int i = 0; i < number_of_elem; i++){
        s->insert(numbers[i]);
    }

    clock_t tEnd = clock();

    std::cout << "Timeout : " << base_green << (double)(tEnd - tStart)/CLOCKS_PER_SEC << base_end;
    std::cout << std::endl << std::endl;

    delete s;
}


int main() {
    std::cout << std::endl;

    std::vector<int*> for_test;
    std::vector<int> for_ref;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,1000000000);

    int number_of_element = 10000000;

    for (int i = 0; i < number_of_element; i++){
        for_ref.push_back((int)dist6(rng));
    }

    std_sort_ref(for_ref);

    for (int i = 0; i < number_of_element; i++){
        for_test.push_back(new int(dist6(rng)));
    }

    for (double i = 0.1; i < 1; i += 0.1)
        fast_test(for_test, number_of_element, i);


    for (int i = 0; i < number_of_element; i++){
        delete for_test[i];
    }
}
