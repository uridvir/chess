#pragma once
#include "Piece.h"

namespace Chess
{
	class Piece;

	class Pawn: public Piece
	{
	public:
		using Piece::Piece;
		bool couldAttack(Position newPosition) override;
		bool canMove(Position newPosition) override;

		PieceType type() const override;
	};
}