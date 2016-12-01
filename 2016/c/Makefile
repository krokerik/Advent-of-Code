SRC   = $(wildcard *.c)
OBJ   = $(SRC:.c=.o)
PROBS = $(basename $(SRC))
CC    = gcc

.PHONY: all clean
all: $(PROBS)
clean:
	rm -f $(OBJ) $(PROBS)

.SECONDEXPANSION:
$(PROBS): $$@.o
	$(CC) -g -o $@ $^
$(OBJ): $$(basename $$@).c
	$(CC) -g -c $^
