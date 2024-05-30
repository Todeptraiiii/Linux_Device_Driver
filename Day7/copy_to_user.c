ssize_t scull_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
    Scull_Dev *dev = filp->private_data; // Lấy thông tin thiết bị
    struct Scull_QSet *dptr; // Chỉ tới bộ đệm hiện tại
    int quantum = dev->quantum, qset = dev->qset;
    int itemsize = quantum * qset; // Kích thước của một mục
    int item, s_pos, q_pos, rest;
    ssize_t retval = 0;

    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;

    if (*f_pos >= dev->size)
        goto out;
    if (*f_pos + count > dev->size)
        count = dev->size - *f_pos;

    item = (long)*f_pos / itemsize;
    rest = (long)*f_pos % itemsize;
    s_pos = rest / quantum; q_pos = rest % quantum;

    dptr = scull_follow(dev, item);

    if (dptr == NULL || !dptr->data || !dptr->data[s_pos])
        goto out;

    if (count > quantum - q_pos)
        count = quantum - q_pos;

    if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
        retval = -EFAULT;
        goto out;
    }
    *f_pos += count;
    retval = count;

out:
    up(&dev->sem);
    return retval;
}

