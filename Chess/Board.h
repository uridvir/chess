#pragma once
#include "Position.h"
#include "Piece.h"
#include <set>
#include <vector>
#include <memory>

namespace Chess 
{

	enum Color { White, Black };

	class Piece;

	struct PieceType
	{
		enum Species { King, Queen, Rook, Knight, Bishop, Pawn, None };
		Species species;
		Color color;
	};

	class Board
	{

	private:
		std::vector<std::vector<Piece*>> squareArray;
		friend class Game;

		std::vector<std::unique_ptr<Piece>> pieces;

		std::set<Piece*> whitePieces;
		std::set<Piece*> blackPieces;

		Piece* whiteKing;
		Piece* blackKing;

		void layoutPieces();
		void removePiece(Piece& piece);
	public:
		Board();
		bool hasPieceAt(Position pos);
		Piece* pieceAt(Position pos);
		Piece* kingOfColor(Color color);
		std::set<Piece*> allPiecesOfColor(Color color);

	};

}