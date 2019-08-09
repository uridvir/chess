#pragma once
#include "Piece.h"
namespace Chess
{
	class Queen: public Piece
	{
	public:
		using Piece::Piece;
		bool couldAttack(Position newPosition) override;
		PieceType type() const override;
	};
}