#include "Position.h"
using namespace Chess;

int Position::file() const
{
	return fileValue;
}

int Position::rank() const
{
	return rankValue;
}

bool Position::exists()
{
	return false;
}

Position::Position(int file, int rank) {
	doesExist = file >= 1 && file <= 8 && rank >= 1 && rank <= 8;

	if (!doesExist) {
		this->fileValue = 0;
		this->rankValue = 0;
	}
	else {
		this->fileValue = file;
		this->rankValue = rank;
	}
}

Position::Position(std::string pos) {

	doesExist = false;
	fileValue = 0;
	rankValue = 0;

	if (pos.length() != 2)
	{
		return;
	}

	if ('a' <= pos[0] && pos[0] <= 'h')
	{
		fileValue = pos[0] - 'a' + 1;
	}
	else if ('A' <= pos[0] && pos[0] <= 'H')
	{
		fileValue = pos[0] - 'A' + 1;
	}
	else {
		return;
	}

	if ('1' <= pos[1] && pos[1] <= '8') 
	{
		rankValue = pos[1] - '0';
	}
	else
	{
		return;
	}

	doesExist = true;
}