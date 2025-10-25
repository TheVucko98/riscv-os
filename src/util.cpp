#include "../lib/hw.h"

// compiler gives error if i dont implement my own memset
extern "C" void* memset(void* str, int c, size_t n)
{
    uint8 c8 = c;
    uint8* str8 = (uint8*)str;
    while (n > 0)
    {
        *str8 = c8;
        str8++;
        n--;
    }

    return str;
}