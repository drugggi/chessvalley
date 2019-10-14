chessvalley: chessvalley.o chessboard.o pieceinfo.o bitboards.o chessboard.h bitboards.h pieceinfo.h
	g++ chessvalley.cpp chessboard.cpp pieceinfo.cpp bitboards.cpp -o chessvalley
