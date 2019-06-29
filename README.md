# SOFT HEAP Project C++ project

## Soft Heap variante from kaplan choosen => BTree implem

#### new SoftHeap<E>(e) => create soft heap with one element

#### Insert(E e) => takes an element of any kind of type and insert it inside the soft heap

#### Meld(SoftHeap<E> *s) => takes an soft heap and merged it inside the soft heap

#### Extract_min() => return the minimal element that is not tagged deleted

### DELETE => you can use both delete in the same time to be able to manage memory as you wish

#### FakeDelete(E e) 
=> lazy manner deleted, it just marks the element as deleted and on the next extract_min
While we are getting an element with the deleted tag, we extract again until get a not tagged deleted element

#### RealDelete(E e, bool force_delete) 
=> Reald delete means that the element is deleted for real in the heap and the value in the list doesn't exists anymore


You can mix both of these fonction => if you fakeDelete, then you can even realDelete
Moreover, you can precise in realDelete if you want to delete an element tagged deleted or not.

force_delete = true => delete even deleted tagged element

force_delete = false => delete only untagged deleted element

can cause invalid read of size if you don't allocate your memory

don't forget to extend the stack when using valgrind => --main-stacksize=number

#### Need to do tests with always the sames values but not in the same order and not all time one by on

## What about tests (Makefile):

#### Some constructors tested => make test

#### Some basics uses of fonctions => make test_soft

#### Some tricky tests using valgrind => make tricky_test

#### Test vs std::sort => make time_test
The error rate of the algo is also displayed while testing because it's not fair for std::sort if we compare
only the time.

As you'll be able to see, epsilon affect on the number of element you can put without getting any error of sort.
Then if you know the number of elements to sort and that the %error that you can incur (if you accept any error rate),
then this algo is yours.
Otherwise, you can go away.


