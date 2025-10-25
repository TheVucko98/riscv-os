#ifndef _THREAD_HPP
#define _THREAD_HPP

#include "../lib/hw.h"

class _thread {
    public:
        static _thread* running;
        static size_t time;
        _thread(void (*start_routine)(void*), void* arg, void* stack);
        _thread();
        ~_thread();
        _thread(const _thread&) = delete;
        _thread& operator=(const _thread&) = delete;

        static void dispatch();

        void join();

        // za ulancavanje niti u listama cekanja
        _thread* next = nullptr;
        // lista cekanja na ovu nit
        _thread* waiting = nullptr;

        void* stack = nullptr;

        size_t sleeping_time = 0;
        bool ready = true;
        bool interrupted = false;
        bool finished = false;

        const size_t id = next_id++;

        struct Context
        {
            uint64 ra;
            uint64 sp;
        };

        void (*start_routine)(void*) = nullptr;
        void* arg = nullptr;
        void* operator new(size_t size);
        void operator delete(void* ptr);
    private:

        
        Context context;

        static void contextSwitch(Context *oldContext, Context *runningContext);
        
        static void execWrapper();

        static size_t next_id;

};

#endif // _THREAD_HPP