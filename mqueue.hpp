/*
Copyright: Paul Caron
Date: May 22, 2021
https://github.com/paul-caron/mqueue
*/
#ifndef _MQUEUE_HPP_
#define _MQUEUE_HPP_

#include <semaphore.h>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <array>
#include <string>

template<class T, int N>
class MQueue{
    private:
    struct store{
        int size;
        int front;
        int back;
        sem_t * mutex;//not used anymore but here for compaibilty
        std::array <T, N> container; 
    };
    store * state;
    sem_t * mutex;//added this so programs did not attempt to share a pointer to private memory space
    public:
    MQueue(const char * pathname);
    ~MQueue();
    void push(T element);
    T pop();
    bool empty();
    void resetInternals();//added for progrmaic restes if nessarry
};

#include "mqueue.tpp"
#endif

