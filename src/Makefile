FLAGS = -lncurses -lpthread
CC = g++

fliptris:	main.o tetriminos.o score.o lines.o game.o factory.o next.o window.o buffer.o
	$(CC) -o fliptris main.o tetriminos.o score.o lines.o game.o factory.o next.o window.o buffer.o $(FLAGS)

tetriminos.o:	tetriminos.cc tetriminos.h
	$(CC) -c tetriminos.cc $(FLAGS)

window.o:	window.cc window.h
	$(CC) -c window.cc $(FLAGS)

score.o: score.cc score.h
	$(CC) -c score.cc $(FLAGS)

lines.o: lines.cc lines.h
	$(CC) -c lines.cc $(FLAGS)

factory.o: factory.cc factory.h
	$(CC) -c factory.cc $(FLAGS)

next.o:	next.cc next.h
	$(CC) -c next.cc $(FLAGS)

game.o: game.cc game.h
	$(CC) -c game.cc $(FLAGS)

buffer.o: buffer.cc buffer.h
	$(CC) -c buffer.cc $(FLAGS)

tetris.o: tetris.cc tetris.h
	$(CC) -c tetris.cc $(FLAGS)

main.o:	main.cc
	$(CC) -c main.cc $(FLAGS)

clean:
	rm fliptris main.o tetriminos.o score.o lines.o factory.o next.o window.o game.o buffer.o
