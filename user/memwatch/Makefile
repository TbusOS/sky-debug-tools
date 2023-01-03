
.PHONY: all install clean 

BIN = memwatch
#LIBS = -ldemo 
OBJDIR = obj
OBJS = memtest.o memwatch.o

CFLAGS += -O0 -g -DMEMWATCH -DMEMWATCH_STDIO
#CFLAGS += -O0 

all: $(OBJS)
	#$(CC) -o $(BIN) $(OBJS) $(LDFLAGS) $(LIBS)
	$(CC) -rdynamic -g -o $(BIN) $(OBJS) $(LDFLAGS)
	$(CROSS)objdump -D --debugging -S $(BIN) > $(BIN).asm	
	$(CROSS)objdump -D -S --debugging  $(OBJS) > $(BIN).o.asm	

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $<

install:
	mkdir -p $(INSTALLDIR)/$(BIN)/
	cp -f $(BIN) $(BIN).asm $(BIN).o.asm  $(INSTALLDIR)/$(BIN)/
	mkdir -p $(INSTALLDIR)/$(BIN)/
	cp -f $(OBJS)  $(INSTALLDIR)/$(BIN)/
	rm -rf $(BIN) *.asm *.o
#	cp -f $(ROOTDIR)/$(BIN).log $(INSTALLDIR)/$(BIN)/
#	rm -rf $(ROOTDIR)/$(BIN).log

clean:
	rm -rf $(BIN) *.asm *.o
