RTPROG = ../rtprog

DEV_PROG = PK3
PROJECT = testAccelero
BOARD = emz64
OUT_PWD = build 

# CCFLAGS += -pedantic

DRIVERS += sysclock uart i2c timer gpio
MODULES += gui cmdline

FONTS += Lucida_Console10

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
