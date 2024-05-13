#include <linux/ioport.h>

// Define a resource structure for I/O port range
struct resource ioport_resource = {
    .name = "PCI IO",
    .start = 0x0000,
    .end = IO_SPACE_LIMIT,
    .flags = IORESOURCE_IO,
    .parent = NULL,
    .sibling = NULL,
    .child = NULL
};

// Create a subrange of the ioport_resource
struct resource *subrange = allocate_resource(&ioport_resource, 0x0100, 0x0200, 0, 0, NULL);

// Check if allocation was successful
if (subrange) {
    // Resource allocated successfully, mark it as busy
    request_resource(&ioport_resource, subrange);
} else {
    // Allocation failed
    printk("Failed to allocate subrange\n");
}

