#include <vector>

/**This funciton test is not accurate at all but
 * she is just there to show how soft heap can be sorted
 * approximately sometimes
 * @tparam E
 */


template<typename E>
int evaluate_percent_of_sorted_element(std::vector<E> list){

    int counter_unsorted_element = 0;
    int size = list.size();

    for (int i = 0; i < size - 1; i++){
        if (*list[i] > *list[i + 1])
            counter_unsorted_element++;
    }

     return counter_unsorted_element * 100 / size;
}