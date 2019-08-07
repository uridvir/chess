#pragma once
#include "Position.h"
#include "Piece.h"
#include <set>

namespace Chess 
{

	enum Color { White, Black };

	class Piece;

	class Board
	{

	private:
		Piece* squareArray[8][8];

		std::set<Piece*> whitePieces;
		std::set<Piece*> blackPieces;

		Piece* whiteKing;
		Piece* blackKing;

	public:

		bool hasPieceAt(Position pos);
		Piece* pieceAt(Position pos);
		Piece* kingOfColor(Color color);
		std::set<Piece*> allPiecesOfColor(Color color);

	};

}