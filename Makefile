ACM0_DIR = /dev/ttyACM0
USB0_DIR = /dev/ttyUSB0

acm0_test = $(shell if [ -e $(ACM0_DIR) ]; then echo "exist"; else echo "noexist"; fi)
usb0_test = $(shell if [ -e $(USB0_DIR) ]; then echo "exist"; else echo "noexist"; fi)

upload:gtr_vl53l3cx
ifeq ("$(acm0_test)", "exist")
	idf.py -p /dev/ttyACM0 flash
endif

ifeq ("$(usb0_test)", "exist")
	idf.py -p /dev/ttyUSB0 flash
endif

gtr_vl53l3cx:
	idf.py build

clean_rc:
	idf.py clean

fullclean:
	@rm -rf ./.vscode
	rm -rf ./build

monitor_rc:
ifeq ("$(acm0_test)", "exist")
	idf.py -p /dev/ttyACM0 monitor
endif

ifeq ("$(usb0_test)", "exist")
	idf.py -p /dev/ttyUSB0 monitor
endif

menuconfig:
	idf.py menuconfig

PROJECT_NAME := vl53l3cx

# include $(IDF_PATH)/make/project.mk
