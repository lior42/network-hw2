SUBDIRS:=$(patsubst %/.,%,$(wildcard */.))
BINDIR:=bin
INNERPROGNAME:=prog

all: $(SUBDIRS) $(BINDIR)

$(SUBDIRS): $(BINDIR)
	$(MAKE) BIN=prog -C $@/.
	cp $@/build/prog $(BINDIR)/$@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir clean; \
	done
	mkdir -p $(BINDIR) && rm -rf $(BINDIR)

.PHONY: all $(SUBDIRS)

