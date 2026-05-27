#include "block.h"
#include "ctest.h"
#include "free.h"
#include "image.h"
#include "inode.h"
#include "mkfs.h"

#include <string.h>
#include <unistd.h>

#define TEST_IMAGE "testfs.img"

static int test_image_open_close(void)
{
    int fd = image_open(TEST_IMAGE, 1);

    CTEST_ASSERT(fd >= 0);
    CTEST_ASSERT(image_close() == 0);

    unlink(TEST_IMAGE);

    return 0;
}

static int test_block_write_read(void)
{
    unsigned char write_block[BLOCK_SIZE];
    unsigned char read_block[BLOCK_SIZE];
    int i;

    CTEST_ASSERT(image_open(TEST_IMAGE, 1) >= 0);

    for (i = 0; i < BLOCK_SIZE; i++) {
        write_block[i] = (unsigned char)(i % 256);
        read_block[i] = 0;
    }

    bwrite(0, write_block);
    bread(0, read_block);

    CTEST_ASSERT(memcmp(write_block, read_block, BLOCK_SIZE) == 0);
    CTEST_ASSERT(image_close() == 0);

    unlink(TEST_IMAGE);

    return 0;
}

static int test_set_free(void)
{
    unsigned char block[BLOCK_SIZE];

    memset(block, 0, BLOCK_SIZE);

    set_free(block, 0, 1);
    CTEST_ASSERT(block[0] == 1);

    set_free(block, 1, 1);
    CTEST_ASSERT(block[0] == 3);

    set_free(block, 0, 0);
    CTEST_ASSERT(block[0] == 2);

    return 0;
}

static int test_find_free(void)
{
    unsigned char block[BLOCK_SIZE];

    memset(block, 0xff, BLOCK_SIZE);
    block[0] = 0xfe;

    CTEST_ASSERT(find_free(block) == 0);

    block[0] = 0xff;
    block[1] = 0xfd;

    CTEST_ASSERT(find_free(block) == 9);

    return 0;
}

static int test_ialloc(void)
{
    unsigned char block[BLOCK_SIZE];

    CTEST_ASSERT(image_open(TEST_IMAGE, 1) >= 0);

    memset(block, 0, BLOCK_SIZE);
    bwrite(1, block);

    CTEST_ASSERT(ialloc() == 0);
    CTEST_ASSERT(ialloc() == 1);

    bread(1, block);
    CTEST_ASSERT(block[0] == 3);

    CTEST_ASSERT(image_close() == 0);

    unlink(TEST_IMAGE);

    return 0;
}

static int test_alloc(void)
{
    unsigned char block[BLOCK_SIZE];

    CTEST_ASSERT(image_open(TEST_IMAGE, 1) >= 0);

    memset(block, 0, BLOCK_SIZE);
    bwrite(2, block);

    CTEST_ASSERT(alloc() == 0);
    CTEST_ASSERT(alloc() == 1);

    bread(2, block);
    CTEST_ASSERT(block[0] == 3);

    CTEST_ASSERT(image_close() == 0);

    unlink(TEST_IMAGE);

    return 0;
}

static int test_mkfs(void)
{
    unsigned char block[BLOCK_SIZE];

    CTEST_ASSERT(image_open(TEST_IMAGE, 1) >= 0);

    mkfs();

    bread(1, block);
    CTEST_ASSERT(block[0] == 0);

    bread(2, block);
    CTEST_ASSERT(block[0] == 0x7f);

    CTEST_ASSERT(alloc() == 7);

    CTEST_ASSERT(image_close() == 0);

    unlink(TEST_IMAGE);

    return 0;
}

int main(void)
{
    int failures = 0;

    CTEST_RUN(test_image_open_close);
    CTEST_RUN(test_block_write_read);
    CTEST_RUN(test_set_free);
    CTEST_RUN(test_find_free);
    CTEST_RUN(test_ialloc);
    CTEST_RUN(test_alloc);
    CTEST_RUN(test_mkfs);

    if (failures == 0) {
        printf("All tests passed\n");
    }

    return failures;
}