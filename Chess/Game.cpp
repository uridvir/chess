#include "Game.h"
using namespace Chess;

//TODO: Actually implement
std::vector<std::vector<PieceType>> Game::getBoardState()
{
	//Abbreviations
	PieceType WR = { PieceType::Rook, Color::White };
	PieceType WN = { PieceType::Knight, Color::White };
	PieceType WB = { PieceType::Bishop, Color::White };
	PieceType WQ = { PieceType::Queen, Color::White };
	PieceType WK = { PieceType::King, Color::White };
	PieceType WP = { PieceType::Pawn, Color::White };
	PieceType BR = { PieceType::Rook, Color::Black };
	PieceType BN = { PieceType::Knight, Color::Black };
	PieceType BB = { PieceType::Bishop, Color::Black };
	PieceType BQ = { PieceType::Queen, Color::Black };
	PieceType BK = { PieceType::King, Color::Black };
	PieceType BP = { PieceType::Pawn, Color::Black };
	PieceType NO = { PieceType::None };

	std::vector<std::vector<PieceType>> state =
	{ 
		{ WR, WN, WB, WQ, WK, WB, WN, WR },
		{ WP, WP, WP, WP, WP, WP, WP, WP },
		{ NO, NO, NO, NO, NO, NO, NO, NO },
		{ NO, NO, NO, NO, NO, NO, NO, NO },
		{ NO, NO, NO, NO, NO, NO, NO, NO },
		{ NO, NO, NO, NO, NO, NO, NO, NO },
		{ BP, BP, BP, BP, BP, BP, BP, BP },
		{ BR, BN, BB, BQ, BK, BB, BN, BR },
	};

	return state;
}
