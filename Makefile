CC=g++
CFLAGS=-std=c++17 -O3 -g

sources=main.cpp src.cpp
objects=$(sources:.cpp=.o)

exec:$(objects)
	$(CC) $(CFLAGS) $^ -o $@

run: exec remove
	./exec input.txt output.txt 84 2 0

make debug: exec
	gdb --args ./exec input.txt output.txt 84 2 0

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o exec temp.* output.txt

remove:
	rm temp.*
