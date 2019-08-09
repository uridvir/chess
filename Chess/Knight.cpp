#include "Knight.h"
#include "Path.h"
using namespace Chess;

bool Chess::Knight::couldAttack(Position newPosition)
{
	auto path = Path(this->position, newPosition);
	return path.exists() && path.type() == Path::Knight;
}

PieceType Chess::Knight::type() const
{
	return { PieceType::Knight, this->color };
}
