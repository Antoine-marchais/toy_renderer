#ifndef NSTACK_H
#define NSTACK_H

#include "string.h"
#include <algorithm>
#include <stdexcept>

template <typename T>
class NStack
{
public:
    NStack();
    NStack(int stack_size);
    NStack(const NStack<T>& stack);
    ~NStack();
    T top(int rank = 0);
    T pop(int rank = 0);
    void push(const T& item, int rank = 0);
    int getNbItems();
private:
    int stack_size;
    int nb_items;
    T *items;
};

template <typename T>
NStack<T>::NStack():stack_size(256), nb_items(0), items(new T[256]){}

template <typename T>
NStack<T>::NStack(int stack_size): stack_size(stack_size), nb_items(0), items(new T[stack_size]){}

template <typename T>
NStack<T>::NStack(const NStack<T>& stack): 
    stack_size(stack.stack_size), 
    nb_items(stack.nb_items), 
    items(new T[stack.stack_size])
{
    memcpy(items, stack.items, sizeof(T)*stack_size);
}

template <typename T>
NStack<T>::~NStack(){
    delete[] items;
}

template <typename T>
T NStack<T>::top(int rank){
    if (rank >= nb_items){
        throw std::invalid_argument("Not enough items in stack for using top a this rank");
    }
    return items[nb_items-(1+rank)];
}

template <typename T>
T NStack<T>::pop(int rank){
    if (rank >= nb_items){
        throw std::invalid_argument("Not enough items in stack to pop element");
    }
    else if (rank == 0){
        nb_items--;
        return items[nb_items];
    }
    else {
        int position_in_stack = nb_items-rank-1;
        T result = items[nb_items-(1+rank)];
        T *holding_buffer;
        holding_buffer = new T[rank];
        memcpy(holding_buffer, items+position_in_stack+1, rank);
        memcpy(items+position_in_stack, holding_buffer, rank);
        delete[] holding_buffer;
        nb_items--;
        return result;
    }
}

template <typename T>
void NStack<T>::push(const T& item, int rank){
    if (stack_size == nb_items){
        throw std::invalid_argument("stack is already full");
    }
    else if (rank == 0){
        items[nb_items] = item;
        nb_items++;
    }
    else {
        int position_in_stack = nb_items-rank;
        T *holding_buffer;
        holding_buffer = new T[rank];
        memcpy(holding_buffer, items+position_in_stack, rank);
        memcpy(items+position_in_stack+1, holding_buffer, rank);
        delete[] holding_buffer;
        items[position_in_stack] = item;
        nb_items++;
    }
}

#endif

