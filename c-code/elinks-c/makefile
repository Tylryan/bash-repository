######### Layout Template ########

# target: dependencies
# command

######### Explanation ###########
# target is the expected output of your command
# $@ means target
# $< means dependencies
##################################

CC 		   = gcc
CFLAGS     = -Wall -Wextra -Werror -O3

SRC_DIR    = src
HEADER_DIR = $(SRC_DIR)/headers

BUILD_DIR    = build
DIST_DIR     = dist
BIN 	     = elinks-search
BIN_LOCATION = $(DIST_DIR)/$(BIN)

# One day i'll figure out the wildcard thing
# OBJECTS   = $(BUILD_DIR)/$(wildcard *.o)


# I like to order these least important up to most important
OBJECTS    = $(BUILD_DIR)/argument_parser.o $(BUILD_DIR)/helper_functions.o \
			 $(BUILD_DIR)/main_functions.o  $(BUILD_DIR)/main.o 

all: $(BIN_LOCATION)

$(BIN_LOCATION): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BIN_LOCATION)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/helper_functions.o: $(SRC_DIR)/helper_functions.c $(HEADER_DIR)/helper_functions.h $(HEADER_DIR)/structures.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main_functions.o: $(SRC_DIR)/main_functions.c $(HEADER_DIR)/main_functions.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/argument_parser.o: $(SRC_DIR)/argument_parser.c $(HEADER_DIR)/argument_parser.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(BUILD_DIR)/*.o
