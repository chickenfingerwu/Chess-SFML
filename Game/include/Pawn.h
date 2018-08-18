#pragma once
#include "Piece.h"

class Pawn:public Piece
{
    public:
        Pawn(Player* player,Square* square);
        bool firstStride = true;
        bool canCapture(Piece* capture_piece);
        bool isValidPath(int finalX,int finalY);
        void drawPath(int finalX,int finalY);
        ~Pawn();
};
