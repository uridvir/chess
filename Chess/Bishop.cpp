#include "Bishop.h"
#include "Path.h"
using namespace Chess;

bool Chess::Bishop::couldAttack(Position newPosition)
{
	auto path = Path(this->position, newPosition);
	return path.exists() && path.type() == Path::Diagonal;
}

PieceType Chess::Bishop::type() const
{
	return { PieceType::Bishop, this->color };
}
