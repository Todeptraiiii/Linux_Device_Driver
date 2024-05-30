# SPDX-License-Identifier: BSD-2-Clause-Views

ifneq ($(KERNELRELEASE),)

# object files to build
obj-m += debug.o

ifneq ($(DEBUG),)
ccflags-y += -DDEBUG
endif

else

ifneq ($(KERNEL_SRC),)
# alternatively to variable KDIR accept variable KERNEL_SRC as used in
# PetaLinux/Yocto for example
KDIR ?= $(KERNEL_SRC)
endif

KDIR ?= /lib/modules/$(shell uname -r)/build

all: modules

help modules modules_install clean:
	$(MAKE) -C $(KDIR) M=$(shell pwd) $@

install: modules_install
	depmod -a $(shell uname -r)

uninstall:
	rm /lib/modules/$(shell uname -r)/extra/debug.ko
	depmod -a $(shell uname -r)

endif
