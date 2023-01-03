
.PHONY: all install clean 

BIN = file_test
OBJS = file_test.o
#LIBS = -ldemo

CFLAGS += -O0

all: $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< 

install:
	mkdir -p $(INSTALLDIR)/$(BIN)/
	cp -f $(BIN) $(INSTALLDIR)/$(BIN)/
	cp -f $(OBJS)  $(INSTALLDIR)/$(BIN)/
	rm -rf $(BIN) *.asm *.o

clean:
	rm -rf $(BIN)  *.o
