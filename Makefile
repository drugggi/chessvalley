# declare the variable
CC=g++
CFLAGS=-c

DEPS = chessboard.h bitboards.h pieceinfo.h search.h evaluate.h
OBJ = chessvalley.o chessboard.o bitboards.o pieceinfo.o search.o evaluate.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

chessvalley: chessvalley.o chessboard.o bitboards.o pieceinfo.o search.o evaluate.o
	$(CC) chessvalley.o chessboard.o bitboards.o pieceinfo.o search.o evaluate.o -o chessvalley


# chessvalley is the "target" and after ": " are the dependencies and next line after <Tab> is the command
chessvalleyold: chessvalley.o chessboard.o pieceinfo.o bitboards.o chessboard.h bitboards.h pieceinfo.h evaluate.h
	$(CC) chessvalley.cpp chessboard.cpp pieceinfo.cpp bitboards.cpp evaluate.cpp -o chessvalley

# remove object files and executable chessvalley
clean:
	rm *.o chessvalley 
