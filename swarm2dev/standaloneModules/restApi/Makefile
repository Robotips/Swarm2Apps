RTPROG = ../../../../rtprog

DEV_PROG = PK3
PROJECT = restApi
BOARD = swarmtips2
OUT_PWD = build

# CCFLAGS += -pedantic

DDRIVERS += uart i2c timer pwm adc gpio # usb_hal

MODULES += network
NETWORK_DRIVERS = esp8266

MODULES += gui
GUI_DRIVERS = ssd1306
FONTS += Lucida_Console10

MODULES += sensor
SENSOR_DRIVERS = VL6180X

SRC += main.c restApi.c

LDFLAGS_XC += -Wl,--defsym=_min_heap_size=2048 -O1

include $(RTPROG)/rtprog.mk

all : hex
    @echo "SRC asked         :" $(sort $(SRC) $(ARCHI_SRC))
    @echo "DRIVERS implemented   :" $(DRIVERS)
    @echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
    @echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
    @echo OBJECTS: $(OBJECTS)
