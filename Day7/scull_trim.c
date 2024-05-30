void scull_trim(struct Scull_Dev *dev) {
    struct Scull_QSet *next, *dptr;
    int qset = dev->qset;   // "dev" là con trỏ tới cấu trúc Scull_Dev
    int i;

    // Bắt đầu cắt giảm
    for (dptr = dev->data; dptr; dptr = next) {
        if (dptr->data) {
            for (i = 0; i < qset; i++)
                kfree(dptr->data[i]);
            kfree(dptr->data);
            dptr->data = NULL;
        }
        next = dptr->next;
        kfree(dptr);
    }
    dev->size = 0;
    dev->quantum = scull_quantum;
    dev->qset = scull_qset;
    dev->data = NULL;
}

