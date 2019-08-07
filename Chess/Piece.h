#pragma once
#include "Position.h"
#include "Board.h"

namespace Chess {

	class Board;
	enum Color;

	class Piece
	{

	protected:
		Board* board;

	public:

		Color color;
		Position position;

		Piece(Chess::Color color, Position position, Board* board);
		virtual bool couldReach(Position newPosition);
		virtual bool canMove(Position to);
		bool isPinned();

		virtual bool isKing();
		virtual bool movePutsInCheck(Piece* const piece, Position to);

	};

}