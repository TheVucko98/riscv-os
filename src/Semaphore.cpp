#include "../h/Semaphore.hpp"

#include "../h/MemoryAllocator.hpp"

void* _sem::operator new(size_t size)
{
    return MemoryAllocator::getInstance().alloc(size);
}

void _sem::operator delete(void* ptr)
{
    MemoryAllocator::getInstance().free(ptr);
}

_sem::_sem(unsigned init): val(init)
{
}

_sem::~_sem()
{
}