#include "Board.h"
using namespace Chess;

bool Board::hasPieceAt(Position pos)
{
	return false;
}

Piece* Board::pieceAt(Position pos)
{
	return squareArray[pos.rank() - 1][pos.file() - 1];
}

Piece* Board::kingOfColor(Color color)
{
	return color == Color::White ? whiteKing : blackKing;
}

std::set<Piece*> Board::allPiecesOfColor(Color color)
{
	return color == Color::White ? whitePieces : blackPieces;
}
