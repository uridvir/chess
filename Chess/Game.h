#pragma once
#include <vector>
#include "Board.h"

namespace Chess 
{
	
	enum Color;
	
	class Game
	{

	private:
		Board board;

	public:
		Game();
		std::vector<std::vector<PieceType>> getBoardState();
	
	};

}