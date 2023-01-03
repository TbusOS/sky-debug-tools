
.PHONY: all install clean 

BIN = libdemo.so
OBJS = libdemo.o

CFLAGS += -O0

all: $(OBJS)
	$(CC) -fPIC -shared -o $(BIN) $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) -fPIC $(CFLAGS) $(LDFLAGS) -c $< 

install:
	mkdir -p $(INSTALLDIR)/lib/
	cp -f libdemo.so $(INSTALLDIR)/lib/
	mkdir -p $(INSTALLDIR)/include/
	cp -f libdemo.h $(INSTALLDIR)/include/

clean:
	rm -rf $(BIN)  *.o
