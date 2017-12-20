RTPROG = ../rtprog

PROJECT = esp
BOARD = swarmtips2
DRIVERS += uart

# CCFLAGS += -pedantic

### Uncomment module inclusion to use module in RtProg
# MODULES += network
# NETWORK_DRIVERS = esp8266
vpath %.c network/ network/driver/esp8266/
SRC += $(wildcard network/*.c) network/driver/esp8266/esp8266.c
INCLUDEPATH += -Inetwork/driver/esp8266

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
	@echo "SRC asked         :" $(sort $(SRC) $(ARCHI_SRC))
