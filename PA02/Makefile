TARGET = pa2
GCC = gcc
CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -Werror -pedantic

CC = $(GCC) $(CFLAGS)

SRCS = main.c huffman.c tree.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND =  valgrind --tool=memcheck --verbose --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

testmem: $(TARGET)
	# $(VALGRIND)=./valgrind.txt ./pa2 original/binary1 binary1.count binary1.tree binary1.code binary1.hbt
	$(VALGRIND)=./valgrind.txt ./pa2 original/empty empty.count empty.tree empty.code empty.hbt

testall: test1 test2 test3 test4 test5 test6 

test1: $(TARGET)
	./pa2 original/gophers gophers.count gophers.tree gophers.code gophers.hbt
	diff gophers.count count/gophers.count
	diff gophers.tree tree/gophers.tree
	diff gophers.code code/gophers.code
	diff gophers.hbt compressed/gophers.hbt

test2: $(TARGET)
	./pa2 original/empty empty.count empty.tree empty.code empty.hbt
	diff empty.count count/empty.count
	diff empty.tree tree/empty.tree
	diff empty.code code/empty.code
	diff empty.hbt compressed/empty.hbt

test3: $(TARGET)
	./pa2 original/lorum lorum.count lorum.tree lorum.code lorum.hbt
	diff lorum.count count/lorum.count
	diff lorum.tree tree/lorum.tree
	diff lorum.code code/lorum.code
	diff lorum.hbt compressed/lorum.hbt

test4: $(TARGET)
	./pa2 original/stone stone.count stone.tree stone.code stone.hbt
	diff stone.count count/stone.count
	diff stone.tree tree/stone.tree
	diff stone.code code/stone.code
	diff gophers.hbt compressed/gophers.hbt

test5: $(TARGET)
	./pa2 original/woods woods.count woods.tree woods.code woods.hbt
	diff woods.count count/woods.count
	diff woods.tree tree/woods.tree
	diff woods.code code/woods.code
	diff woods.hbt compressed/woods.hbt

test6: $(TARGET)
	./pa2 original/binary1 binary1.count binary1.tree binary1.code binary1.hbt
	diff binary1.count count/binary1.count
	diff binary1.tree tree/binary1.tree
	diff binary1.code code/binary1.code
	diff binary1.hbt compressed/binary1.hbt

clean: # remove all machine generated files
	rm -f sort *.o *.hbt *.tree *.code *.count *txt