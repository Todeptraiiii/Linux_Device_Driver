int scull_open(struct inode *inode, struct file *filp) {
    Scull_Dev *dev;   // thông tin thiết bị
    int num = NUM(inode->i_rdev);
    int type = TYPE(inode->i_rdev);

    // Nếu private_data không hợp lệ, không sử dụng devfs
    if (!filp->private_data && type) {
        if (type > SCULL_MAX_TYPE) return -ENODEV;
        filp->f_op = scull_fop_array[type];
        return filp->f_op->open(inode, filp); // chuyển tới open cụ thể
    }

    // type 0, kiểm tra số thiết bị (trừ khi private_data hợp lệ)
    dev = (Scull_Dev *)filp->private_data;
    if (!dev) {
        if (num >= scull_nr_devs) return -ENODEV;
        dev = &scull_devices[num];
        filp->private_data = dev; // cho các phương thức khác
    }

    // Tăng usage count trước khi có thể ngủ
    MOD_INC_USE_COUNT;

    // Cắt giảm độ dài thiết bị xuống 0 nếu open chỉ để ghi
    if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
        if (down_interruptible(&dev->sem)) {
            MOD_DEC_USE_COUNT;
            return -ERESTARTSYS;
        }
        scull_trim(dev); // bỏ qua lỗi
        up(&dev->sem);
    }
    return 0; // thành công
}

