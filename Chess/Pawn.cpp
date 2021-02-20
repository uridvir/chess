#include "Pawn.h"
using namespace Chess;

bool Chess::Pawn::couldAttack(Position newPosition)
{
	if (std::abs(newPosition.file() - this->position.file()) != 1)
	{
		return false;
	}

	switch (this->color) 
	{
	case Color::White:
		return newPosition.rank() - this->position.rank() == 1;
	case Color::Black:
		return newPosition.rank() - this->position.rank() == -1;
	default:
		return false;
	}
}

bool Chess::Pawn::canMove(Position newPosition)
{
	if (board->kingOfColor(this->color)->movePutsInCheck(this, newPosition))
	{
		return false;
	}
	if (couldAttack(newPosition) && board->hasPieceAt(newPosition) && board->pieceAt(newPosition)->color != this->color)
	{
		return true;
	}
	if (newPosition.file() - this->position.file() != 0 || board->hasPieceAt(newPosition))
	{
		return false;
	}

	const int rankChange = newPosition.rank() - this->position.rank();

	switch (this->color)
	{
	case Color::White:
		if (rankChange == 1)
		{
			return true;
		}
		return rankChange == 2 && this->position.rank() == 2;
	case Color::Black:
		if (rankChange == -1) 
		{
			return true;
		}
		return rankChange == -2 && this->position.rank() == 7;
	default:
		return false;
	}
}

Piece* Chess::Pawn::getEnPassantVictim(Position moveTo)
{
	Piece* victim = board->pieceAt(Position(moveTo.file(), this->position.rank()));
	if (!victim || !couldAttack(moveTo) || victim->color == this->color) {
		return nullptr;
	}
	if (victim->movesMade == 1 && board->justMoved == victim
		&& victim->position.rank() == (victim->color == Color::White ? 4 : 5)) {
		return victim;
	}
	return nullptr;
}

PieceType Chess::Pawn::type() const
{
	return { PieceType::Pawn, this->color };
}
