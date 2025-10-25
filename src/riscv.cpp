#include "../h/riscv.hpp"

void Riscv::popSppSpie()
{
    __asm__ volatile("csrc sstatus, %0" :: "r"(1 << 8));
    __asm__ volatile("csrw sepc, ra");
    // __asm__ volatile("csrr sp, sscratch");
    __asm__ volatile("sret");
}