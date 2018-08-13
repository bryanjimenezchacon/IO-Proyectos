# change application name here (executable output name)
TARGET=main_menu
 
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN = -w
 
PTHREAD=-pthread
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
 
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
 
OBJS=    main_menu.o
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)


	./main_menu
    

    
main_menu.o: src/main_menu.c
	$(CC) -c $(CCFLAGS) src/main_menu.c $(GTKLIB) -o main_menu.o

    
clean:
	rm -f *.o $(TARGET) 
