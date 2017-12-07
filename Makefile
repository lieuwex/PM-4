CCX ?= g++
CCXFLAGS = -Wall -Wextra -O3

SRC_FILES = $(shell find . -name '*.h' -o -name '*.cpp')
BIN ?= main

$(BIN): $(SRC_FILES)
	$(CCX) $(CCXFLAGS) -o $@ $(filter %.cpp,$^)
