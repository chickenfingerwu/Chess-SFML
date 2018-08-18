#pragma once
#include "Piece.h"

class Queen:public Piece
{
    public:
        Queen(Player* player,Square* square);
        bool canCapture(Piece* capture_piece);
        bool isValidPath(int finalX,int finalY);
        void drawPath(int finalX,int finalY);
        ~Queen();
};
