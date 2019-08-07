#pragma once
#include "Board.h"
#include <vector>

namespace Chess {

	class Board;

	class Path
	{

	public:
		enum Type { Horizontal, Diagonal, Knight };

	private:

		Position startPos;
		Position endPos;
		Type pathType;
		bool doesExist;

		signed int fileIncrement : 2;
		signed int rankIncrement : 2;

	public:

		Position start();
		Position end();
		Type type();
		bool exists();

		Path(Position from, Position to);
		bool obstructed(Board* board);
		bool goesThrough(Position pos);
		std::vector<Position> liesBeyond();

	};

}