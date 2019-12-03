PROGRAM = paperman
OBJS = main.o keyboard.o texture.o list.o shape.o vector.o
CC = gcc
CFLAGS = -Wall -O2 -I/usr/X11R6/include
LDLIBS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm -lpthread

.SUFFIXES: .c .o

main: $(OBJS)
	$(CC) -o $(PROGRAM) $^ $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)
