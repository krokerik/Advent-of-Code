SRC = $(wildcard *.java)
OBJ = $(SRC:.java=.class)

.PHONY: all clean
all: $(OBJ)
clean:
	rm -f *.class

.SECONDEXPANSION:
$(OBJ): $$(basename $$@).java
	javac $^
