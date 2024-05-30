# Makefile for compiling kernel module and user program

# Kernel module file name
KERNEL_MODULE := implement 

# Kernel module source file
KERNEL_MODULE_SRC := implement.c

# User program file name
USER_PROGRAM := implement_usr

# User program source file
USER_PROGRAM_SRC := implement_usr.c

# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall

# Kernel source directory
KERNEL_SOURCE := /lib/modules/$(shell uname -r)/build
obj-m += implement.o

all:	$(KERNEL_MODULE) $(USER_PROGRAM)

# Kernel module compilation
$(KERNEL_MODULE):
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) modules

# User program compilation
$(USER_PROGRAM): $(USER_PROGRAM_SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Clean up
clean:
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) clean
	rm -f $(USER_PROGRAM) *.o

.PHONY: all clean

