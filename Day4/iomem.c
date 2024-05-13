#include <linux/ioport.h>
#include <linux/errno.h>

unsigned long mem_addr = 0xC0000000; // Example memory address
unsigned long mem_size = 0x1000;      // Example memory size

// Check if the memory region is already in use
if (check_mem_region(mem_addr, mem_size)) {
    printk("drivername: memory already in use\n");
    return -EBUSY;
}

// Request access to the memory region
if (!request_mem_region(mem_addr, mem_size, "drivername")) {
    printk("drivername: failed to request memory region\n");
    return -EBUSY; // Or appropriate error code
}

// Memory region is now reserved for driver use

