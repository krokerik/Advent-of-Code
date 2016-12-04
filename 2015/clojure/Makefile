SRC = $(wildcard *.clj)
PROBS = $(SRC:.clj=.out)

.PHONY: all clean
all: $(PROBS)
clean:
	rm -f *.class

.SECONDEXPANSION:
$(PROBS): $$(basename $$@).clj
	java -cp ~/.clojure/clojure.jar clojure.main $^ > $@
