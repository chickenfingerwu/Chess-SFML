#pragma once
#include <vector>
#include "Type.h"
#include "Square.h"
#include <vector>
using namespace std;
class Piece;
class Player;
class Board
{
    public:
        int m_width,m_height;
        Square*** m_board;
        Piece*** BoardPiece;
        Board();
        ~Board();
        Board(int width,int height);
        vector<Piece*> whitePieces;
        vector<Piece*> blackPieces;
        Piece* getPiece(Square* square);
        bool PathIsNotObscured(vector<vector<int>> &path);
        void setupPieceVector();
        void MovePiece(int finalX,int finalY,Piece* piece);
        void SetPiece(Piece* piece,Square* newSquare);
        bool validLeaping(Piece* piece,int** path);
        bool EndGame(int finalX,int finalY,Piece* piece);
        bool isValidMove(Piece* piece,int finalX,int finalY);
        bool isWithinBoard(int finalX, int finalY);
        bool isNotOrigin(Square* square,int finalX,int finalY);
        void setupPieces(Player* player1,Player* player2);
        void setupPlayer1pieces(Player* player);
        void setupPlayer2pieces(Player* player);
};
