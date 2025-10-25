#ifndef _SEMAPHORE_HPP
#define _SEMAPHORE_HPP

#include "../lib/hw.h"
#include "syscall_c.h"


class _sem
{
public:
    _sem(unsigned init = 1);
    ~_sem();

    int val;
    _thread* waiting = nullptr;
    void* operator new(size_t size);
    void operator delete(void* ptr);
};

#endif // _SEMAPHORE_HPP