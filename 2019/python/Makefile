SRC = $(wildcard *.py)
PROBS = $(basename $(SRC))
INT = python3

all: $(PROBS)

.SECONDEXPANSION:
$(PROBS): $$@.py
	$(INT) $^
