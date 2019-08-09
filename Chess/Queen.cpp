#include "Queen.h"
#include "Path.h"
using namespace Chess;

bool Chess::Queen::couldAttack(Position newPosition)
{
	auto path = Path(this->position, newPosition);
	return path.exists() && (path.type() == Path::Horizontal || path.type() == Path::Diagonal);
}

PieceType Chess::Queen::type() const
{
	return { PieceType::Queen, this->color };
}