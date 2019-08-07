#pragma once
#include <vector>

namespace Chess 
{

	enum Color { White, Black };

	struct PieceType
	{
		enum Species { King, Queen, Rook, Knight, Bishop, Pawn, None };
		Species type;
		Color color;
	};
	
	class Game
	{
	public:
		std::vector<std::vector<PieceType>> getBoardState();
	};

}