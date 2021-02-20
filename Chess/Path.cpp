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

	const int fileChange = to.file() - from.file();
	const int rankChange = to.rank() - from.rank();

	doesExist = true;

	if ((fileChange == 0) ^ (rankChange == 0))
	{
		pathType = Horizontal;
	}
	else if (std::abs(fileChange) == std::abs(rankChange))
	{
		if (fileChange == 0) {
			doesExist = false;
		}
		pathType = Diagonal;
	}
	else if (std::abs(fileChange) + std::abs(rankChange) == 3)
	{
		pathType = Knight;
	}
	else 
	{
		doesExist = false;
	}

	auto signum = [](int x) -> int {
		if (x < 0)
		{
			return -1;
		}
		else if (x == 0)
		{
			return 0;
		}
		return 1;
	};

	startPos = from;
	endPos = to;

	if (pathType == Knight)
	{
		return;
	}

	fileIncrement = signum(fileChange);
	rankIncrement = signum(rankChange);
}

bool Path::obstructed(Board* board, Piece* obstructor) {

	if (pathType == Type::Knight || !doesExist) {

		return false;

	}

	int file = startPos.file() + fileIncrement;
	int rank = startPos.rank() + rankIncrement;

	while (file != endPos.file() || rank != endPos.rank()) {

		if (board->hasPieceAt(Position(file, rank))) {

			obstructor = board->pieceAt(Position(file, rank));

			if (board->hasPieceAt(startPos)) {
				Color oppColor = board->pieceAt(startPos)->color == Color::White ? Color::Black : Color::White;
				if (obstructor == board->kingOfColor(oppColor)) {
					return false;
				}
			}
			return true;

		}

		file += fileIncrement;
		rank += rankIncrement;

	}

	obstructor = nullptr;
	return false;

}

bool Path::goesThrough(Position pos)
{
	if (pathType == Type::Knight || !doesExist) {
		return false;
	}

	int file = startPos.file() + fileIncrement;
	int rank = startPos.rank() + rankIncrement;

	while (file != endPos.file() || rank != endPos.rank())
	{
		if (file == pos.file() && rank == pos.rank())
		{
			return true;
		}

		file += fileIncrement;
		rank += rankIncrement;
	}
	return false;
}

std::vector<Position> Path::liesBeyond()
{
	if (pathType == Type::Knight || !doesExist) {
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