SOURCES = main.cpp Player.cpp Supervisor.cpp Game.cpp

build:
	g++ -g -Wall -o main $(SOURCES)
run: build
	./main > output.txt
clean:
	rm -f main output.txt