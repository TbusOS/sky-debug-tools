
#USER_DIRS=
#USER_DIRS += hello_world
USER_DIRS += core_dump \
			 memwatch \
#			 file_test

.PHONY: all install clean 

all: 
	for dir in $(USER_DIRS); do [ ! -d $$dir ] || make -C $$dir ; done

install:
	for dir in $(USER_DIRS); do [ ! -d $$dir ] || make -C $$dir install ; done

clean:
	for dir in $(USER_DIRS); do [ ! -d $$dir ] || make -C $$dir clean ; done


%_only:
	$(MAKE) -C $(@:_only=)

%_install:
	$(MAKE) -C $(@:_install=) install

%_clean:
	$(MAKE) -C $(@:_clean=) clean
