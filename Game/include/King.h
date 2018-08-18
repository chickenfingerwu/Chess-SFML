#pragma once
#include "Piece.h"

class King:public Piece
{
    public:
        King(Player* player,Square* square);
        bool canCapture(Piece* capture_piece);
        bool isValidPath(int finalX,int finalY);
        void drawPath(int finalX,int finalY);
        ~King();
};
