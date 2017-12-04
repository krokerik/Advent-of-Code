SRC    = $(wildcard *.c)
OBJ    = $(SRC:.c=.o)
PROBS  = $(basename $(SRC))
CC     = gcc
CFLAGS = -g -Wall -Werror

.PHONY: all clean
all: $(PROBS)
clean:
	rm -f $(OBJ) $(PROBS)

.SECONDEXPANSION:
$(PROBS): $$@.o
	$(CC) $(CFLAGS) -o $@ $^ -lm
$(OBJ): $$(basename $$@).c
	$(CC) $(CFLAGS) -c $^
