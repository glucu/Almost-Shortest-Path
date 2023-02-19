#ifndef ALMOSTSHORTESTPATH_MINHEAP_HPP
#define ALMOSTSHORTESTPATH_MINHEAP_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ostream>

template <typename T>
class MinHeap;

template <typename T>
class HeapNode {
public:
    HeapNode() = default;
    HeapNode(T item, int value)
            : m_item{item}, m_value{value} { }
private:
    T m_item;

    int m_value{};

    friend class MinHeap<T>;
};

template <typename T>
class MinHeap {
public:
    MinHeap() = delete;
    explicit MinHeap(int N)
            : m_size{0} {
        m_heap.resize(N + 1);
    }

    [[nodiscard]] bool empty() const
    { return m_size == 0; }

    void heapify_up(int index);
    void heapify_down(int index);
    void insert(T item, int value);
    T find_min();
    void delete_by_index(int index);
    T extract_min();
    void delete_by_item(T item);
    void change_by_key(T item, T new_value);

    void print() const {
        for (int i{1}; i <= m_size; ++i) {
            std::cout << m_heap[i].m_item << ' ';
        }
    }

private:
    std::vector<HeapNode<T>> m_heap;
    std::unordered_map<T, int> m_position;
    int m_size;
};

// MEMBER FUNCTION DEFINITIONS
template <typename T>
void MinHeap<T>::heapify_up(int index) {
    auto parent{ index / 2 };
    while(index > 1 && m_heap[parent].m_item > m_heap[index].m_item) {
        std::swap(m_heap[parent], m_heap[index]);
        m_position[m_heap[parent].m_item] = parent;
        m_position[m_heap[index].m_item] = index;
        index = parent;
        parent = index / 2;
    }
}

template <typename T>
void MinHeap<T>::heapify_down(int index) {
    while(2 * index <= m_size) {

        auto left_child{ 2 * index };
        if(left_child < m_size && m_heap[left_child].m_item > m_heap[left_child + 1].m_item) {
            ++left_child;
        }
        if(m_heap[index].m_item <= m_heap[left_child].m_item) break;
        std::swap(m_heap[index].m_item, m_heap[left_child].m_item);
        m_position[m_heap[left_child].m_item] = left_child;
        m_position[m_heap[index].m_item] = index;
        index = left_child;
    }
}

template <typename T>
void MinHeap<T>::insert(T item, int value) {
    m_size++;
    m_heap[m_size] = HeapNode<T>{item, value};
    m_position[item] = m_size;
    heapify_up(m_size);
}

template <typename T>
T MinHeap<T>::find_min() {
    return m_heap[1].m_item;
}

template <typename T>
void MinHeap<T>::delete_by_index(int index) {
    if(index > m_size) return;

    m_heap[index] = m_heap[m_size];
    m_position[m_heap[m_size].m_value] = index;
    m_size--;
    heapify_down(index);
}

template <typename T>
T MinHeap<T>::extract_min() {
    auto item{ m_heap[1].m_item };
    delete_by_index(1);
    return item;
}

template <typename T>
void MinHeap<T>::delete_by_item(T item) {
    auto index{ m_position[item] };
    delete_by_index(index);
    m_position.erase(item);
}

template <typename T>
void MinHeap<T>::change_by_key(T item, T new_value) {
    auto index{ m_position[item] };
    m_heap[index].m_item = new_value;
    if(index > 1 && m_heap[index].m_item < m_heap[index / 2].m_item) {
        heapify_up(index);
    }
    else {
        heapify_down(index);
    }
}

#endif //ALMOSTSHORTESTPATH_MINHEAP_HPP
