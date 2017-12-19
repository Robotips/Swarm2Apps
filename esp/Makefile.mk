RTPROG = ../../rtprog

PROJECT = esp

# CCFLAGS += -pedantic

MODULES += network
NETWORK_DRIVERS = esp8266

FONTS += Lucida_Console10

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
	@echo "SRC asked         :" $(sort $(SRC) $(ARCHI_SRC))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
@echo OBJECTS: $(OBJECTS)