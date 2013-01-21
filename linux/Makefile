CC = g++ -pg -ansi

all:
	$(CC) Game.cpp Object.cpp Enemy.cpp GLContext.cpp GameController.cpp Crate.cpp Vector.cpp Player.cpp -o game -lGL -lGLU `sdl-config --cflags --libs`

clean:
	@echo Cleaning up...
	@rm lesson01
	@echo Done.
