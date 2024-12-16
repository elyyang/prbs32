/*=====================================================================================

ELY 2023

PRBS Example

RE: https://en.wikipedia.org/wiki/Pseudorandom_binary_sequence

PRBS-7  : x^7 + x^6 + 1
PRBS-10 : x^11 + x^10 + 1
PRBS-15 : x^15 + x^14 + 1
PRBS-23 : x^23 + x^18 + 1
PRBS-31 : x^31 + x^28 + 1
=======================================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "prbs.h"

int main(int argc, char* argv[]) 
{
    const uint32_t bits = 32;
    uint32_t start;
    uint64_t count;
    char* filename;

//FILE *fp;
//fp = fopen("prbs32_reference.txt", "w" );

    if (argc < 3)
    {
        printf("progam expects the following parameters (seed, count, filename) \n");
        return 0;
    }    
    else
    {        
        start = atoi(argv[1]);
        count = atoi(argv[2]);
        filename = argv[3];

        if(start > 0)
        {
            printf("PRBS-%d starting seed: 0x%x count: %ld \n", bits, start, count);
        }
        else
        {
            printf("seed must be non-zero decimal number! \n");
            return 0;
        }        
    }

    if(filename == NULL)
    {
        uint32_t seed = start;
        for(uint32_t i=0; i<count; i++)        
        {        
            uint64_t addr = (sizeof(uint32_t)*i);
            printf("PRBS-%d (index: %8d) seed: 0x%.8X (%10u) \t (address offset: 0x%.8lx)\n", bits, i, seed, seed, addr);

//fprintf(fp,"%.7d \t 0x%.8X \t 0x%.8lx\n", i, seed, addr);

            seed = prbs_next(bits, seed);
        }
    }
    else
    {   
        printf("writing to file: '%s' \n", filename);
        prbs32_writeFile(filename, count, start);        
    }

//fclose(fp);

    return 0;
}
