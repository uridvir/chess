#pragma once
#include "Piece.h"
namespace Chess
{
	class Rook: public Piece
	{
	public:
		using Piece::Piece;
		bool couldAttack(Position newPosition) override;
		PieceType type() const override;
	};
}
