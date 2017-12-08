CCX ?= g++
CCXFLAGS = -Wall -Wextra -O3 -std=c++11

SRC_FILES = $(shell find . -name '*.h' -o -name '*.cpp')
BIN ?= main

$(BIN): $(SRC_FILES)
	$(CCX) $(CCXFLAGS) -o $@ $(filter %.cpp,$^)
