#include "../h/syscall_c.h"


// https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html

void* mem_alloc(size_t size)
{
    register void* ret asm("a0");
    register size_t s asm("a1") = (size + MEM_BLOCK_SIZE - 1)/ MEM_BLOCK_SIZE;
    register int id asm("a0") = MEM_ALLOC;

    asm volatile ("ecall" : "=r"(ret) : "r"(s), "r"(id) : "memory");

    return ret;
}

int mem_free(void* ptr)
{
    register int ret asm("a0");
    register void* p asm("a1") = ptr;
    register int id asm("a0") = MEM_FREE;

    asm volatile ("ecall" : "=r"(ret) : "r"(p), "r"(id) : "memory");

    return ret;
}

int thread_create(thread_t* handle, void(*start_routine)(void*), void* arg)
{
    register void* stack asm("a4") = mem_alloc(DEFAULT_STACK_SIZE);
    register int ret asm("a0");
    register thread_t* h asm("a1") = handle;
    register void(*sr)(void*) asm("a2") = start_routine;
    register void* a asm("a3") = arg;
    register int id asm("a0") = THREAD_CREATE;

    asm volatile ("ecall" : "=r"(ret) : "r"(h), "r"(sr), "r"(a), "r"(id), "r"(stack) : "memory");

    return ret;
}

int thread_exit()
{
    register int ret asm("a0");
    register int id asm("a0") = THREAD_EXIT;

    asm volatile ("ecall" : "=r"(ret) : "r"(id) : "memory");

    return ret;
}

void thread_dispatch()
{
    register int id asm("a0") = THREAD_DISPATCH;

    asm volatile ("ecall" : : "r"(id) : "memory");
}

void thread_join(thread_t handle)
{
    register thread_t h asm("a1") = handle;
    register int id asm("a0") = THREAD_JOIN;

    asm volatile ("ecall" : : "r"(h), "r"(id) : "memory");
}

int thread_getID()
{
    register int ret asm("a0");
    register int id asm("a0") = THREAD_GETID;

    asm volatile ("ecall" : "=r"(ret) : "r"(id) : "memory");

    return ret;
}

int sem_open(sem_t* handle, unsigned init)
{
    register int ret asm("a0");
    register sem_t* h asm("a1") = handle;
    register unsigned i asm("a2") = init;
    register int id asm("a0") = SEM_OPEN;

    asm volatile ("ecall" : "=r"(ret) : "r"(h), "r"(i), "r"(id) : "memory");

    return ret;
}

int sem_close(sem_t handle)
{
    register int ret asm("a0");
    register sem_t h asm("a1") = handle;
    register int id asm("a0") = SEM_CLOSE;

    asm volatile ("ecall" : "=r"(ret) : "r"(h), "r"(id) : "memory");

    return ret;
}

int sem_wait(sem_t id)
{
    register int ret asm("a0");
    register sem_t h asm("a1") = id;
    register int i asm("a0") = SEM_WAIT;

    asm volatile ("ecall" : "=r"(ret) : "r"(h), "r"(i) : "memory");

    return ret;
}

int sem_signal(sem_t id)
{
    register int ret asm("a0");
    register sem_t h asm("a1") = id;
    register int i asm("a0") = SEM_SIGNAL;

    asm volatile ("ecall" : "=r"(ret) : "r"(h), "r"(i) : "memory");

    return ret;
}

int time_sleep(time_t time)
{
    register int ret asm("a0");
    register time_t t asm("a1") = time;
    register int id asm("a0") = TIME_SLEEP;

    asm volatile ("ecall" : "=r"(ret) : "r"(t), "r"(id) : "memory");

    return ret;
}

char getc()
{
    register char ret asm("a0");
    register int id asm("a0") = GETC;

    asm volatile ("ecall" : "=r"(ret) : "r"(id) : "memory");

    return ret;
}

void putc(char c)
{
    register char ret asm("a1") = c;
    register int id asm("a0") = PUTC;

    asm volatile ("ecall" : : "r"(ret), "r"(id) : "memory");
}