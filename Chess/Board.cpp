#include "Board.h"
#include <algorithm>
using namespace Chess;

void Chess::Board::layoutPieces()
{
	for (auto it = pieces.begin(); it != pieces.end(); it++)
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

void Chess::Board::removePiece(Piece& piece)
{
	switch (piece.color)
	{
	case Color::White:
		whitePieces.erase(&piece);
		break;
	case Color::Black:
		blackPieces.erase(&piece);
		break;
	}

	//Don't clear whiteKing or blackKing because capturing a king is illegal

	auto check = [&piece](std::unique_ptr<Piece>& ptr) -> bool {
		return ptr.get() == &piece;
	};

	auto it = std::find_if(pieces.begin(), pieces.end(), check);
	if (it != pieces.end())
	{
		squareArray[it->get()->position.rank() - 1][it->get()->position.file() - 1] = nullptr;
		pieces.erase(it);
	}
}

Chess::Board::Board()
{
	squareArray = std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr));
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