BINDIR:=build
INNERPROGNAME:=prog

IGNOREDIRS:=.cache $(BINDIR) share .vscode ref srv2

SUBDIRS:=$(filter-out $(IGNOREDIRS),$(patsubst %/.,%,$(wildcard */.)))

all: $(SUBDIRS) $(BINDIR)

$(SUBDIRS): $(BINDIR)
	$(MAKE) BIN=prog CFLAGS="-I $(PWD)/share" -C $@/.
	cp $@/build/prog $(BINDIR)/$@

$(BINDIR):
	mkdir -p $(BINDIR)

clean: $(BINDIR)
	for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir clean; \
	done
	rm -rf $(BINDIR)

.PHONY: all $(SUBDIRS)

