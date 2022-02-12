CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -O2
BIN_PATH= dist/push-to-server
# OBJECTS =  build/main.o build/main_functions.o \
# 		   build/helper_functions.o build/server_info.o
OBJECTS =  build/main_functions.o build/helper_functions.o build/main.o

all: $(BIN_PATH)

$(BIN_PATH):  $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BIN_PATH)

build/main.o: src/main.c 
	$(CC) $(CFLAGS) -c $< -o $@

build/main_functions.o: src/main_functions.c headers/main_functions.h 
	$(CC) $(CFLAGS) -c $< -o $@

build/helper_functions.o: src/helper_functions.c headers/helper_functions.h headers/server_info_t.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm build/*.o
