result = register_chrdev(scull_major, "scull", &scull_fops);
if (result < 0) {
    printk(KERN_WARNING "scull: can’t get major %d\n", scull_major);
    return result;
}
if (scull_major == 0) scull_major = result; /* dynamic */

