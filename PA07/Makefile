GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = answer07.o pa07.o
HDRS = pa07.h
TARGET = pa07
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose
TESTN := $(shell seq 0 10)
TESTS := $(addprefix test,${TESTN})

.PHONY : clean testall $(TESTS)

pa07: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@


.c.o: 
	$(GCC) $(CFLAGS) -c $*.c

testall: | $(TESTS)

${TESTS}: test%:
	./$(TARGET) inputs/input$*_A inputs/input$*_B

clean:
	rm -f pa07 $(OBJS) outputs/*
