SUBDIRS := $(wildcard */.)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	$(MAKE) -C $% clean

.PHONY: clean all $(SUBDIRS)
