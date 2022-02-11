CC 	      = gcc
CFLAGS 	  = -Wall -Wextra -Werror -O3
BUILD_DIR = build
DIST_DIR  = dist
BIN 	  = run
BIN_PATH  = $(DIST_DIR)/$(BIN)
OBJECTS   = $(BUILD_DIR)/main.o

all: $(BIN_PATH)

$(BIN_PATH): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/main.o: *.c
	$(CC) -c $< -o $@

debug:
	$(CC) -g $(CFLAGS) $(MAIN)

run: $(DIST_DIR)/$(BIN)
	./$(DIST_DIR)/$(BIN)

clean:
	rm $(BUILD_DIR)/*.o
