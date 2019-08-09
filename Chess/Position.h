#pragma once

#include<string>

namespace Chess {

	class Position
	{

	private:

		//The column
		int fileValue;

		//The row
		int rankValue;

		//Is this a valid position?
		bool doesExist;

	public:

		int file() const;
		int rank() const;
		bool exists();

		explicit Position(int file = 0, int rank = 0);
		explicit Position(std::string pos);
	};

	bool operator==(const Position& lhs, const Position& rhs);
	bool operator!=(const Position& lhs, const Position& rhs);

}