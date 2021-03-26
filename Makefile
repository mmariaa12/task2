CFLAG = -std=c++98 -Wall -Wextra

all: main.o Vector3d.o Particle.o ParticleSystem.o
	g++ -o task2 main.o Vector3d.o Particle.o ParticleSystem.o

main.o: main.cpp Vector3d.hpp Particle.hpp
	g++ $(CFLAG) -c main.cpp

Vector3d.o: Vector3d.cpp Vector3d.hpp
	g++ $(CFLAG) -c Vector3d.cpp

Particle.o: Particle.cpp Vector3d.hpp Particle.hpp
	g++ $(CFLAG) -c Particle.cpp

ParticleSystem.o: ParticleSystem.cpp Vector3d.hpp Particle.hpp \
ParticleSystem.hpp
	g++ $(CFLAG) -c ParticleSystem.cpp

clean:
	rm -rfv *.o task2

fmt:
	clang-format -i --verbose *.[ch]pp \
	-style="{IndentWidth: 4, AccessModifierOffset: -4}"