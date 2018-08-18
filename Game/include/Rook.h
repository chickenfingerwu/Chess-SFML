#pragma once
#include "Piece.h"

class Rook : public Piece
{
    public:
        Rook(Player* player,Square* square);
        bool canCapture(Piece* capture_piece);
        bool isValidPath(int finalX,int finalY);
        void drawPath(int finalX,int finalY);
        virtual ~Rook();
};
