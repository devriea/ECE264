GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = answer06.o pa06.o
HDRS = pa06.h
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

pa06: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@


.c.o: 
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f pa06 $(OBJS) outputs/*
