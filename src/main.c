/*======================================================================*/
/* TIMA LABORATORY                                                      */
/*======================================================================*/
#include "encoding.h"
#include "util.h"

#define OSCILLO_BASE 0x82000000

void init_csrs()
{
    write_csr(mie, 0);
    write_csr(sie, 0);
    write_csr(mip, 0);
    write_csr(sip, 0);
    write_csr(mideleg, 0);
    write_csr(medeleg, 0);
}


int main(int argc, char** argv)
{
    init_csrs();

    uint8_t * addr = (uint8_t *)(OSCILLO_BASE);

    // printf("[  -- PROG --  ]  Value at 0x%x = 0x%llx \n", MONITOR_BASE, *addr);

    // int i = 0;
    // for(i =0; i<144*256; i++)
    // {
    //     int pixel = (*(addr + 7 + i)) + 100;
    //     *(addr + 7 + i) = ( pixel > 255 ? 255 : (uint8_t)pixel );
    // }

    *addr = (uint8_t)0x00;

    volatile int j = 100;
    while(j--)
        printf("NONE  --- Hello world @%d \n", j);

    *addr = (uint8_t)0x01;

    j = 100;
    while(j--)
        printf(" IN Only  --- Hello world @%d \n", j);

    *addr = (uint8_t)0x02;

    j = 100;
    while(j--)
        printf(" OUT Only  --- Hello world @%d \n", j);

    *addr = (uint8_t)0x03;

    j = 100;
    while(j--)
        printf(" IN + OUT --- Hello world @%d \n", j);

    *addr = (uint8_t)0x00;

    j = 100;
    while(j--)
        printf("NONE  --- Hello world @%d \n", j);

    return 0;
}
