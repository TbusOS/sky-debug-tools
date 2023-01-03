
.PHONY: all install clean 

BIN = core_dump
#LIBS = -ldemo 
OBJDIR = obj
OBJS = core_dump.o

CFLAGS += -O0 -g -Dstatic=
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

clean:
	rm -rf $(BIN) *.asm *.o
