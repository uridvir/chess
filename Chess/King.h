#pragma once
#include "Piece.h"

namespace Chess {

	class Piece;

	class King : public Piece
	{
	public:
		using Piece::Piece;
		bool couldAttack(Position newPosition) override;
		bool canMove(Position newPosition) override;
		Piece* getCastlingRook(Position moveTo) override;
		bool movePutsInCheck(Piece *const piece, Position newPosition) override;
		PieceType type() const override;
	};
}