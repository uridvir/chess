#include "Rook.h"
#include "Path.h"
using namespace Chess;

bool Chess::Rook::couldAttack(Position newPosition)
{
	auto path = Path(this->position, newPosition);
	return path.exists() && path.type() == Path::Horizontal;
}

PieceType Chess::Rook::type() const
{
	return { PieceType::Rook, this->color };
}