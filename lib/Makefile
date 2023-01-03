
LIB_DIRS=
LIB_DIRS += libdemo

.PHONY: all install clean 

all: 
	for dir in $(LIB_DIRS); do [ ! -d $$dir ] || make -C $$dir ; done

install:
	for dir in $(LIB_DIRS); do [ ! -d $$dir ] || make -C $$dir install ; done

clean:
	for dir in $(LIB_DIRS); do [ ! -d $$dir ] || make -C $$dir clean ; done


%_only:
	$(MAKE) -C $(@:_only=)

%_install:
	$(MAKE) -C $(@:_install=) install

%_clean:
	$(MAKE) -C $(@:_clean=) clean