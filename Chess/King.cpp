#include "King.h"
#include "Path.h"
using namespace Chess;

bool King::couldAttack(Position newPosition)
{
	//TODO: Get rid of this check and implement errors
	if (!newPosition.exists())
	{
		return false;
	}

	if (std::abs(newPosition.file() - this->position.file()) <= 1 && std::abs(newPosition.rank() - this->position.rank()) <= 1)
	{
		return true;
	}

	return false;

}

bool King::canMove(Position newPosition)
{
	if (!couldAttack(newPosition)) 
	{
		return false;
	}

	for (auto threat : board->allPiecesOfColor(this->color == Color::White ? Color::Black : Color::White))
	{
		auto path = Path(threat->position, newPosition);
		
		if (path.exists() && threat->couldAttack(newPosition) && !path.obstructed(board)) 
		{
			return false;
		}
	}

	return true;
}

bool King::movePutsInCheck(Piece *const piece, Position newPosition)
{
	
	if (piece->isPinned()) {

		return true;

	}

	for (auto threat : board->allPiecesOfColor(this->color == Color::White ? Color::Black : Color::White)) {

		auto path = Path(threat->position, this->position);

		if (path.exists() && threat->couldAttack(this->position) && !path.obstructed(board) && !path.goesThrough(newPosition))
		{
			return true;
		}
	}

	return false;

}

PieceType King::type() const
{
	return { PieceType::King, this->color };
}