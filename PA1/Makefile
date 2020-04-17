TARGET = pa1
GCC = gcc
CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -Werror -pedantic

CC = $(GCC) $(CFLAGS)

SRCS = pa1.c sequence.c shell_array.c shell_list.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND =  valgrind --tool=memcheck --verbose --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file
PROFILER = valgrind --tool=callgrind

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

testmemlist: $(TARGET)
	$(VALGRIND)=./valList.txt ./pa1 -l examples/15.b output/15l.b
testruntime: $(TARGET)
	$(PROFILER) ./pa1 -l examples/10K.b output/10kl.b
testmemarr: $(TARGET)
	$(VALGRIND)=./valArr.txt ./pa1 -a examples/100K.b output/100ka.b

testall: test1 test2 test10k test100k testMillion

test1: $(TARGET)
	./pa1 -a examples/15.b output/15a.b
	diff output/15a.b examples/15sa.b
	./pa1 -l examples/15.b output/15l.b
	diff output/15l.b examples/15sl.b

test2: $(TARGET)
	./pa1 -a examples/1K.b output/1Ka.b
	diff output/1Ka.b examples/1Ksa.b
	./pa1 -l examples/1K.b output/1Kl.b
	diff output/1Kl.b examples/1Ksl.b

test10k: $(TARGET)
	./pa1 -a examples/10K.b output/10ka.b
	./pa1 -l examples/10K.b output/10kl.b

test100k: $(TARGET)
	./pa1 -a examples/100K.b output/100ka.b
	./pa1 -l examples/100K.b output/100kl.b
testMillion: $(TARGET)
	./pa1 -l examples/1M.b output/1Ml.b
	./pa1 -a examples/1M.b output/1Ma.b
clean: # remove all machine generated files
	rm -f sort *.o output/* *.txt