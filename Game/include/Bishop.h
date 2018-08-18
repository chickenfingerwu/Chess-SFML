#pragma once
#include "Piece.h"

class Bishop:public Piece
{
    public:
        Bishop(Player* player,Square* square);
        bool canCapture(Piece* capture_piece);
        bool isValidPath(int finalX,int finalY);
        void drawPath(int finalX,int finalY);
        ~Bishop();
};
