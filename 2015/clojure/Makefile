SRC = $(wildcard *.clj)
PROBS = $(basename $(SRC))

.PHONY: all clean $(PROBS)
all: $(PROBS)
clean:
	rm -f *.class

.SECONDEXPANSION:
$(PROBS): $$@.clj
	java -cp ~/.clojure/clojure.jar clojure.main $^ > $@.out
