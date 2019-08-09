#include "Piece.h"
#include "Path.h"
using namespace Chess;

Piece::Piece(Color color, Position position, Board* board) {

	this->color = color;
	this->position = position;
	this->board = board;

}

bool Piece::couldAttack(Position newPosition)
{
	return false;
}

bool Piece::isPinned()
{

	auto path = Path(board->kingOfColor(this->color)->position, this->position);

	if (!path.exists() || path.obstructed(board)) {

		return false;

	}

	auto positions = path.liesBeyond();

	for (auto position : positions) {

		/*
		Consider the first piece encountered as we move beyond the "pinned" piece. If it could threaten the king, there is a pin.
		Otherwise there is no pin because the piece is in the way.
		*/
		if (board->hasPieceAt(position)) {
			auto piece = board->pieceAt(position);
			return (piece->color != this->color) && piece->couldAttack(board->kingOfColor(this->color)->position);
		}

	}

	return false;

}

bool Piece::canMove(Position newPosition)
{
	
	if (!couldAttack(newPosition) || Path(this->position, newPosition).obstructed(board)) {

		return false;

	}

	if (board->kingOfColor(this->color)->movePutsInCheck(this, newPosition)) {

		return false;

	}

	return true;

}

bool Chess::Piece::movePutsInCheck(Piece* const piece, Position to)
{
	return false;
}

PieceType Chess::Piece::type() const
{
	return { PieceType::None };
}