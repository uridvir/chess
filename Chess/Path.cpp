#include "Path.h"
using namespace Chess;

Position Path::start()
{
	return startPos;
}

Position Path::end()
{
	return endPos;
}

Path::Type Path::type()
{
	return pathType;
}

bool Path::exists()
{
	return doesExist;
}

Path::Path(Position from, Position to) {

	if ((to.file() - from.file() == 0) ^ (to.rank() - from.rank() == 0)) {

		doesExist = true;
		pathType = Type::Horizontal;

	}
	else if (std::abs(to.file() - from.file()) == std::abs(to.rank() - from.rank())) {

		doesExist = true;
		pathType = Type::Diagonal;

	}
	else if ((std::abs(to.file() - from.file()) == 2 && std::abs(to.rank() - from.rank()) == 1)
		|| (std::abs(to.file() - from.file()) == 1 && std::abs(to.rank() - from.rank()) == 2)) {

		doesExist = true;
		pathType = Type::Knight;

	}
	else {

		doesExist = false;

	}

	fileIncrement = to.file() - from.file() > 0 ? 1 : (to.file() - from.file() == 0 ? 0 : -1);
	rankIncrement = to.rank() - from.rank() > 0 ? 1 : (to.rank() - from.rank() == 0 ? 0 : -1);

	startPos = from;
	endPos = to;

}

bool Path::obstructed(Board* board) {

	if (pathType == Type::Knight) {

		return false;

	}

	int file = startPos.file() + fileIncrement;
	int rank = startPos.rank() + rankIncrement;

	while (file != endPos.file() && rank != endPos.rank()) {

		if (board->hasPieceAt(Position(file, rank))) {

			return true;

		}

		file += fileIncrement;
		rank += rankIncrement;

	}

	return false;

}

bool Path::goesThrough(Position pos)
{

	if (pathType == Type::Knight) {

		return false;

	}

	int file = startPos.file() + fileIncrement;
	int rank = startPos.rank() + rankIncrement;

	while (file != endPos.file() && rank != endPos.rank()) {

		if (file == pos.file() && rank == pos.rank()) {

			return true;

		}

		file += fileIncrement;
		rank += rankIncrement;

	}

	return false;

}

std::vector<Position> Path::liesBeyond()
{
	
	if (pathType == Type::Knight) {

		return {};

	}

	auto positions = std::vector<Position>();

	int file = endPos.file() + fileIncrement;
	int rank = endPos.rank() + rankIncrement;

	Position pos(file, rank);
	
	while (pos.exists()) {

		positions.push_back(pos);

		file += fileIncrement;
		rank += rankIncrement;

		pos = Position(file, rank);

	}

	return positions;

}