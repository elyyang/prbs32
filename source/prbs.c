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

//--------------------------------------------------------------------------------------
static uint32_t prbs_dict[34][4] = {
    { 2,   1,  0x80, 0x80}, //0
    { 3,   2,  0x80, 0x80}, //1
    { 4,   2,  0x80, 0x80}, //2
    { 5,   4,  0x80, 0x80}, //3
    { 6,   5,  0x80, 0x80}, //4 PRBS-7
    { 7,   5,     4,    3}, //5 PRBS-8
    { 8,   4,  0x80, 0x80}, //6
    { 9,   6,  0x80, 0x80}, //7
    {10,   8,  0x80, 0x80}, //8
    {11,   5,     3,    0}, //9
    {12,   3,     2,    0}, //10
    {13,   4,     2,    0}, //11
    {14,  13,  0x80, 0x80}, //12 PRBS-15
    {15,  14,    12,    3}, //13 PRBS-16
    {16,  13,  0x80, 0x80}, //14
    {17,  10,  0x80, 0x80}, //15
    {18,   5,     1,    0}, //16 
    {19,  16,  0x80, 0x80}, //17
    {20,  18,  0x80, 0x80}, //18
    {21,  20,  0x80, 0x80}, //19
    {22,  17,  0x80, 0x80}, //20 PRBS-23
    {23,  22,    21,   16}, //21 PRBS-24
    {24,  21,  0x80, 0x80}, //22
    {25,   5,     1,    0}, //23
    {26,   4,     1,    0}, //24
    {27,  24,  0x80, 0x80}, //25
    {28,  26,  0x80, 0x80}, //26
    {29,   5,     3,    0}, //27
    {30,  27,  0x80, 0x80}, //28 PRBS-31
    {31,  21,     1,    0}, //29 PRBS-32
    {32,  19,  0x80, 0x80}, //30
    {33,  26,     1,    0}, //31
    {34,  32,  0x80, 0x80}, //32
    {35,  24,  0x80, 0x80}, //33
};

uint32_t prbs_next(const uint32_t bits, const uint32_t seed)
{
    uint32_t *pRow = prbs_dict[bits-3];
    uint32_t a = pRow[0];
    uint32_t b = pRow[1];
    uint32_t c = pRow[2];
    uint32_t d = pRow[3];
    uint32_t mask = (1UL << bits) - 1;

    return( ((seed << 1) | (((seed >> a) ^
                             (seed >> b) ^
                             (seed >> c) ^
                             (seed >> d)) & 1 )) & mask);
}

void prbs_fill(uint32_t* addr, uint32_t bits, uint32_t num, uint32_t seed)
{
    for (uint32_t i=0; i<num; i++)
    {
        addr[i] = seed;        
        seed = prbs_next(bits, seed);
    }
}

bool prbs_check(uint32_t* addr, uint32_t bits, uint32_t num, uint32_t seed)
{
    for (uint32_t i=0; i<num; i++)
    {
        if(addr[i] != seed)
        {
            return false;
        }
    }
    seed = prbs_next(bits, seed);    
    return true;
}

//--------------------------------------------------------------------------------------

void prbs8_writeFile(char* filename, uint32_t num, uint8_t seed)
{    
    FILE *fp;
    fp = fopen(filename, "w" );
    
    for(uint32_t i=0; i<num; i++)
    {       
        fputc(seed, fp);
        seed = prbs_next(8, seed);        
    }
    fclose(fp);
}

void prbs32_writeFile(char* filename, uint32_t num, uint32_t seed)
{    
    FILE *fp;
    fp = fopen(filename, "w" );
    
    for(uint32_t i=0; i<num; i++)
    {   
        //size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
        fwrite(&seed, sizeof(uint8_t), sizeof(uint32_t), fp);
        seed = prbs_next(32, seed);        
    }
    fclose(fp);
}

//--------------------------------------------------------------------------------------

void prbs7_period(uint8_t start)
{    
    uint8_t a = start;
    uint8_t mask = 0x7F;

    for (uint32_t i = 1;; i++) 
    {
        a = ((a << 1) | (((a >> 6) ^ (a >> 5)) & 1)) & mask;

        //printf("%x\n", a);
        
        if (a == start) 
        {
            printf("prbs-7 repetition period: %d\n", i);
            break;
        }
    }
}

void prbs8_period(uint8_t start)
{    
    uint8_t a = start;
    uint8_t mask = 0xFF;

    for (uint32_t i = 1;; i++) 
    {        
        a = ((a << 1) | ((  (a >> 7) ^ 
                            (a >> 5) ^
                            (a >> 4) ^
                            (a >> 3)                            
                            ) & 1) ) & mask;

        printf("0x%x\n", a);
        
        if (a == start) 
        {
            printf("prbs-8 repetition period: %d\n", i);
            break;
        }
    }
}

void prbs15_period(uint16_t start)
{    
    uint16_t a = start;
    uint16_t mask = 0x7FFF;

    for (uint32_t i = 1;; i++) 
    {
        uint8_t next = (((a >> 14) ^ (a >> 13)) & 1);
        a = ((a << 1) | next) & mask;
        
        printf("%x\n", a);
        
        if (a == start) 
        {
            printf("prbs-15 repetition period: %d\n", i);
            break;
        }
    }    
}

void prbs16_period(uint16_t start)
{    
    uint16_t a = start;
    uint16_t mask = 0xFFFF;

    for (uint32_t i = 1;; i++) 
    {
        a = ((a << 1) | ((  (a >> 15) ^ 
                            (a >> 14) ^
                            (a >> 12) ^
                            (a >> 3)                            
                            ) & 1) ) & mask;
        
        printf("0x%.4X\n", a);
        
        if (a == start) 
        {
            printf("prbs-16 repetition period: %d\n", i);
            break;
        }
    }    
}

void prbs24_period(uint16_t start)
{    
    uint32_t a = start;
    uint32_t mask = 0xFFFFFF;

    for (uint32_t i = 1;; i++) 
    {
        a = ((a << 1) | ((  (a >> 23) ^ 
                            (a >> 22) ^
                            (a >> 21) ^
                            (a >> 16)                            
                            ) & 1) ) & mask;
        
        printf("0x%.4X\n", a);
        
        if (a == start) 
        {
            printf("prbs-24 repetition period: %d\n", i);
            break;
        }
    }    
}

void prbs32_period(uint32_t start)
{    
    uint32_t a = start;
    uint32_t mask = 0xFFFFFFFF;

    for (uint64_t i = 1;; i++) 
    {
        a = ((a << 1) | ((  (a >> 31) ^ 
                            (a >> 21) ^
                            (a >> 1)  ^
                            (a >> 0)                            
                            ) & 1) ) & mask;
        
        printf("0x%.4X\n", a);
        
        if (a == start) 
        {
            printf("prbs-32 repetition period: %ld\n", i);
            break;
        }
    }    
}


