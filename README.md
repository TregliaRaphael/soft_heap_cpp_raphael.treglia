#### SOFT HEAP Project C++ project

### Soft Heap variante from kaplan choosen => BTree implem

## new SoftHeap<E>(e) => create soft heap with one element

## Insert(E e) => takes an element of any kind of type and insert it inside the soft heap

## Meld(SoftHeap<E> *s) => takes an soft heap and merged it inside the soft heap

## Extract_min() => return the minimal element that is not tagged deleted

## FakeDelete(E e) => lazy manner deleted, it just marks the element as deleted and on the next extract_min
While we are getting an element with the deleted tag, we extract again until get a not tagged deleted element

## RealDelete(E e) => Reald delete means that the element is deleted for real in the heap and the value in the list doesn't exists anymore

# Need to do tests with always the sames values but not in the same order and not all time one by on
