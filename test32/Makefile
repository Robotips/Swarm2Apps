RTPROG = ../rtprog

DEV_PROG = PK3
PROJECT = test32
BOARD = emz64
OUT_PWD = build 

# CCFLAGS += -pedantic

DRIVERS += sysclock uart i2c timer
MODULES += gui

MODULES += cmdline
FONTS += Lucida_Console10

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
