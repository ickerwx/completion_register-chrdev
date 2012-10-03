obj-m += trial_completion-register_chrdev_v2.o

ARCH = arm
CROSS_COMPILE = arm-none-linux-gnueabi-
KSRC = /home/tomxue/Tom/Source_Code/HTC/pyramid-ics-crc-3.0.16-c764bfb

all: modules

modules:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KSRC) M=$(shell pwd) modules

clean:
	rm -rf *.mod.* *.o *.ko *.order *.symvers
