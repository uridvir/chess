#include "King.h"
#include "Path.h"
using namespace Chess;

bool King::couldReach(Position newPosition)
{
	return false;
}

bool King::canMove(Position newPosition)
{
	return false;
}

bool King::isKing() 
{
	return true;
}

bool King::movePutsInCheck(Piece *const piece, Position newPosition)
{
	
	if (piece->isPinned()) {

		return true;

	}

	for (auto threat : board->allPiecesOfColor(this->color == Color::White ? Color::Black : Color::White)) {

		auto path = Path(threat->position, this->position);

		if (path.exists() && threat->couldReach(this->position) && !path.obstructed(board) && !path.goesThrough(newPosition)) {

			return true;

		}

	}

	return false;

}
