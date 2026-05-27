CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs

LIB = libvvsfs.a
TARGET = testfs

LIB_OBJS = image.o block.o free.o inode.o mkfs.o
TEST_OBJS = testfs.o

.PHONY: all test clean pristine

all: $(TARGET)

$(TARGET): $(TEST_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(TEST_OBJS) $(LIB)

$(LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(LIB_OBJS)

image.o: image.c image.h
	$(CC) $(CFLAGS) -c image.c

block.o: block.c block.h free.h image.h
	$(CC) $(CFLAGS) -c block.c

free.o: free.c free.h block.h
	$(CC) $(CFLAGS) -c free.c

inode.o: inode.c inode.h block.h free.h
	$(CC) $(CFLAGS) -c inode.c

mkfs.o: mkfs.c mkfs.h block.h free.h
	$(CC) $(CFLAGS) -c mkfs.c

testfs.o: testfs.c image.h block.h free.h inode.h mkfs.h ctest.h
	$(CC) $(CFLAGS) -c testfs.c

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o

pristine: clean
	rm -f $(TARGET) *.a testfs.img