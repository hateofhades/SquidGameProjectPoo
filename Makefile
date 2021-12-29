SOURCES = main.cpp Player.cpp

build:
	g++ -g -Wall -o main $(SOURCES)
clean:
	rm -f main