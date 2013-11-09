GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS =  b2b.o
TARGET = b2b
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment

b2b: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

environment:
	@mkdir -p outputs

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -r $(TARGET) $(OBJS) outputs/*output* outputs/memoutput*
