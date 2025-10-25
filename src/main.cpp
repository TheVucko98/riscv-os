#include "../h/printing.hpp"
#include "../h/riscv.hpp"
#include "../h/Thread.hpp"
#include "../h/syscall_cpp.hpp"
#include "../h/Scheduler.hpp"

extern "C" void traps(uint64 syscall_id ...);

extern void userMain();

extern void testMain();

void idle(void* arg)
{
    while (true)
    {
        _printString("Aca!\n");
        thread_dispatch();
    }
}

int main()
{
    // | 1 for Vector Table Pointer way
    Riscv::w_stvec((uint64)traps | 1);

    _thread* main_thread = new _thread();

    _thread::running = main_thread;

    Thread* idleThread = new Thread(idle, nullptr);
    idleThread->start();
    idleThread->join();

    // Thread* userThread = new Thread((void(*)(void*))userMain, nullptr);
    // userThread->start();
    // userThread->join();
    // delete userThread;

    /*Thread* testThread = new Thread((void(*)(void*))testMain, nullptr);
    testThread->start();
    testThread->join();
    delete testThread;*/

    return 0;
}