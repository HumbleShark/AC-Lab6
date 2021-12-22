ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m   := hello2.o
ccflags-y += -g
else
# normal makefile
KDIR ?= /lib/modules/4.19.220/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello2.ko hello2.ko.unstripped
	$(CROSS_COMPILE)strip -g hello2.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
