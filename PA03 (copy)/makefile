TARGET = pa3
GCC = gcc
CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -Werror -pedantic

CC = $(GCC) $(CFLAGS)

SRCS = main.c pa3.c stack.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND =  valgrind --tool=memcheck --verbose --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

testmem: $(TARGET)
	# $(VALGRIND)=./valgrind1.txt ./pa2 original/binary1 binary1.count binary1.tree binary1.code binary1.hbt
	$(VALGRIND)=./valgrind2.txt ./pa3 inputs/1K.po 1K.pr 1K.dim 1K.pck

testall: test1 test2 test3 test4 test5 testmem

test03: $(TARGET) # test
	./pa3 inputs/3.po 3.pr 3.dim 3.pck
test08: $(TARGET)
	./pa3 inputs/8.po 8.pr 8.dim 8.pck
test1: $(TARGET)
	./pa3 inputs/3.po 3.pr 3.dim 3.pck
	diff 3.pr expected/3.pr
	diff 3.dim expected/3.dim
	diff 3.pck expected/3.pck

test2: $(TARGET)
	./pa3 inputs/8.po 8.pr 8.dim 8.pck
	diff 8.pr expected/8.pr
	diff 8.dim expected/8.dim
	diff 8.pck expected/8.pck

test3: $(TARGET)
	./pa3 inputs/100.po 100.pr 100.dim 100.pck

test4: $(TARGET)
	./pa3 inputs/500.po 500.pr 500.dim 500.pck

test5: $(TARGET)
	./pa3 inputs/1K.po 1K.pr 1K.dim 1K.pck

clean: # remove all machine generated files
	rm -f sort *.o *.pr *.dim *.pck *.txt
