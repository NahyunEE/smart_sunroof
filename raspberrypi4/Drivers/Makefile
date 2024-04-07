
obj-m += GlassMotor/GlassMotor.o
obj-m += ShieldMotor/ShieldMotor.o


KDIR := /lib/modules/$(shell uname -r)/build


PWD := $(shell pwd)

G_DEV_FILE := /dev/GlassMotorDriver
S_DEV_FILE := /dev/ShieldMotorDriver


default:

	$(MAKE) -C $(KDIR) M=$(PWD) modules

	@sudo insmod GlassMotor/GlassMotor.ko
	@sudo insmod ShieldMotor/ShieldMotor.ko

	@sudo chmod 666 $(G_DEV_FILE)
	@sudo chmod 666 $(S_DEV_FILE)




clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

	@rm -f GlassMotor/*.ko
	@rm -f ShieldMotor/*.ko

	@sudo rmmod GlassMotor
	@sudo rmmod ShieldMotor
