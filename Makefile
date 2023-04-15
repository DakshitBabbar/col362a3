CC=g++
CFLAGS=-std=c++11 -O3

sources=main.cpp src.cpp
objects=$(sources:.cpp=.o)

exec:$(objects)
	$(CC) $(CFLAGS) $^ -o $@

run: exec
	./exec ../random.txt output.txt 1000000 2 0

make debug: exec
	gdb --args ./exec input.txt output.txt 83 2 0

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o exec temp.* output.txt

remove:
	rm -f temp.*
