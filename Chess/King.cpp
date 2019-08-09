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
	//Check that the king can reach and isn't capturing his own color
	if (!couldAttack(newPosition) || board->hasPieceAt(newPosition) && board->pieceAt(newPosition)->color == this->color) 
	{
		return false;
	}

	//Check that the new position is safe
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

	//TODO: Implement a "checked" state so that this check only happens when king has been checked
	for (auto threat : board->allPiecesOfColor(this->color == Color::White ? Color::Black : Color::White)) {

		auto path = Path(threat->position, this->position);

		if (path.exists() && threat->couldAttack(this->position) && !path.obstructed(board) && !path.goesThrough(newPosition)
			&& newPosition != threat->position)
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