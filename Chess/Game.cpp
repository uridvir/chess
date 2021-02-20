#include "Game.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
using namespace Chess;

Chess::Game::Game()
{
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Rook(Color::White, Position("a1"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Knight(Color::White, Position("b1"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Bishop(Color::White, Position("c1"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Queen(Color::White, Position("d1"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new King(Color::White, Position("e1"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Bishop(Color::White, Position("f1"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Knight(Color::White, Position("g1"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Rook(Color::White, Position("h1"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::White, Position("a2"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::White, Position("b2"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::White, Position("c2"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::White, Position("d2"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::White, Position("e2"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::White, Position("f2"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::White, Position("g2"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::White, Position("h2"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Rook(Color::Black, Position("a8"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Knight(Color::Black, Position("b8"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Bishop(Color::Black, Position("c8"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Queen(Color::Black, Position("d8"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new King(Color::Black, Position("e8"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Bishop(Color::Black, Position("f8"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Knight(Color::Black, Position("g8"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Rook(Color::Black, Position("h8"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::Black, Position("a7"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::Black, Position("b7"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::Black, Position("c7"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::Black, Position("d7"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::Black, Position("e7"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::Black, Position("f7"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::Black, Position("g7"), &board)));
	board.pieces.emplace_back(std::unique_ptr<Piece>(new Pawn(Color::Black, Position("h7"), &board)));
	board.layoutPieces();
	whoseTurn = Color::White;
}

std::vector<std::vector<PieceType>> Game::getBoardState()
{
	auto state = std::vector<std::vector<PieceType>>(8, std::vector<PieceType>(8));
	for (int rank = 1; rank <= 8; rank++)
	{
		for (int file = 1; file <= 8; file++)
		{
			auto pos = Position(file, rank);
			if (!board.hasPieceAt(pos))
			{
				state[rank - 1][file - 1] = { PieceType::None };
				continue;
			}
			state[rank - 1][file - 1] = board.pieceAt(pos)->type();
		}
	}
	return state;
}

void Chess::Game::makeMove(Position from, Position to)
{
	auto movingPiece = board.pieceAt(from);
	if (movingPiece == nullptr || movingPiece->color != whoseTurn)
	{
		return;
	}
	if (!movingPiece->canMove(to))
	{
		Piece* partner = nullptr;
		switch (movingPiece->type().species) {
		case PieceType::Species::Pawn:
			partner = movingPiece->getEnPassantVictim(to);
			if (partner != nullptr) {
				Position victimPos = partner->position;
				board.removePiece(*partner);
				board.squareArray[victimPos.rank() - 1][victimPos.file() - 1] = nullptr;
			}
			else {
				return;
			}
			break;
		case PieceType::Species::King:
			partner = movingPiece->getCastlingRook(to);
			if (partner != nullptr) {
				board.squareArray[partner->position.rank() - 1][partner->position.file() - 1] = nullptr;
				partner->position = Position(to.file() < from.file() ? 4 : 6, partner->position.rank());
				board.squareArray[partner->position.rank() - 1][partner->position.file() - 1] = partner;
				partner->movesMade++;
			}
			else {
				return;
			}
			break;
		default:
			return;
		}
	}
	if (board.hasPieceAt(to))
	{
		board.removePiece(*board.pieceAt(to));
	}
	board.squareArray[to.rank() - 1][to.file() - 1] = movingPiece;
	board.squareArray[from.rank() - 1][from.file() - 1] = nullptr;
	movingPiece->position = to;
	movingPiece->movesMade++;
	board.justMoved = movingPiece;
	whoseTurn = whoseTurn == Color::White ? Color::Black : Color::White;
}
