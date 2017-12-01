SRC    = $(wildcard *.c)
OBJ    = $(SRC:.c=.o)
PROBS  = $(basename $(SRC))
CC     = gcc
CFLAGS = -Wall -g
CLIBS  = -lcrypto -lssl

.PHONY: all clean
all: $(PROBS)
clean:
	rm -f $(OBJ) $(PROBS)

.SECONDEXPANSION:
$(PROBS): $$@.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
$(OBJ): $$(basename $$@).c
	$(CC) $(CFLAGS) -c $^
