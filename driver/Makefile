# obj-m := hello.o

# all:
# 	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# clean:
# 	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# //@ obj-m -> tell the kernel makefile that the driver needs to be compiled as module
obj-m := hello.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# //@ M=$(PWD) -> indicate in the kernel makefile that source for driver is in present working directory
# //@ modules -> tell kernel makefile just build modules instead of building the complete kernel source code
