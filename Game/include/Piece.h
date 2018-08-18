#pragma once
#include "Color.h"
#include "Type.h"
#include <vector>

/*The parent's class of all pieces*/

class Player;
class Square;
class Piece
{
    public:
        //piece's type
        Type m_type;
        //occupied board's square,
        //basically it's where the piece is on the board
        Square* PieceSquare;
        //piece's path when move
        std::vector<std::vector<int>> path;
        //not yet captured so we initialize to false
        bool isCaptured = false;
        //piece's player
        Player* m_player;
        Piece(Player* player,Square* square);
        virtual ~Piece();
        //virtual function to check whether or not
        //a piece can capture another piece
        virtual bool canCapture(Piece* capture_piece) = 0;
        //virtual function to check if piece's path is valid
        virtual bool isValidPath(int finalX,int finalY) = 0;
        //virtual function to draw piece's path
        virtual void drawPath(int finalX,int finalY) = 0;
};
