all: main.o Vector3d.o
	g++ -o task2 main.o Vector3d.o

main.o: main.cpp Vector3d.hpp
	g++ -c main.cpp

Vector3d.o: Vector3d.cpp Vector3d.hpp
	g++ -c Vector3d.cpp

clean:
	rm -rfv *.o task2

fmt:
	clang-format -i --verbose *.[ch]pp -style="{IndentWidth: 4, AccessModifierOffset: -4}"