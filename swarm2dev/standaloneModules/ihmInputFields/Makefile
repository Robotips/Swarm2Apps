RTPROG = ../../../../rtprog

DEV_PROG = PK3
PROJECT = ihmInputFields
BOARD = emz64
OUT_PWD = build 

# CCFLAGS += -pedantic

DRIVERS += sysclock uart i2c timer
MODULES += gui

MODULES += cmdline
FONTS += Lucida_Console10

SRC += main.c inputField.c utilities.c

LDFLAGS_XC += -Wl,--defsym=_min_heap_size=2048 -O1

include $(RTPROG)/rtprog.mk

all : hex
	@echo "SRC asked         :" $(sort $(SRC) $(ARCHI_SRC))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
