#include "block.h"
#include "free.h"

void set_free(unsigned char *block, int num, int set)
{
    int byte_num = num / 8;
    int bit_num = num % 8;

    if (set) {
        block[byte_num] |= (1 << bit_num);
    } else {
        block[byte_num] &= ~(1 << bit_num);
    }
}

int find_free(unsigned char *block)
{
    int byte_num;
    int bit_num;

    for (byte_num = 0; byte_num < BLOCK_SIZE; byte_num++) {
        if (block[byte_num] != 0xff) {
            for (bit_num = 0; bit_num < 8; bit_num++) {
                if (!(block[byte_num] & (1 << bit_num))) {
                    return byte_num * 8 + bit_num;
                }
            }
        }
    }

    return -1;
}