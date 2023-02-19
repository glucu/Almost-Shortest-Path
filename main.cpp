#include "MinHeap.hpp"

#include <iostream>

int main() {

    MinHeap<int> heap1{14};

    for(int i{1}; i <= 14; ++i) {
        int item{};
        std::cin >> item;
        heap1.insert(item, i);
    }

    heap1.print(); std::cout << '\n';

    while(!heap1.empty()) {
        std::cout << heap1.find_min() << ' ';
        heap1.delete_by_index(1);
    }
    std::cout << "\n\n";

    MinHeap<int> heap2{7};

    heap2.insert(5, 1);
    heap2.insert(1, 2);
    heap2.insert(10, 3);
    heap2.insert(30, 4);
    heap2.insert(20, 5);
    heap2.insert(40, 6);
    heap2.insert(50, 7);

    std::cout << "print: ";
    heap2.print(); std::cout << '\n';
    std::cout << "find_min: " << heap2.find_min() << '\n';
    std::cout << "delete_by_index(1)...\n";
    heap2.delete_by_index(1);
    std::cout << "print: ";
    heap2.print(); std::cout << '\n';
    std::cout << "find_min: " << heap2.find_min() << '\n';

    std::cout << "change_by_key(5,25)...\n";
    heap2.change_by_key(5, 25);
    std::cout << "find_min: " << heap2.find_min() << '\n';
    heap2.print();
    return 0;
}

/*
 *
 *                     1
 *                 5       10
 *             30    20   40    50
 *
 *
 *                      5
 *                  20      10
 *                30  50    40
 *
 *
 *                     10
 *                   20      25
 *                 30   50   40
 *
 */