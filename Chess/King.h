#pragma once
#include "Piece.h"

namespace Chess {

	class Piece;

	class King : public Piece
	{

	public:
		bool couldReach(Position newPosition);
		bool canMove(Position newPosition);

		bool isKing() override;
		bool movePutsInCheck(Piece *const piece, Position newPosition) override;

	};

}