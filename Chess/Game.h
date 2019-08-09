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
		Color whoseTurn;

	public:
		Game();
		std::vector<std::vector<PieceType>> getBoardState();
		void makeMove(Position from, Position to);
	
	};

}