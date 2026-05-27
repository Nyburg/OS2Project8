# Very, Very Simple File System

## Description

This project implements the first stage of a Very, Very Simple File System,
or VVSFS. The file system is simulated using a regular disk image file. The
project currently supports opening and closing the disk image, as well as
reading and writing fixed-size logical blocks.

Each logical block is 4096 bytes.

## Files

- `image.c` and `image.h`: contain functions for opening and closing the disk image.
- `block.c` and `block.h`: contain functions for reading and writing logical blocks.
- `testfs.c`: contains tests for the image and block functionality.
- `ctest.h`: contains simple test macros used by `testfs.c`.
- `Makefile`: builds the static library and test executable.

## Building

To build the project, run:
```sh
make
```
This buildes the object files, creates the static library `libvvsfs.a` and builds the test executable `testfs`

## Testing

To build and run the tests, run: 
```sh
make test
```

## Cleaning

To remove the object files, run: 
`make clean`

To remove the object files, executable, static libraries and the test disk image, run: 
`make pristine`
# OS2Project7
# OS2Project7
# OS2Project8
