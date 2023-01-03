
DIRS=
DIRS += lib
DIRS += user

ROOTDIR  = $(shell pwd)
INSTALLDIR = $(ROOTDIR)/install
LDFLAGS = -L$(INSTALLDIR)/lib -I$(INSTALLDIR)/include

export ROOTDIR INSTALLDIR LDFLAGS
#export CC=gcc
#export CC=arm-none-linux-gnueabi-gcc
#export CXX=g++
export CROSS=arm-none-linux-gnueabi-
export CC=$(CROSS)gcc

.PHONY: all
all: lib_only lib_install user_only user_install

.PHONY: install
install:
	for dir in $(DIRS); do [ ! -d $$dir ] || make -C $$dir install ; done	

.PHONY: clean
clean:
	for dir in $(DIRS); do [ ! -d $$dir ] || make -C $$dir clean ; done	

.PHONY: distclean
distclean:
	for dir in $(DIRS); do [ ! -d $$dir ] || make -C $$dir clean ; done	
	rm -rf $(INSTALLDIR)/


%_only:
	@case "$(@)" in \
	*/*) d=`expr $(@) : '\([^/]*\)/.*'`; \
	     t=`expr $(@) : '[^/]*/\(.*\)'`; \
	     make -C $$d $$t;; \
	*)   make -C $(@:_only=);; \
	esac

%_install:
	@case "$(@)" in \
	*/*) d=`expr $(@) : '\([^/]*\)/.*'`; \
	     t=`expr $(@) : '[^/]*/\(.*\)'`; \
	     make -C $$d $$t;; \
	*)   make -C $(@:_install=) install;; \
	esac

%_clean:
	@case "$(@)" in \
	*/*) d=`expr $(@) : '\([^/]*\)/.*'`; \
	     t=`expr $(@) : '[^/]*/\(.*\)'`; \
	     make -C $$d $$t;; \
	*)   make -C $(@:_clean=) clean;; \
	esac
