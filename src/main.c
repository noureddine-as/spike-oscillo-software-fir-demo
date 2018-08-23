/*======================================================================*/
/* TIMA LABORATORY                                                      */
/* Spike with signal and image visual presentation                      */ 
/* noureddine-as                                                        */
/* noureddine.aitsaid0@gmail.com                                        */
/*======================================================================*/
#include "encoding.h"
#include "util.h"
#include "FIR_COEFFS.h"

void init_csrs()
{
    write_csr(mie, 0);
    write_csr(sie, 0);
    write_csr(mip, 0);
    write_csr(sip, 0);
    write_csr(mideleg, 0);
    write_csr(medeleg, 0);
}

#define OSCILLO_BASE 0x82000000

int x_index = 0, i=0;
uint8_t Xn;
uint32_t Yn;
uint8_t XnBuffer[N+1];

int main(int argc, char** argv)
{
    init_csrs();
    for ( i = 0; i < N+1; i++){
        XnBuffer[i] = 0;
    }

    uint8_t *base = (uint8_t *)(OSCILLO_BASE);
    uint8_t *pt_app_status = base;
    uint8_t *pt_spike_status = base+1;

    uint16_t *pt_in_n_rows = (uint16_t *)(OSCILLO_BASE +2);
    uint8_t *pt_in_data = base+4;

    uint16_t *pt_out_n_rows = (uint16_t *)(base + 4 + *(pt_in_n_rows));
    uint16_t *pt_out_data = (uint16_t *)(base + 4 + *(pt_in_n_rows) + 2) ;

    // Deactivate Output for the moment
    *pt_app_status = (uint8_t)0x03; // Activate  OUTPUT + INPUT 

    // printf("[BAREMETAL - INFO] ------------------------------------\n"
    //        "[BAREMETAL - INFO] >> At 0x%x = 0x%lx \n", base, *base);
    // printf("[BAREMETAL - INFO] app_status   = 0x%x \n", *pt_app_status);
    // printf("[BAREMETAL - INFO] spike_status = 0x%x \n", *pt_spike_status);
    // printf("[BAREMETAL - INFO / INPUT] ------------------------------------\n");
    // printf("[BAREMETAL - INFO / INPUT] in_n_rows       = %d \n", *pt_in_n_rows);
    // printf("[BAREMETAL - INFO / INPUT] in_data[0]      = 0x%x \n", *pt_in_data);
    // printf("[BAREMETAL - INFO / OUTPUT] ------------------------------------\n");
    // printf("[BAREMETAL - INFO / OUTPUT] out_n_rows       = %d \n", *pt_out_n_rows);
    // printf("[BAREMETAL - INFO / OUTPUT] out_data[0]      = 0x%x \n", *pt_out_data);

    volatile int i, j;
    for(i = 0; i< *(pt_in_n_rows); i++)
    {
        Yn = 0;
        XnBuffer[0] = *(pt_in_data + i);
        uint64_t t_0 = rdcycle();

        //printf("input[ %d ] = 0x%x \n", i, *(pt_in_data + i));
        for ( j = N-1; j >=0 ; j-- ){
            Yn = (uint32_t)(Yn + ((uint32_t)h[j] * (uint32_t)XnBuffer[j]));
            XnBuffer[j+1] = XnBuffer[j];
            // N+1 -> N   poubelle
        }

        t_0 = rdcycle() - t_0;
        printf("cycles [ %d ] = %d \n", i, t_0);

        // Output on 8 bits
        *(pt_out_data + i) = (Yn >> 12) & 0xFF;
        printf("Result  [ %d ] = 0x%x \n", i, (Yn >> 12) & 0xFF);
    }

    volatile int k = 1000;
    while(k--);

    return 0;
}
