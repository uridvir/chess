#pragma once
#include "Position.h"
#include "Board.h"

namespace Chess {

	struct PieceType;
	class Board;
	enum Color;

	class Piece
	{

	protected:
		Board* board;

	public:
		Color color;
		Position position;
		int movesMade = 0;

		Piece(Chess::Color color, Position position, Board* board);
		virtual bool couldAttack(Position newPosition);
		virtual bool canMove(Position to);
		virtual Piece* getEnPassantVictim(Position moveTo);
		virtual Piece* getCastlingRook(Position moveTo);
		Piece* getPinner();
		virtual bool movePutsInCheck(Piece* const piece, Position to);
		virtual PieceType type() const;
	};
}