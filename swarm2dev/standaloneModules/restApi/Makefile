RTPROG = ../../../rtprog

DEV_PROG = PK3
PROJECT = restApi
BOARD = swarmtips2
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += uart i2c timer pwm adc gpio # usb_hal

### Uncomment module inclusion to use module in RtProg
#MODULES += network
#NETWORK_DRIVERS = esp8266

##Uncomment inclusion esp project
vpath %.c ../../../esp/network/ ../../../esp/network/driver/esp8266/
INCLUDEPATH += -I../../../esp/network/driver/esp8266/
SRC += $(wildcard ../../../esp/network/*.c) 
SRC += ../../../esp/network/driver/esp8266/esp8266.c




# MODULES += gui
# GUI_DRIVERS = ssd1306
# FONTS += Lucida_Console10

MODULES += sensor
SENSOR_DRIVERS += lsm6ds3 VL6180X 

#MODULES += mrobot



SRC += main.c restApi.c motors.c

LDFLAGS_XC += -Wl,--defsym=_min_heap_size=2048 -O1

include $(RTPROG)/rtprog.mk

all : hex
    @echo "SRC asked         :" $(sort $(SRC) $(ARCHI_SRC))
    @echo "DRIVERS implemented   :" $(DRIVERS)
    @echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
    @echo OBJECTS: $(OBJECTS)
