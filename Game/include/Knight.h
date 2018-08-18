#pragma once
#include "Piece.h"

class Knight:public Piece
{
    public:
        Knight(Player* player,Square* square);
        bool canCapture(Piece* capture_piece);
        bool isValidPath(int finalX,int finalY);
        void drawPath(int finalX,int finalY);
        ~Knight();
};
