SRC    = $(wildcard *.scm)
PROBS  = $(basename $(SRC))
SC     = csc

.PHONY: all clean
all: $(PROBS)
clean:
	rm -f $(PROBS)
.SECONDEXPANSION:
$(PROBS): $$@.scm
	$(SC) $(HFLAGS) $^