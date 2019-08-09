#include "Board.h"
using namespace Chess;

void Chess::Board::layoutPieces()
{
	for (auto it = pieces.begin(); it < pieces.end(); it++)
	{
		auto piece = it->get();
		squareArray[piece->position.rank() - 1][piece->position.file() - 1] = it->get();

		switch (piece->color)
		{
		case Color::White:
			whitePieces.emplace(piece);
			if (piece->type().species == PieceType::King)
			{
				whiteKing = piece;
			}
			break;
		case Color::Black:
			blackPieces.emplace(piece);
			if (piece->type().species == PieceType::King)
			{
				blackKing = piece;
			}
			break;
		}
	}
}

Chess::Board::Board()
{
	squareArray = std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr));
	pieces = std::vector<std::unique_ptr<Piece>>();
}

bool Board::hasPieceAt(Position pos)
{
	return squareArray[pos.rank() - 1][pos.file() - 1] != nullptr;
}

Piece* Board::pieceAt(Position pos)
{
	return squareArray[pos.rank() - 1][pos.file() - 1];
}

Piece* Board::kingOfColor(Color color)
{
	return color == Color::White ? whiteKing : blackKing;
}

std::set<Piece*> Board::allPiecesOfColor(Color color)
{
	return color == Color::White ? whitePieces : blackPieces;
}
