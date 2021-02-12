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

	return !this->movePutsInCheck(this, newPosition);
}

Piece* Chess::King::getCastlingRook(Position moveTo)
{
	if (this->movesMade != 0 || moveTo.file() != 3 && moveTo.file() != 7) {
		return nullptr;
	}
	Piece* rook = board->pieceAt(Position(moveTo.file() < this->position.file() ? 1 : 8, this->position.rank()));
	if (!rook || rook->movesMade != 0 || Path(this->position, rook->position).obstructed(board)) {
		return nullptr;
	}

	auto signum = [](int x) -> int {
		if (x < 0) return -1;
		else if (x == 0) return 0;
		return 1;
	};

	int inc = signum(moveTo.file() - this->position.file());
	for (int file = this->position.file(); file - inc != moveTo.file(); file += inc) {
		if (this->movePutsInCheck(this, Position(file, this->position.rank()))) {
			return nullptr;
		}
	}
	return rook;
}

bool King::movePutsInCheck(Piece *const piece, Position newPosition)
{
	Piece *const pinner = piece->getPinner();

	if (pinner != nullptr && pinner->position != newPosition) {

		return true;

	}

	//TODO: Implement a "checked" state so that this check only happens when king has been checked
	Position kingPos = piece == this ? newPosition : this->position;
	for (auto threat : board->allPiecesOfColor(this->color == Color::White ? Color::Black : Color::White)) {

		auto path = Path(threat->position, kingPos);
		if (path.exists() && threat->couldAttack(kingPos) && !path.obstructed(board) && !path.goesThrough(newPosition)
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