CC = g++
FLAGS = -std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
COMPILE_FLAGS = $(FLAGS) -c 

example.out: main.o Game.o Rocket.o
	$(CC) main.o Game.o Rocket.o rsdl.cpp $(FLAGS) -o example.out

main.o: main.cpp 
	$(CC) $(COMPILE_FLAGS) main.cpp

Rocket.o: Rocket.h Rocket.cpp Game.h
	$(CC) $(COMPILE_FLAGS) Rocket.cpp

Game.o: Game.h Game.cpp Rocket.h
	$(CC) $(COMPILE_FLAGS) Game.cpp

Game.h: Rocket.h

.PHONY: clean

clean:
	rm *.o 