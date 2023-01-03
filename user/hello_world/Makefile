
.PHONY: all install clean 

BIN = hello_world
OBJS = hello_world.o
LIBS = -ldemo

CFLAGS += -O0

all: $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< 

install:
	mkdir -p $(INSTALLDIR)/bin/
	cp -f $(BIN) $(INSTALLDIR)/bin/

clean:
	rm -rf $(BIN)  *.o
