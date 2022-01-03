SOURCES = main.cpp Player.cpp Supervisor.cpp Game.cpp

build:
	g++ -g -Wall -o main $(SOURCES)
clean:
	rm -f main