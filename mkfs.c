#include "block.h"
#include "free.h"
#include "mkfs.h"

#include <string.h>

void mkfs(void)
{
    unsigned char block[BLOCK_SIZE];

    memset(block, 0, BLOCK_SIZE);

    bwrite(0, block);
    bwrite(1, block);
    bwrite(3, block);
    bwrite(4, block);
    bwrite(5, block);
    bwrite(6, block);

    memset(block, 0, BLOCK_SIZE);
    set_free(block, 0, 1);
    set_free(block, 1, 1);
    set_free(block, 2, 1);
    set_free(block, 3, 1);
    set_free(block, 4, 1);
    set_free(block, 5, 1);
    set_free(block, 6, 1);

    bwrite(2, block);
}