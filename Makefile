CC = clang
CFLAGS = -g -Wall -Wextra -Wpedantic -I /opt/homebrew/include/SDL2
LDFLAGS = -L /opt/homebrew/lib -lSDL2
EXEC = chip8-emulator

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): main.o platform.o instructions.o components.o utils.o
	$(CC) $(LDFLAGS) $^ -o $@

# Compile object files
main.o: main.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

platform.o: platform.c platform.h
	$(CC) $(CFLAGS) -c $< -o $@

instructions.o: instructions.c instructions.h
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $< -o $@

components.o: components.c components.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f *.o $(EXEC)

.PHONY: all clean

