CC=g++
CFLAGS=-std=c++17 -O3

sources=main.cpp src.cpp
objects=$(sources:.cpp=.o)

exec:$(objects)
	$(CC) $(CFLAGS) $^ -o $@

run: exec
	./exec input.txt output.txt 84 2 0

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o exec output.txt temp*