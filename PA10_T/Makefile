GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = answer10.o pa10.o
HDRS = pa10.h
TARGET = pa10
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: clean

pa10: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -r $(TARGET) $(OBJS)
